//
// Created by Roman on 6/4/2025.
//

#include "ClientSprite.h"
#include "Engine/RenManager.h"
#include "Engine/utils/AppUtils.h"

nsClientSprite::nsClientSprite() {
    desc.tex = _device->TextureLoad("textures/client.png");
    desc.ComputeCenter();
    renState = _device->StateLoad("default/rs/gui_clamp.txt");
    desc.color.Rand();

    auto size = nsAppUtils::GetClientSize();

    nsVec2 pos;
    pos.Random(200);
    origin.pos = size / 2 + pos;
}
