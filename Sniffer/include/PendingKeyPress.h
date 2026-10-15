#pragma once

#include "KeyPress.h"

struct PendingKeyPress {
    public:
        KeyPress Press;
        int DeviceId;
        int KeyRegister;

        PendingKeyPress(KeyPress press, int deviceId, int keyRegister) {
            Press = press;
            DeviceId = deviceId;
            KeyRegister = keyRegister;
        }
};