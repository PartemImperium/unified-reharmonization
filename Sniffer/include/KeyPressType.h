# pragma once

enum KeyPressType {
    KeyPressed   = 1 << 0,
    KeyPressed2x = 1 << 1,
    KeyPressed3x = 1 << 2,
    KeyPressed4x = 1 << 3,
    KeyPressed5x = 1 << 5,
    KeyHeldDown  = 1 << 6,
    KeyReleased  = 1 << 7,
};
