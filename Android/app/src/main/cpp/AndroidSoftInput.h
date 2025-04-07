//
// Created by Roman on 5/24/2024.
//

#pragma once

#include "Engine/input/ISoftInput.h"
#include "Platform/AndroidPlatform/JavaObject.h"
#include <game-activity/GameActivity.h>

class AndroidSoftInput : public ISoftInput {
public:
    AndroidSoftInput(JavaObject::sp_t activity);

    void Show() override;
    void Hide() override;

    bool IsActive() override;

private:
    JavaObject::sp_t _activity;
    bool _active = false;
};


