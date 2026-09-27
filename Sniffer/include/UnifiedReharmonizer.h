#pragma once

#include <queue>
#include <vector>

#include "libunifireharm.h"

struct UnifiedReharmonizer {
    private:
        FrameHandler Handler;
        std::queue<KeyPress> QueuedKeyPresses;
        std::vector<KeyPress> ActiveFirstRegisterPresses;
        std::vector<KeyPress> ActiveThirdRegisterPresses;

        bool hasPendingKeyPress();
    public:
        KeyPress listenForKey();
};
