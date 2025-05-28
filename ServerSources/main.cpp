#include "Core/debug/LogStdOut.h"
#include "Engine/Platform.h"
#include "Networking/Net.h"
#include "Networking/SocketServer.h"
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

    nsServerSocket server;
    if (server.Listen(3333)) {
        while (true) {
            auto client = server.Accept();
        }
    }

    nsNet::Release();
    Log::Release();
}
