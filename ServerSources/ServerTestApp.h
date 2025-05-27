// Copyright (c) 2003-2025, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ServerTestApp.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#pragma once
#include "Core/AppInfo.h"

class nsServerTestApp : public IAppInfo {
public:
    const char * GetAppName() override;
    const char * GetDefCfgPath() override;
};
