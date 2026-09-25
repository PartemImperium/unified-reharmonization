#pragma once

struct KeyPressFrame {
    private:
        unsigned char* RawFrame;
        int RawSize;

        void parseIsValidFrame();

        void parseKey();

        void parseDeviceSlot();

    public:
        bool IsValidFrame;
        ButtonType Key;
        unsigned short DeviceSlot;

        KeyPressFrame() {
            IsValidFrame = false;
        }

        KeyPressFrame(unsigned char* _frame, int _size) {
            RawFrame = _frame;
            RawSize = _size;

            parseKey();
            parseDeviceSlot();
        }

        void outputDeviceSlot();

        void outputRawFrame();

        void outputKey();
};