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
 
void outputFrame(unsigned char* _frame, int _size) {
    std::cout << std::hex;
    std::cout << "Full Frame => ";
    for (int i = 0; i < _size; i++) {
        std::cout << (unsigned short) _frame[i] << "/";
    }
    std::cout << std::endl;
    std::cout << std::dec;
}

void outputKey(unsigned char* _frame, int _size) {
    unsigned short key = (unsigned short) (_frame[HARMONY_KEY_POSITION] << 8) + _frame[HARMONY_KEY_POSITION + 1];

    switch (key) {
        case 0xec01:
            std::cout << "Key => Off Button";
            break;

        case 0xe801:
            std::cout << "Key => Activity Music";
            break;
        case 0xed01:
            std::cout << "Key => Activity Screen";
            break;
        case 0xe901:
            std::cout << "Key => Activity Movie";
            break;

        case 0xf00f:
            std::cout << "Key => Smart Plus";
            break;
        case 0xf10f:
            std::cout << "Key => Smart Minus";
            break;
        case 0xf20f:
            std::cout << "Key => Light Top";
            break;
        case 0xf30f:
            std::cout << "Key => Light Bottom";
            break;
        case 0xf40f:
            std::cout << "Key => Outlet Top";
            break;
        case 0xf50f:
            std::cout << "Key => Outlet Bottom";
            break;

        case 0xf401:
            std::cout << "Key => Blue";
            break;
        case 0xf501:
            std::cout << "Key => Yellow";
            break;
        case 0xf601:
            std::cout << "Key => Green";
            break;
        case 0xf701:
            std::cout << "Key => Red";
            break;

        case 0x9a00:
            std::cout << "Key => DVR";
            break;
        case 0x8d00:
            std::cout << "Key => Guide";
            break;
        case 0xff01:
            std::cout << "Key => Info";
            break;

        case 0x9400:
            std::cout << "Key => Exit";
            break;
        case 0x65:
            std::cout << "Key => Menu";
            break;

        case 0xe900:
            std::cout << "Key => Volume Up";
            break;
        case 0xea00:
            std::cout << "Key => Volume Down";
            break;

        case 0x50:
            std::cout << "Key => D-Pad Left";
            break;
        case 0x4f:
            std::cout << "Key => D-Pad Right";
            break;
        case 0x52:
            std::cout << "Key => D-Pad Up";
            break;
        case 0x51:
            std::cout << "Key => D-Pad Down";
            break;

        case 0x58:
            std::cout << "Key => D-Pad OK";
            break;

        case 0x9c00:
            std::cout << "Key => Channel Up";
            break;
        case 0x9d00:
            std::cout << "Key => Channel Down";
            break;

        case 0xe200:
            std::cout << "Key => Mute";
            break;
        case 0x2402:
            std::cout << "Key => Back Arrow";
            break;

        case 0xb300:
            std::cout << "Key => Fast Forward";
            break;
        case 0xb400:
            std::cout << "Key => Fast Backward";
            break;

        case 0xb000:
            std::cout << "Key => Play";
            break;
        case 0xb100:
            std::cout << "Key => Pause";
            break;

        case 0xb200:
            std::cout << "Key => Record";
            break;
        case 0xb700:
            std::cout << "Key => Stop";
            break;

        case 0x1e:
            std::cout << "Key => 1";
            break;
        case 0x1f:
            std::cout << "Key => 2";
            break;
        case 0x20:
            std::cout << "Key => 3";
            break;
        case 0x21:
            std::cout << "Key => 4";
            break;
        case 0x22:
            std::cout << "Key => 5";
            break;
        case 0x23:
            std::cout << "Key => 6";
            break;
        case 0x24:
            std::cout << "Key => 7";
            break;
        case 0x25:
            std::cout << "Key => 8";
            break;
        case 0x26:
            std::cout << "Key => 9";
            break;
        case 0x27:
            std::cout << "Key => 0";
            break;

        case 0x56:
            std::cout << "Key => Keypad .-";
            break;
        case 0x28:
            std::cout << "Key => Keypad E";
            break;
            default:
            std::cout << std::hex;
            std::cout << "KEY => " << key << std::endl;
            std::cout << std::dec;
            break;
        }
        
        std::cout << std::endl;
}

void outputDeviceSlot(unsigned char* _frame, int _size) {
    unsigned short deviceSlot = (unsigned short) _frame[HARMONY_DEVICE_SLOT_POSITION];

    std::cout << "Device ID => " << deviceSlot << std::endl;
}

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
        if (next == 'y')
            std::cout << "Press a Key" << std::endl;
 
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
            std::cout << "Length:" << actual_length << std::endl;
            // Key Frame
            outputFrame(data, actual_length);
            // Button value
            outputKey(data, actual_length);
            // Output Map
            outputDeviceSlot(data, actual_length);
            std::cout << std::endl;
            // Continue?
            std::cout << "Next y or ~y?" << std::endl;
            std::cin >> next;
        }
        // Not a Key Value Frame
        else
            next = 'c'; // Continue
    } while ((next == 'y') || (next == 'c'));
 
    // Leave a clean environment
    libusb_release_interface(device_handle, HARMONY_INTERFACE_INDEX);
    libusb_attach_kernel_driver(device_handle, HARMONY_INTERFACE_INDEX);
    libusb_close(device_handle);
    libusb_exit(ctx);
 
    return 0;
}