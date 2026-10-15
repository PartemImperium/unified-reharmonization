#include <libusb-1.0/libusb.h>

#include "../include/libunifireharm.h"

bool UnifiedReharmonizer::hasPendingKeyPress() {
    
    for (auto devices : PendingKeys) {
        for (auto registers : devices.second) {
            for (PendingKeyPress key : registers.second) {
                if (key.Press.Type != 0
                    && key.Press.Button != 0) {
                    return true;
                }
            }
        }
    }

    return false;
}

//TODO: Add way to change these vals with some sort of config
const int MULTI_CLICK_TIMEOUT = 250;
const int DEFAULT_TIMEOUT = 10000;

KeyPress UnifiedReharmonizer::listenForKey() {
    KeyPress output;
    int sleepDuration = DEFAULT_TIMEOUT;
    while (QueuedKeyPresses.empty()) {
        bool hasPendingKeys = hasPendingKeyPress();
        
        if (hasPendingKeys) {
            sleepDuration = MULTI_CLICK_TIMEOUT;
        }

        // Listen for key
        KeyPressFrame workingFrame = Handler.listenForFrame(sleepDuration);

        if (workingFrame.IsTimeoutFrame
         && sleepDuration == MULTI_CLICK_TIMEOUT
         && PendingKeys.size() > 0) {//TODO: This size check doesnt help much now that we have the device and register maps.. Fix that later... I never actually implimented this path anyways so can fix it then
            // This is a Multi Click Timeout and there is an active key. 
            // It must have been pressed and is still being held.
            // As such release the KeyPressed event and put the sleepDuration back to default (for the Release event)
        }
        else if (workingFrame.IsValidFrame) {
            if (hasPendingKeys) {

                
                if (workingFrame.IsResetFrame) {
                    // Its a reset frame, push any pending click(s) and the release.
                    for (PendingKeyPress pending : PendingKeys[workingFrame.DeviceSlot][workingFrame.ButtonRegister]) {
                        QueuedKeyPresses.push(pending.Press);
                        KeyPress release(KeyReleased, pending.Press.Button);
                        QueuedKeyPresses.push(release);
                    }

                    //TODO: Clear pending keys that are ONLY the current register.... Other registers could still exist
                    PendingKeys[workingFrame.DeviceSlot][workingFrame.ButtonRegister].clear();
                }
                else if (workingFrame.Keys.size() == 1
                      && PendingKeys[workingFrame.DeviceSlot][workingFrame.ButtonRegister].size() == 1
                      && workingFrame.Keys[0] == PendingKeys[workingFrame.DeviceSlot][workingFrame.ButtonRegister][0].Press.Button) {
                    //Its not a reset frame and both the working frame and the pending keys have 1 key in them
                    PendingKeys[workingFrame.DeviceSlot][workingFrame.ButtonRegister][0].Press.Type = (KeyPressType) (PendingKeys[workingFrame.DeviceSlot][workingFrame.ButtonRegister][0].Press.Type << 1);

                    if (PendingKeys[workingFrame.DeviceSlot][workingFrame.ButtonRegister][0].Press.Type == KeyPressed5x) {

                        
                    }
                }
            }
            else {
                // We dont know about this button yet.
                for (ButtonType button : workingFrame.Keys) {
                    if (button != 0) {
                        KeyPress click(KeyPressed, button);

                        PendingKeyPress pClick(click, workingFrame.DeviceSlot, workingFrame.ButtonRegister);
                        PendingKeys[workingFrame.DeviceSlot][workingFrame.ButtonRegister].push_back(pClick);
                        
                        KeyPress hold(KeyHeldDown, button);
                        QueuedKeyPresses.push(hold);
                    }
                }
            }
        }       
    }

    output = QueuedKeyPresses.front();
    QueuedKeyPresses.pop();

    return output;
};
