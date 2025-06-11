//
// Created by Roman on 10/10/2024.
//

#include "GameAppInfo.h"

static nsGameAppInfo g_info;

IAppInfo *App_GetInfo()
{
    return &g_info;
}

const char *nsGameAppInfo::GetAppName() {
    return "network_template";
}

const char *nsGameAppInfo::GetDefCfgPath() {
    return nullptr;
}
