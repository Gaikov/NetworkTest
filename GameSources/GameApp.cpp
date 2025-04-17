//
// Created by Roman on 10/10/2024.
//

#include "GameApp.h"
#include "Engine/Platform.h"
#include "Engine/display/VisualSceneRender2d.h"
#include "Engine/RenManager.h"
#include "Engine/Input.h"
#include "Engine/display/Sprite.h"
#include "Engine/display/text/TextLabel.h"
#include "Engine/utils/AppUtils.h"
#include "Engine/TimeFormat.h"
#include "Engine/renderer/font/FontsCache.h"

bool nsGameTemplate::Init() {
    _device = nsRenDevice::Shared()->Device();

    _stage = new nsVisualContainer2d();
    auto renState = _device->StateLoad("default/rs/gui_clamp.txt");

    auto sprite = new nsSprite();
    sprite->renState = renState;
    sprite->desc.tex = _device->TextureLoad("tests/background.jpg");
    sprite->desc.ResetSize().ComputeCenter();
    sprite->desc.color = nsColor::white;

    auto label = new nsTextLabel();
    label->color = nsColor::yellow;
    label->text = "Hello from GROm!";
    label->renState = renState;
    label->font = nsFontsCache::Shared()->LoadFont("tests/fonts/bmfont.fnt");

    _stage->AddChild(sprite);
    _stage->AddChild(label);


    nsRect  r;
    label->GetBounds(r, _stage);
    label->origin.pos = nsVec2(r.width, r.height) / -2;

    g_inp.ShowCursor(true);
    return true;
}

void nsGameTemplate::Release() {
    _stage->Destroy();
}

void nsGameTemplate::DrawWorld() {
    _device->ClearScene(CLR_CBUFF | CLR_ZBUFF | CLR_STENCIL);

    _stage->origin.angle = _stage->origin.angle + g_frameTime;
    _stage->origin.pos = nsAppUtils::GetClientSize() / 2;

    nsVisualSceneRender2d::DrawScene(_stage);
}

void nsGameTemplate::Loop(float frameTime) {
    _stage->Loop();
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
    return "Template 1.0.0";
}

static nsGameTemplate g_game;

IGameApp*	App_GetGame() {
    return &g_game;
}

