#pragma once

#include <linux/hid.h>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "libunifireharm.h"

struct FrameHandler {

    private:
    
        libusb_context *ctx;
        struct libusb_device_descriptor desc;
        struct libusb_config_descriptor *config;
        libusb_device_handle *device_handle;
        libusb_device *device;
        const struct libusb_interface *iface;
        const struct libusb_interface_descriptor *iface_desc;

        // Bench for reading HARMONY Keys (Button Press)
        unsigned char data[HARMONY_MAX_MSG_LENGTH];
        int actual_length = 0;
    public:
        FrameHandler() {
            std::cout << "Starting keys sniffer..." << std::endl;

            libusb_init(&ctx);
            libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_WARNING);

            // Look at the keyboard based on vendor and device id
            device_handle = libusb_open_device_with_vid_pid(ctx, HARMONY_VENDOR_ID, HARMONY_PRODUCT_ID);

            std::cout << std::hex;
            std::cout << "Found Harmony Device: " << device_handle << std::endl << std::endl;

            // Get interface
            device = libusb_get_device(device_handle);
            libusb_get_device_descriptor(device, &desc);
            libusb_get_config_descriptor(device, HARMONY_CONFIG_INDEX, &config);
            iface = &config->interface[HARMONY_INTERFACE_INDEX];
            iface_desc = &iface->altsetting[HARMONY_ALT_SETTING_INDEX];

            // Detach & claim interface from kernel driver
            libusb_detach_kernel_driver(device_handle, HARMONY_INTERFACE_INDEX);
            libusb_claim_interface(device_handle, HARMONY_INTERFACE_INDEX);
        }

        ~FrameHandler() {
            std::cout << "Deconstruct";
            // Leave a clean environment
            libusb_release_interface(device_handle, HARMONY_INTERFACE_INDEX);
            libusb_attach_kernel_driver(device_handle, HARMONY_INTERFACE_INDEX);
            libusb_close(device_handle);
            libusb_exit(ctx);
        }

        KeyPressFrame listenForFrame(int timeout);
};