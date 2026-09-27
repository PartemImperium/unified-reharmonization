#include <linux/hid.h>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "../include/libunifireharm.h"

KeyPress UnifiedReharmonizer::listenForKey() {
    KeyPress output;
    if (QueuedKeyPresses.empty()){
        // Listen for key
        KeyPressFrame workingFrame = Handler.listenForFrame(HARMONY_TIMEOUT);

        if (workingFrame.IsValidFrame) {

        }
        
        return output;
    }
    else {
        output = QueuedKeyPresses.front();
        QueuedKeyPresses.pop();

        return output;
    }
};
