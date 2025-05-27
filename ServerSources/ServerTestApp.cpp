//
// Created by Roman on 5/27/2025.
//

#include "ServerTestApp.h"

IAppInfo* App_GetInfo() {
    static nsServerTestApp app;
    return &app;
}

const char * nsServerTestApp::GetAppName() {
    return "ServerTestApp";
}

const char * nsServerTestApp::GetDefCfgPath() {
    return nullptr;
}
