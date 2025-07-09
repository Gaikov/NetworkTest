//
// Created by Roman on 6/4/2025.
//

#include "ClientSprite.h"

#include "Engine/TimeFormat.h"
#include "Packets.h"
#include "Engine/Input.h"
#include "Engine/RenManager.h"
#include "Engine/utils/AppUtils.h"

nsClientSprite::nsClientSprite(nsClient *client, int clientId, bool local)
    : _client(client),
      _local(local),
      _clientId(clientId) {

    desc.tex = _device->TextureLoad("textures/client.png");
    desc.ComputeCenter();
    renState = _device->StateLoad("default/rs/gui_clamp.txt");

    _state.RegisterVar(&_pos);
    _pos.SetHandler([this]() {
        origin.pos = _pos.GetValue();
    });

    _state.RegisterVar(&_color);
    _color.SetHandler([this]() {
       desc.color = _color.GetValue();
    });

    if (_local) {
        const auto size = nsAppUtils::GetClientSize();
        nsVec2 pos;
        pos.Random(200);
        _pos.SetValue( size / 2 + pos);

        nsColor color;
        color.Rand();
        _color = color;
    }
}

void nsClientSprite::Loop() {
    nsSprite::Loop();

    if (_local) {
        UpdateLocal();
    }
}

bool nsClientSprite::OnNetPacket(const nsPacket *packet) {
    if (packet->id == nsClientPacketId::CLIENT_INFO) {
        const auto p = reinterpret_cast<const nsClientInfo *>(packet);
        if (p->clientId == _clientId) {
            _state.DeserializePacket(p);
            return true;
        }
    }
    return false;
}

void nsClientSprite::UpdateLocal() {
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
        nsVec2 pos = _pos.GetValue();
        dir.Norm();
        pos += dir * g_frameTime * 400;
        _pos = pos;
    }
}

void nsClientSprite::SendLocalState() const {
    nsClientInfo info = {};
    info.clientId = _clientId;
    info.targetType = TARGET_OTHER_CLIENTS;
    _client->SendState(&info, _state);
}

void nsClientSprite::FixedUpdate() const {
    if (_local) {
        SendLocalState();
    }
}
