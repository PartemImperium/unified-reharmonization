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