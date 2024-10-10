// Copyright (c) 2003-2024, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file AppInfo.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once

#include "Core/AppInfo.h"

class nsGameAppInfo : public IAppInfo {
public:
    const char *GetAppName() override;
    const char *GetDefCfgPath() override;
};