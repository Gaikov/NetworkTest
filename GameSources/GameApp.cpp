//
// Created by Roman on 10/10/2024.
//

#include "GameApp.h"

#include "Packets.h"
#include "Engine/Input.h"
#include "Core/Config.h"
#include "Engine/Platform.h"
#include "Engine/display/VisualSceneRender2d.h"
#include "Engine/RenManager.h"
#include "Networking/Net.h"
#include "Networking/client/Client.h"

nsGameTemplate::nsGameTemplate() : _fixedUpdate(20, this) {
}

bool nsGameTemplate::Init() {
    srand(time(nullptr));

    if (!nsNet::Init()) {
        return false;
    }

    _device = nsRenDevice::Shared()->Device();
    _stage = new nsVisualContainer2d();
    _self = new nsClientSprite();
    _stage->AddChild(_self);

    _client = new nsClient();
    _client->AddPacketHandler(nsPacketId::MESSAGE, [](const nsPacket *packet) {
        const auto msg = reinterpret_cast<const nsMessagePacket *>(packet);
        Log::Info("Net message: %s", msg->message);
    });

    _client->AddPacketHandler(nsPacketId::CLIENT_ID, [this](const nsPacket *packet) {
        const auto p = reinterpret_cast<const nsClientIdPacket *>(packet);
        Log::Info("Client ID: %i", p->id);
        _selfId = p->clientId;

        nsClientSpawn cc = {};
        cc.clientId = _selfId;
        cc.targetType = TARGET_OTHER_CLIENTS;
        cc.pos = _self->origin.pos;
        cc.color = _self->desc.color;
        _client->SendPacket(&cc);
    });

    _client->AddPacketHandler(nsClientPacketId::CLIENT_SPAWN, [this](const nsPacket *packet) {
        const auto p = reinterpret_cast<const nsClientSpawn *>(packet);
        //other client spawn
        nsClientSprite *s = new nsClientSprite();
        s->clientId = p->clientId;
        s->origin.pos = p->pos;
        s->desc.color = p->color;
        _sprites.push_back(s);
        _stage->AddChild(s);

        //self info to other client
        nsClientInfo info = {};
        info.clientId = _selfId;
        info.targetType = TARGET_CLIENT;
        info.targetId = p->clientId;
        info.pos = _self->origin.pos;
        info.color = _self->desc.color;
        _client->SendPacket(&info);
    });

    _client->AddPacketHandler(nsClientPacketId::CLIENT_INFO, [this](const nsPacket *packet) {
        const auto p = reinterpret_cast<const nsClientInfo *>(packet);
        for (auto it = _sprites.begin(); it != _sprites.end(); ++it) {
            if ((*it)->clientId == p->clientId) {
                (*it)->origin.pos = p->pos;
                (*it)->desc.color = p->color;
                return;
            }
        }

        nsClientSprite *s = new nsClientSprite();
        s->clientId = p->clientId;
        s->origin.pos = p->pos;
        s->desc.color = p->color;
        _sprites.push_back(s);
        _stage->AddChild(s);
    });

    _client->AddPacketHandler(nsClientPacketId::CLIENT_DISCONNECTED, [this](const nsPacket *packet) {
        const auto p = reinterpret_cast<const nsClientDisconnected *>(packet);
        for (auto it = _sprites.begin(); it != _sprites.end(); ++it) {
            if ((*it)->clientId == p->clientId) {
                _stage->RemoveChild(*it);
                _sprites.erase(it);
                delete *it;
                break;
            }
        }
    });

    g_cfg->RegCmd("msg", [this](int argc, const char *args[]) {
        if (argc < 2) {
            Log::Warning("Usage: msg <message>");
        } else {
            Log::Info("Sending message: %s", args[1]);
            nsMessagePacket msg = {};
            strcpy(msg.message, args[1]);
            _client->SendPacket(&msg);
        }
    });

    g_cfg->RegCmd("connect", [this](int argc, const char *args[]) {
        if (argc < 2) {
            Log::Warning("Usage: connect <ip>");
        } else {
            Log::Info("Connecting to %s", args[1]);
            _client->Disconnect();
            _client->Connect(args[1], 3333);
        }
    });

    g_cfg->RegCmd("disconnect", [this](int argc, const char *args[]) {
        _client->Disconnect();
    });

    _client->Connect("127.0.0.1", 3333);

    return true;
}

void nsGameTemplate::Release() {
    delete _client;

    if (_stage) {
        _stage->Destroy();
    }

    nsNet::Release();
}

void nsGameTemplate::DrawWorld() {
    _device->ClearScene(CLR_CBUFF | CLR_ZBUFF | CLR_STENCIL);

    nsVisualSceneRender2d::DrawScene(_stage);
}

void nsGameTemplate::Loop(float frameTime) {
    if (_client->GetState() == nsClient::DISCONNECTED) {
        for (auto s: _sprites) {
            _stage->RemoveChild(s);
            delete s;
        }
        _sprites.clear();
    }

    _client->ProcessPackets();
    _stage->Loop();

    auto app = App_GetPlatform();

    nsVec2 dir;
    if (app->IsKeyPressed(NS_KEY_RIGHT)) {
        dir.x = 1;
    }
    if (app->IsKeyPressed(NS_KEY_LEFT)) {
        dir.x = -1;
    }
    if (app->IsKeyPressed(NS_KEY_UP)) {
        dir.y = 1;
    }
    if (app->IsKeyPressed(NS_KEY_DOWN)) {
        dir.y = -1;
    }

    if (dir.x || dir.y) {
        nsVec2 pos = _self->origin.pos;
        dir.Norm();
        pos += dir * frameTime * 400;
        _self->origin.pos = pos;
    }

    _fixedUpdate.Update(frameTime);
}

void nsGameTemplate::OnFixedUpdate(float frameTime) {
    nsClientInfo info = {};
    info.clientId = _selfId;
    info.targetType = TARGET_OTHER_CLIENTS;
    info.pos = _self->origin.pos;
    info.color = _self->desc.color;
    _client->SendPacket(&info);
}

IUserInput *nsGameTemplate::GetUserInput() {
    return _stage;
}

void nsGameTemplate::OnActivate(bool active) {
}

void nsGameTemplate::OnPause(bool paused) {
}

int nsGameTemplate::GetWindowIcon() {
    return 0;
}

bool nsGameTemplate::InitDialog() {
    return true;
}


void nsGameTemplate::GetGUIDimension(int &width, int &height) {
    App_GetPlatform()->GetClientSize(width, height);
}

const char *nsGameTemplate::GetVersionInfo() {
    return "NetworkTest 1.0.0";
}

static nsGameTemplate g_game;

IGameApp *App_GetGame() {
    return &g_game;
}
