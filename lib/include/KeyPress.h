#pragma once

#include "libunifireharm.h"

struct KeyPress {
    public:
        KeyPressType Type;
        ButtonType Button;

        KeyPress() {}

        KeyPress(KeyPressType type, ButtonType buttonType) {
            Type = type;
            Button = buttonType;
        }
};
