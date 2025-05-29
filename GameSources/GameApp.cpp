//
// Created by Roman on 10/10/2024.
//

#include "GameApp.h"
#include "Engine/Platform.h"
#include "Engine/display/VisualSceneRender2d.h"
#include "Engine/RenManager.h"
#include "Engine/utils/AppUtils.h"
#include "Networking/Net.h"

bool nsGameTemplate::Init() {
    if (!nsNet::Init()) {
        return false;
    }

    _device = nsRenDevice::Shared()->Device();
    _stage = new nsVisualContainer2d();

    _socket = new nsClientSocket();
    if (!_socket->Connect("127.0.0.1", 3333)) {
        return false;
    }

    return true;
}

void nsGameTemplate::Release() {
    if (_stage) {
        _stage->Destroy();
    }

    nsNet::Release();
}

void nsGameTemplate::DrawWorld() {
    _device->ClearScene(CLR_CBUFF | CLR_ZBUFF | CLR_STENCIL);

    _stage->origin.pos = nsAppUtils::GetClientSize() / 2;

    nsVisualSceneRender2d::DrawScene(_stage);
}

void nsGameTemplate::Loop(float frameTime) {
    _stage->Loop();
    _stage->origin.angle = _stage->origin.angle + frameTime;
}

IUserInput *nsGameTemplate::GetUserInput() {
    return _stage;
}

void nsGameTemplate::OnActivate(bool active) {

}

void nsGameTemplate::OnPause(bool paused) {

}

int nsGameTemplate::GetWindowIcon() {
    return 0;
}

bool nsGameTemplate::InitDialog() {
    return true;
}


void nsGameTemplate::GetGUIDimension(int &width, int &height) {
    App_GetPlatform()->GetClientSize(width, height);
}

const char *nsGameTemplate::GetVersionInfo() {
    return "NetworkTest 1.0.0";
}

static nsGameTemplate g_game;

IGameApp*	App_GetGame() {
    return &g_game;
}

