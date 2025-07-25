#include <iostream>

#include "TestServer.h"
#include "Core/Memory.h"
#include "Core/debug/LogStdOut.h"
#include "Engine/Platform.h"
#include "Networking/Net.h"
#include "Networking/server/Server.h"
#include "nsLib/log.h"

Platform* App_GetPlatform() {
    return nullptr;
}

static LogStdOut   out;

int main(int argc, char *argv[]) {
    Log::Init();
    Log::Shared()->AddPolicy(&out);
    Log::Info("Hello World!");
    if (nsNet::Init()) {
        Log::Info("Server initialized");
    }

    const auto server = new nsTestServer(3333);
    if (server->Start()) {
        while (true) {
            std::string command;
            std::getline(std::cin, command);
            if (command == "quit") {
                break;
            }
        }
    }

    server->Stop();
    delete server;
    nsNet::Release();
    Log::Release();
    mem_report();
    return 0;
}
