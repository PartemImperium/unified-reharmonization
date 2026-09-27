#pragma once

#include <libusb-1.0/libusb.h>

struct KeyPressFrame {
    private:
        unsigned char* RawFrame;
        int RawSize;
        libusb_error ReturnCode;

        void parseIsValidFrame();

        void parseKeys();

        void parseDeviceSlot();

        void parseButtonRegister();

    public:
        bool IsValidFrame;
        ButtonType Keys[5];
        unsigned short DeviceSlot;
        int ButtonRegister;

        KeyPressFrame() {
            IsValidFrame = false;
        }

        KeyPressFrame(unsigned char* _frame, int _size, libusb_error _returnCode) {
            RawFrame = _frame;
            RawSize = _size;
            ReturnCode = _returnCode;

            parseIsValidFrame();
            parseDeviceSlot();
            parseButtonRegister();

            // IMPORTANT: Keep the parse keys at the end. It uses info from the other data in the frame to correctly parse the keys.
            parseKeys();
        }

        void outputButtonRegister();

        void outputDeviceSlot();

        void outputRawFrame();

        void outputKey();
};
