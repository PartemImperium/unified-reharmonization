//============================================================================
// Name        : HarmonyInput.cpp
// Author      : Watea
// Version     :
//============================================================================
 
#include <linux/hid.h>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "include/libunifireharm.h"

int main() {
    char next = 'y';
    int index = 0;

    UnifiedReharmonizer reharm;
    KeyPressFrame keyFrame;

    do {
        if (next == 'y') {
            std::cout << "Press a Key" << std::endl;
        }
 
        keyFrame = reharm.listenForFrame();
        // Key Value received (Key Release ignored here)
        // Note: HARMONY REMOTE seems to send over data; some false positive happen, to ignore in this bench
        if (keyFrame.IsValidFrame) {

            std::cout << std::endl;
            std::cout << "Index:" << index++ << std::endl;
            

            // Output the various info from the key press frame.
            keyFrame.outputRawFrame();
            keyFrame.outputKey();
            keyFrame.outputDeviceSlot();

            std::cout << std::endl;
            // Continue?
            std::cout << "Next y or ~y?" << std::endl;
            std::cin >> next;
        }
        // Not a Key Value Frame
        else
        { 
            next = 'c'; // Continue
        }
    } while ((next == 'y') || (next == 'c'));
 
    return 0;
}