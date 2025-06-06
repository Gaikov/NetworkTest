//
// Created by Roman on 6/6/2025.
//

#include "TestServer.h"
#include "GameSources/Packets.h"

void nsTestServer::OnClientDisconnected(const nsClientConnection *c) {
    nsServer::OnClientDisconnected(c);

    nsClientDisconnected    packet = {};
    nsPacket::Init(&packet);
    packet.clientId = c->GetId();

    BroadcastPacket(&packet);
}
