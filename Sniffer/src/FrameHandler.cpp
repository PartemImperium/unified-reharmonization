#include "../include/libunifireharm.h"

#include <libusb-1.0/libusb.h>

KeyPressFrame FrameHandler::listenForFrame(int timeout) {
    libusb_error returnCode;
    returnCode = (libusb_error) libusb_interrupt_transfer(
        device_handle,
        iface_desc->endpoint[ENDPOINT_INDEX].bEndpointAddress,
        data,
        sizeof(data),
        &actual_length,
        timeout);

    return KeyPressFrame(data, actual_length, returnCode);
}
