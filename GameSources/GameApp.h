// Copyright (c) 2003-2024, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GameApp.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once

#include "Engine/GameApp.h"
#include "Engine/display/VisualContainer2d.h"

class nsGameTemplate : public IGameApp {
    bool InitDialog() override;
    bool Init() override;
    void Release() override;
    void DrawWorld() override;
    void Loop(float frameTime) override;
    void OnActivate(bool active) override;
    void OnPause(bool paused) override;
    int GetWindowIcon() override;
    IUserInput *GetUserInput() override;
    void GetGUIDimension(int &width, int &height) override;
    const char *GetVersionInfo() override;

private:
    nsVisualContainer2d *_stage = nullptr;
};