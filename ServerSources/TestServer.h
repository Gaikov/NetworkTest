// Copyright (c) 2003-2025, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file TestServer.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once
#include "Networking/server/Server.h"

class nsTestServer : public nsServer {
public:
    explicit nsTestServer(int port)
        : nsServer(port) {
    }

protected:
    void OnClientDisconnected(const nsClientConnection *c) override;
};
