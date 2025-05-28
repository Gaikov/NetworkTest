#include "Core/debug/LogStdOut.h"
#include "Engine/Platform.h"
#include "Networking/Net.h"
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

    nsNet::Release();
    Log::Release();
}
