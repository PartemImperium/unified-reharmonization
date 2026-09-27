#include <linux/hid.h>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "../include/libunifireharm.h"

bool UnifiedReharmonizer::hasPendingKeyPress() {
    for (KeyPress key : ActiveFirstRegisterPresses) {
        if (key.Type != 0
         && key.Button != 0) {
            return true;
        }
    }

    for (KeyPress key : ActiveThirdRegisterPresses) {
        if (key.Type != 0
         && key.Button != 0) {
            return true;
        }
    }

    return false;
}

KeyPress UnifiedReharmonizer::listenForKey() {
    KeyPress output;
    while (QueuedKeyPresses.empty()){
        // Listen for key
        int sleepDuration = 10000;
        if (hasPendingKeyPress()){

        }
        KeyPressFrame workingFrame = Handler.listenForFrame(10000);

        if (workingFrame.IsValidFrame) {

        }
        
       
    }

    output = QueuedKeyPresses.front();
    QueuedKeyPresses.pop();

    return output;
};
