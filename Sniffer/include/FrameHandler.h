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
        unsigned char data[100];
        int actual_length = 0;

        const int CONFIG_DESCRIPTOR_INDEX = 0;
        const int CONFIG_INTERFACE_INDEX = 2;
        const int ALT_SETTINGS_INDEX = 0;
        const int ENDPOINT_INDEX = 0;

        const int UNIFYING_RECEIRVER_VENDOR_ID = 0x46d;
        const int UNIFYING_RECEIRVER_PRODUCT_ID = 0xc52b;
    public:
        FrameHandler() {
            std::cout << "Starting keys sniffer..." << std::endl;

            libusb_init(&ctx);
            libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_WARNING);

            // Look at the keyboard based on vendor and device id
            device_handle = libusb_open_device_with_vid_pid(ctx, UNIFYING_RECEIRVER_VENDOR_ID, UNIFYING_RECEIRVER_PRODUCT_ID);

            std::cout << std::hex;
            std::cout << "Found Harmony Device: " << device_handle << std::endl << std::endl;

            // Get interface
            device = libusb_get_device(device_handle);
            libusb_get_device_descriptor(device, &desc);
            libusb_get_config_descriptor(device, CONFIG_DESCRIPTOR_INDEX, &config);
            iface = &config->interface[CONFIG_INTERFACE_INDEX];
            iface_desc = &iface->altsetting[ALT_SETTINGS_INDEX];

            // Detach & claim interface from kernel driver
            libusb_detach_kernel_driver(device_handle, CONFIG_INTERFACE_INDEX);
            libusb_claim_interface(device_handle, CONFIG_INTERFACE_INDEX);
        }

        ~FrameHandler() {
            std::cout << "Deconstruct";
            // Leave a clean environment
            libusb_release_interface(device_handle, CONFIG_INTERFACE_INDEX);
            libusb_attach_kernel_driver(device_handle, CONFIG_INTERFACE_INDEX);
            libusb_close(device_handle);
            libusb_exit(ctx);
        }

        KeyPressFrame listenForFrame(int timeout);
};