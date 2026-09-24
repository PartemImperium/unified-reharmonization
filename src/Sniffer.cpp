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
 
// HARMONY USB interface, thanks to USB sniffer
#define HARMONY_CONFIG_INDEX           0
#define HARMONY_INTERFACE_INDEX        2
#define HARMONY_ALT_SETTING_INDEX      0
#define HARMONY_ENDPOINT_INDEX         0
#define HARMONY_VENDOR_ID              0x46d
#define HARMONY_PRODUCT_ID             0xc52b
#define HARMONY_TIMEOUT                10000
#define HARMONY_MAX_MSG_LENGTH         100
#define HARMONY_KEY_POSITION           3 // Found by sniffing
#define HARMONY_DEVICE_SLOT_POSITION   1 // Found by sniffing


enum ButtonType : unsigned short {
    Off = 0xec01,

    ActivityMusic = 0xe801,
    ActivityScreen = 0xed01,
    ActivityMovie = 0xe901,

    SmartPlus = 0xf00f,
    SmartMinus = 0xf10f,
    SmartLightTop = 0xf20f,
    SmartLightBottom = 0xf30f,
    SmartOutletTop = 0xf40f,
    SmartOutletBottom = 0xf50f,

    Blue = 0xf401,
    Yellow = 0xf501,
    Green = 0xf601,
    Red = 0xf701,

    Dvr = 0x9a00,
    Guide = 0x8d00,
    Info = 0xff01,

    Exit = 0x9400,
    Menu = 0x65,

    VolumeUp = 0xe900,
    VolumeDown = 0xea00,

    DPadLeft = 0x50,
    DPadRight = 0x4f,
    DPadUp = 0x52,
    DPadDown = 0x51,

    DPadOk = 0x58,

    ChannelUp = 0x9c00,
    ChannelDown = 0x9d00,

    Mute = 0xe200,
    BackArrow = 0x2402,

    FastForward = 0xb300,
    FastBackward = 0xb400,

    Play = 0xb000,
    Pause = 0xb100,

    Record = 0xb200,
    Stop = 0xb700,

    Keypad1 = 0x1e,
    Keypad2 = 0x1f,
    Keypad3 = 0x20,
    Keypad4 = 0x21,
    Keypad5 = 0x22,
    Keypad6 = 0x23,
    Keypad7 = 0x24,
    Keypad8 = 0x25,
    Keypad9 = 0x26,
    Keypad0 = 0x27,

    KeypadDash = 0x56,
    KeypadE = 0x28,
};

struct KeyPressFrame {
    private:
        unsigned char* RawFrame;
        int RawSize;

        void parseKey() {
            Key = (ButtonType) ((unsigned short) (RawFrame[HARMONY_KEY_POSITION] << 8) + RawFrame[HARMONY_KEY_POSITION + 1]);
        }

        void parseDeviceSlot() {
            DeviceSlot = (unsigned short) RawFrame[HARMONY_DEVICE_SLOT_POSITION];
        }

    public:
        ButtonType Key;
        unsigned short DeviceSlot;

        KeyPressFrame(unsigned char* _frame, int _size) {
            RawFrame = _frame;
            RawSize = _size;

            parseKey();
            parseDeviceSlot();
        }

        void outputDeviceSlot() {
            std::cout << "Device ID => " << DeviceSlot << std::endl;
        }

        void outputRawFrame() {
            std::cout << "Length:" << RawSize << std::endl;
            
            std::cout << std::hex;
            std::cout << "Full Frame => ";

            for (int i = 0; i < RawSize; i++) {
                std::cout << (unsigned short) RawFrame[i] << "/";
            }

            std::cout << std::endl;
            std::cout << std::dec;
        }

        void outputKey() {
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

};

int main() {
    libusb_context *ctx;
    struct libusb_device_descriptor desc;
    struct libusb_config_descriptor *config;
 
    std::cout << "Starting keys sniffer..." << std::endl;
 
    libusb_init(&ctx);
    libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_WARNING);
 
    // Look at the keyboard based on vendor and device id
    libusb_device_handle *device_handle = libusb_open_device_with_vid_pid(ctx, HARMONY_VENDOR_ID, HARMONY_PRODUCT_ID);
 
    std::cout << std::hex;
    std::cout << "Found Harmony Device: " << device_handle << std::endl << std::endl;
 
    // Get interface
    libusb_device *device = libusb_get_device(device_handle);
    libusb_get_device_descriptor(device, &desc);
    libusb_get_config_descriptor(device, HARMONY_CONFIG_INDEX, &config);
    const struct libusb_interface *iface = &config->interface[HARMONY_INTERFACE_INDEX];
    const struct libusb_interface_descriptor *iface_desc = &iface->altsetting[HARMONY_ALT_SETTING_INDEX];
 
    // Detach & claim interface from kernel driver
    libusb_detach_kernel_driver(device_handle, HARMONY_INTERFACE_INDEX);
    libusb_claim_interface(device_handle, HARMONY_INTERFACE_INDEX);
 
    // Bench for reading HARMONY Keys (Button Press)
    unsigned char data[HARMONY_MAX_MSG_LENGTH];
    int actual_length = 0;
    int index = 0;
    char next = 'y';
 
    do {
        if (next == 'y') {
            std::cout << "Press a Key" << std::endl;
        }
 
        libusb_interrupt_transfer(
            device_handle,
            iface_desc->endpoint[HARMONY_ENDPOINT_INDEX].bEndpointAddress,
            data,
            sizeof(data),
            &actual_length,
            HARMONY_TIMEOUT);
 
        // Key Value received (Key Release ignored here)
        // Note: HARMONY REMOTE seems to send over data; some false positive happen, to ignore in this bench
        if ((actual_length > 0) &&
            (data[HARMONY_KEY_POSITION] + data[HARMONY_KEY_POSITION + 1] != 0)) {
            std::cout << std::endl;
            std::cout << "Index:" << index++ << std::endl;
            

            KeyPressFrame f(data, actual_length);

            // Output the various info from the key press frame.
            f.outputRawFrame();
            f.outputKey();
            f.outputDeviceSlot();

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
 
    // Leave a clean environment
    libusb_release_interface(device_handle, HARMONY_INTERFACE_INDEX);
    libusb_attach_kernel_driver(device_handle, HARMONY_INTERFACE_INDEX);
    libusb_close(device_handle);
    libusb_exit(ctx);
 
    return 0;
}