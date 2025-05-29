#include <iostream>

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

    const auto server = new nsServer(3333);
    server->Start();

    while (true) {
        std::string command;
        std::getline(std::cin, command);
        if (command == "quit") {
            break;
        }
    }

    delete server;
    nsNet::Release();
    Log::Release();
}
