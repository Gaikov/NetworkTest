//
// Created by Roman on 10/10/2024.
//

#include "GameApp.h"
#include "Engine/Platform.h"
#include "Engine/display/VisualSceneRender2d.h"
#include "Engine/RenManager.h"
#include "Engine/Input.h"

static nsGameTemplate g_game;

IGameApp*	App_GetGame() {
    return &g_game;
}

bool nsGameTemplate::InitDialog() {
    return true;
}

bool nsGameTemplate::Init() {
    _stage = new nsVisualContainer2d();
    g_inp.ShowCursor(true);

    return true;
}

void nsGameTemplate::Release() {
    _stage->Destroy();
}

void nsGameTemplate::DrawWorld() {
    auto dev = nsRenDevice::Shared()->Device();

    dev->ClearScene(CLR_CBUFF | CLR_ZBUFF | CLR_STENCIL);

    nsVisualSceneRender2d::DrawScene(_stage);
}

void nsGameTemplate::Loop(float frameTime) {
    _stage->Loop();
}

void nsGameTemplate::OnActivate(bool active) {

}

void nsGameTemplate::OnPause(bool paused) {

}

int nsGameTemplate::GetWindowIcon() {
    return 0;
}
IUserInput *nsGameTemplate::GetUserInput() {
    return nullptr;
}

void nsGameTemplate::GetGUIDimension(int &width, int &height) {
    App_GetPlatform()->GetClientSize(width, height);
}

const char *nsGameTemplate::GetVersionInfo() {
    return "Template 1.0.0-alpha.0";
}
