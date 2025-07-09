// Copyright (c) 2003-2025, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ClientSprite.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once
#include "Engine/display/Sprite.h"
#include "Networking/client/Client.h"

class nsClientSprite : public nsSprite {
public:
    nsClientSprite(nsClient *client, int clientId, bool local);
    int GetId() const { return _clientId; }
    void FixedUpdate() const;

    void Loop() override;
    bool OnNetPacket(const nsPacket *packet);

private:
    nsClient * _client = nullptr;
    bool _local = false;
    int _clientId = 0;

    void UpdateLocal();
    void SendLocalState() const;
};
