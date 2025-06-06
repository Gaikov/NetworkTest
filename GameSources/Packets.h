// Copyright (c) 2003-2025, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Packets.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once
#include "Networking/Packet.h"
#include "nsLib/Vec2.h"
#include "nsLib/Color.h"

struct  nsClientPacketId {
    static constexpr unsigned short CLIENT_POSITION = nsPacketId::LAST_ID;
    static constexpr unsigned short CLIENT_SPAWN = nsPacketId::LAST_ID + 1;
    static constexpr unsigned short CLIENT_INFO = nsPacketId::LAST_ID + 2;
    static constexpr unsigned short CLIENT_DISCONNECTED = nsPacketId::LAST_ID + 3;
};

struct nsClientPosition : nsPacket {
    static constexpr unsigned short ID = nsClientPacketId::CLIENT_POSITION;
    int clientId;
    nsVec2 pos;
    nsColor color;
};

struct nsClientSpawn : nsPacket {
    static constexpr unsigned short ID = nsClientPacketId::CLIENT_SPAWN;
    int clientId;
    nsVec2 pos;
    nsColor color;
};

struct nsClientInfo : nsPacket {
    static constexpr unsigned short ID = nsClientPacketId::CLIENT_INFO;
    int clientId;
    nsVec2 pos;
    nsColor color;
};

struct nsClientDisconnected : nsPacket {
    static constexpr unsigned short ID = nsClientPacketId::CLIENT_DISCONNECTED;
    int clientId;
};

