#include <linux/hid.h>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "../include/libunifireharm.h"

void KeyPressFrame::parseKey() {
    Key = (ButtonType) ((unsigned short) (RawFrame[HARMONY_KEY_POSITION] << 8) + RawFrame[HARMONY_KEY_POSITION + 1]);
}

void KeyPressFrame::parseDeviceSlot() {
    DeviceSlot = (unsigned short) RawFrame[HARMONY_DEVICE_SLOT_POSITION];
}


void KeyPressFrame::outputDeviceSlot() {
    std::cout << "Device ID => " << DeviceSlot << std::endl;
}

void KeyPressFrame::outputRawFrame() {
    std::cout << "Length:" << RawSize << std::endl;
    
    std::cout << std::hex;
    std::cout << "Full Frame => ";

    for (int i = 0; i < RawSize; i++) {
        std::cout << (unsigned short) RawFrame[i] << "/";
    }

    std::cout << std::endl;
    std::cout << std::dec;
}

void KeyPressFrame::outputKey() {
    switch (Key) {
        case Off:
            std::cout << "Key => Off Button";
            break;
    
        case ActivityMusic:
            std::cout << "Key => Activity Music";
            break;
        case ActivityScreen:
            std::cout << "Key => Activity Screen";
            break;
        case ActivityMovie:
            std::cout << "Key => Activity Movie";
            break;
    
        case SmartPlus:
            std::cout << "Key => Smart Plus";
            break;
        case SmartMinus:
            std::cout << "Key => Smart Minus";
            break;
        case SmartLightTop:
            std::cout << "Key => Light Top";
            break;
        case SmartLightBottom:
            std::cout << "Key => Light Bottom";
            break;
        case SmartOutletTop:
            std::cout << "Key => Outlet Top";
            break;
        case SmartOutletBottom:
            std::cout << "Key => Outlet Bottom";
            break;
    
        case Blue:
            std::cout << "Key => Blue";
            break;
        case Yellow:
            std::cout << "Key => Yellow";
            break;
        case Green:
            std::cout << "Key => Green";
            break;
        case Red:
            std::cout << "Key => Red";
            break;
    
        case Dvr:
            std::cout << "Key => DVR";
            break;
        case Guide:
            std::cout << "Key => Guide";
            break;
        case Info:
            std::cout << "Key => Info";
            break;
    
        case Exit:
            std::cout << "Key => Exit";
            break;
        case Menu:
            std::cout << "Key => Menu";
            break;
    
        case VolumeUp:
            std::cout << "Key => Volume Up";
            break;
        case VolumeDown:
            std::cout << "Key => Volume Down";
            break;
    
        case DPadLeft:
            std::cout << "Key => D-Pad Left";
            break;
        case DPadRight:
            std::cout << "Key => D-Pad Right";
            break;
        case DPadUp:
            std::cout << "Key => D-Pad Up";
            break;
        case DPadDown:
            std::cout << "Key => D-Pad Down";
            break;
    
        case DPadOk:
            std::cout << "Key => D-Pad OK";
            break;
    
        case ChannelUp:
            std::cout << "Key => Channel Up";
            break;
        case ChannelDown:
            std::cout << "Key => Channel Down";
            break;
    
        case Mute:
            std::cout << "Key => Mute";
            break;
        case BackArrow:
            std::cout << "Key => Back Arrow";
            break;
    
        case FastForward:
            std::cout << "Key => Fast Forward";
            break;
        case FastBackward:
            std::cout << "Key => Fast Backward";
            break;
    
        case Play:
            std::cout << "Key => Play";
            break;
        case Pause:
            std::cout << "Key => Pause";
            break;
    
        case Record:
            std::cout << "Key => Record";
            break;
        case Stop:
            std::cout << "Key => Stop";
            break;
    
        case Keypad1:
            std::cout << "Key => 1";
            break;
        case Keypad2:
            std::cout << "Key => 2";
            break;
        case Keypad3:
            std::cout << "Key => 3";
            break;
        case Keypad4:
            std::cout << "Key => 4";
            break;
        case Keypad5:
            std::cout << "Key => 5";
            break;
        case Keypad6:
            std::cout << "Key => 6";
            break;
        case Keypad7:
            std::cout << "Key => 7";
            break;
        case Keypad8:
            std::cout << "Key => 8";
            break;
        case Keypad9:
            std::cout << "Key => 9";
            break;
        case Keypad0:
            std::cout << "Key => 0";
            break;
    
        case KeypadDash:
            std::cout << "Key => Keypad .-";
            break;
        case KeypadE:
            std::cout << "Key => Keypad E";
            break;
    
        default:
            std::cout << std::hex;
            std::cout << "KEY => " << Key << std::endl;
            std::cout << std::dec;
            break;
        }

        std::cout << std::endl;
}
