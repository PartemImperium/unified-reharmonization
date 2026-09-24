#pragma once

struct KeyPressFrame {
    private:
        unsigned char* RawFrame;
        int RawSize;

        void parseKey();

        void parseDeviceSlot();

    public:
        ButtonType Key;
        unsigned short DeviceSlot;

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