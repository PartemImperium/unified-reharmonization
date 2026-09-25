#include "../include/libunifireharm.h"

KeyPressFrame UnifiedReharmonizer::listenForFrame() {
    libusb_interrupt_transfer(
        device_handle,
        iface_desc->endpoint[HARMONY_ENDPOINT_INDEX].bEndpointAddress,
        data,
        sizeof(data),
        &actual_length,
        HARMONY_TIMEOUT);

    return KeyPressFrame(data, actual_length);
}