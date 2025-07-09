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

nsGameApp::nsGameApp() : _fixedUpdate(20, this) {
}

bool nsGameApp::Init() {
    srand(time(nullptr));

    if (!nsNet::Init()) {
        return false;
    }

    _client = new nsClient();

    _device = nsRenDevice::Shared()->Device();
    _stage = new nsVisualContainer2d();

    _client->State.AddHandler(nsPropChangedName::CHANGED, [this](const nsBaseEvent*) {
        const nsClient::ConnectionState state = _client->State;
        if (state == nsClient::DISCONNECTED) {
            for (const auto s: _sprites) {
                _stage->RemoveChild(s);
                delete s;
            }
            _sprites.clear();
            _selfId = -1;
        }
    });

    _client->AddPacketHandler(nsPacketId::MESSAGE, [](const nsPacket *packet) {
        const auto msg = reinterpret_cast<const nsMessagePacket *>(packet);
        Log::Info("Net message: %s", msg->message);
    });

    _client->AddPacketHandler(nsPacketId::CLIENT_ID, [this](const nsPacket *packet) {
        const auto p = reinterpret_cast<const nsClientIdPacket *>(packet);
        Log::Info("Client ID: %i", p->clientId);
        _selfId = p->clientId;

        const auto s = new nsClientSprite(_client, p->clientId, true);
        _sprites.push_back(s);
        _stage->AddChild(s);
    });

    _client->AddPacketHandler(nsClientPacketId::CLIENT_INFO, [this](const nsPacket *packet) {
        const auto p = reinterpret_cast<const nsClientInfo *>(packet);
        for (auto it = _sprites.begin(); it != _sprites.end(); ++it) {
            if ((*it)->GetId() == p->clientId) {
                (*it)->origin.pos = p->pos;
                (*it)->desc.color = p->color;
                return;
            }
        }

        const auto s = new nsClientSprite(_client, p->clientId, false);
        s->origin.pos = p->pos;
        s->desc.color = p->color;
        _sprites.push_back(s);
        _stage->AddChild(s);
    });

    _client->AddPacketHandler(nsClientPacketId::CLIENT_DISCONNECTED, [this](const nsPacket *packet) {
        const auto p = reinterpret_cast<const nsClientDisconnected *>(packet);
        for (auto it = _sprites.begin(); it != _sprites.end(); ++it) {
            if ((*it)->GetId() == p->clientId) {
                Log::Info("Removing client %i", p->clientId);
                (*it)->Destroy();
                _sprites.erase(it);
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
            _selfId = -1;
            _client->Connect(args[1], 3333);
        }
    });

    g_cfg->RegCmd("disconnect", [this](int argc, const char *args[]) {
        _client->Disconnect();
    });

    _client->Connect("127.0.0.1", 3333);

    return true;
}

void nsGameApp::Release() {
    delete _client;

    if (_stage) {
        _stage->Destroy();
    }

    nsNet::Release();
}

void nsGameApp::DrawWorld() {
    _device->ClearScene(CLR_CBUFF | CLR_ZBUFF | CLR_STENCIL);

    nsVisualSceneRender2d::DrawScene(_stage);
}

void nsGameApp::Loop(float frameTime) {
    _client->Update();
    _stage->Loop();

    _fixedUpdate.Update(frameTime);
}

void nsGameApp::OnFixedUpdate(float frameTime) {
    if (_client->State != nsClient::CONNECTED) {
        return;
    }

    for (auto s : _sprites) {
        s->FixedUpdate();
    }
}

IUserInput *nsGameApp::GetUserInput() {
    return _stage;
}

void nsGameApp::OnActivate(bool active) {
}

void nsGameApp::OnPause(bool paused) {
}

int nsGameApp::GetWindowIcon() {
    return 0;
}

bool nsGameApp::InitDialog() {
    return true;
}


void nsGameApp::GetGUIDimension(int &width, int &height) {
    App_GetPlatform()->GetClientSize(width, height);
}

const char *nsGameApp::GetVersionInfo() {
    return "NetworkTest 1.0.0";
}

static nsGameApp g_game;

IGameApp *App_GetGame() {
    return &g_game;
}
