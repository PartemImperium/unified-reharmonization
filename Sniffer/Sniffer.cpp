//============================================================================
// Name        : HarmonyInput.cpp
// Author      : Watea
// Version     :
//============================================================================
 
#include <libusb-1.0/libusb.h>
#include <iostream>

#include "include/libunifireharm.h"

int main() {
    char next = 'y';
    int index = 0;

    FrameHandler handler;
    KeyPressFrame keyFrame;

    do {
        if (next == 'y') {
            std::cout << "Press a Key" << std::endl;
        }
 
        keyFrame = handler.listenForFrame(10000);
        // Key Value received (Key Release ignored here)
        // Note: HARMONY REMOTE seems to send over data; some false positive happen, to ignore in this bench
        if (keyFrame.IsValidFrame) {

            std::cout << std::endl;
            std::cout << "Index:" << index++ << std::endl;
            

            // Output the various info from the key press frame.
            keyFrame.outputRawFrame();
            keyFrame.outputKey();
            keyFrame.outputDeviceSlot();
            keyFrame.outputButtonRegister();
            
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