#pragma once

#include <queue>

#include "libunifireharm.h"

struct UnifiedReharmonizer {
    private:
        FrameHandler Handler;
        std::queue<KeyPress> QueuedKeyPresses;
        KeyPress ActiveFirstRegisterPresses[5];
        KeyPress ActiveThirdRegisterPresses[2];

        bool hasPendingKeyPress();
    public:
        KeyPress listenForKey();
};
