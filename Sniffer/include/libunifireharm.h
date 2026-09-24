#pragma once

#include "ButtonType.h"
#include "KeyPressFrame.h"

// HARMONY USB interface, thanks to USB sniffer
#define HARMONY_CONFIG_INDEX           0
#define HARMONY_INTERFACE_INDEX        2
#define HARMONY_ALT_SETTING_INDEX      0
#define HARMONY_ENDPOINT_INDEX         0
#define HARMONY_VENDOR_ID              0x46d
#define HARMONY_PRODUCT_ID             0xc52b
#define HARMONY_TIMEOUT                10000
#define HARMONY_MAX_MSG_LENGTH         100
#define HARMONY_KEY_POSITION           3 // Found by sniffing
#define HARMONY_DEVICE_SLOT_POSITION   1 // Found by sniffing
