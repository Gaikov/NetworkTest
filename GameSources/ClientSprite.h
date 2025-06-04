// Copyright (c) 2003-2025, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ClientSprite.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once
#include "Engine/display/Sprite.h"

class nsClientSprite : public nsSprite {
public:
    int clientId = 0;

    nsClientSprite();
};
