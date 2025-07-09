// Copyright (c) 2003-2025, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Packets.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once
#include "Networking/Packet.h"
#include "nsLib/Vec2.h"

struct  nsClientPacketId {
    static constexpr unsigned short CLIENT_INFO = nsPacketId::LAST_ID;
    static constexpr unsigned short CLIENT_DISCONNECTED = nsPacketId::LAST_ID + 1;
};

struct nsClientInfo : nsPacket {
    static constexpr unsigned short ID = nsClientPacketId::CLIENT_INFO;
    uint16_t clientId;
};

struct nsClientDisconnected : nsPacket {
    static constexpr unsigned short ID = nsClientPacketId::CLIENT_DISCONNECTED;
    uint16_t clientId;
};

