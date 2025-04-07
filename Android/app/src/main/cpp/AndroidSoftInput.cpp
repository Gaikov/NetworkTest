//
// Created by Roman on 5/24/2024.
//
#include "AndroidSoftInput.h"
#include "nsLib/log.h"

AndroidSoftInput::AndroidSoftInput(JavaObject::sp_t activity) :
        _activity(activity) {

}

void AndroidSoftInput::Show() {

    auto method = _activity->BeginMethod("showSoftInput", "()V");
    _activity->GetEnv()->CallVoidMethod(_activity->GetObject(), method);
    _activity->EndMethod();

    _active = true;
}

void AndroidSoftInput::Hide() {
    auto method = _activity->BeginMethod("hideSoftInput", "()V");
    _activity->GetEnv()->CallVoidMethod(_activity->GetObject(), method);
    _activity->EndMethod();

    _active = false;
}

bool AndroidSoftInput::IsActive() {
    return _active;
}

