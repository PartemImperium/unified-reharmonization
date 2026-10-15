#pragma once

#include <queue>
#include <vector>
#include <map>

#include "libunifireharm.h"

struct UnifiedReharmonizer {
    private:
        FrameHandler Handler;
        std::queue<KeyPress> QueuedKeyPresses;
        std::map<int,std::map<int,std::vector<PendingKeyPress>>> PendingKeys;

        bool hasPendingKeyPress();

    public:
        KeyPress listenForKey();
};
