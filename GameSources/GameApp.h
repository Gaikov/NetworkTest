// Copyright (c) 2003-2024, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GameApp.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once

#include "ClientSprite.h"
#include "Engine/display/container/VisualContainer2d.h"
#include "Engine/GameApp.h"
#include "Engine/display/Sprite.h"
#include "Engine/timing/FixedUpdate.h"
#include "Networking/client/Client.h"

class nsGameTemplate : public IGameApp, nsFixedUpdateListener {
    nsVisualContainer2d *_stage = nullptr;
    IRenDevice *_device = nullptr;
    nsClient  *_client = nullptr;
    nsClientSprite *_self = nullptr;
    int _selfId = -1;
    std::vector<nsClientSprite *> _sprites;
    nsFixedUpdate _fixedUpdate;

public:
    nsGameTemplate();

private:
    bool Init() override;
    void Release() override;
    void Loop(float frameTime) override;
    void DrawWorld() override;

    void OnActivate(bool active) override;
    void OnPause(bool paused) override;

    bool InitDialog() override;
    int GetWindowIcon() override;
    IUserInput *GetUserInput() override;
    void GetGUIDimension(int &width, int &height) override;
    const char *GetVersionInfo() override;

    void OnFixedUpdate(float frameTime) override;
};
