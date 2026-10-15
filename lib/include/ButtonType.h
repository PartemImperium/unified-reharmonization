#pragma once

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
