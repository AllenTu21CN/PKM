* 运行系统中键值文件目录:/system/usr/keylayout

* AOSP中键值文件目录：frameworks/base/data/keyboards

* 查看系统中所有的总线输入设备：cat /proc/bus/input/devices，可以获取到设备的Name/Vendor/Product/Version/Uniq等信息

* 根据设备的Vendor/Product/Version找到系统中使用的设备键值kl文件，找不到则使用默认的Generic.kl

* getevent -l命令实时获取输入的HID键索引号，在kernel/drivers/hid/hid-input.c中，通过hid_keyboard数组的索引号对应的键值；或者直接查看[USB HID Usages](http://www.freebsddiary.org/APC/usb_hid_usages.php)通过索引查找即可

```shell
/dev/input/event4: EV_MSC       MSC_SCAN             0007004a            
/dev/input/event4: EV_KEY       KEY_HOME             DOWN                
/dev/input/event4: EV_SYN       SYN_REPORT           00000000            
/dev/input/event4: EV_MSC       MSC_SCAN             0007004a // 0x4a则为HID键索引号 -> HID值为102
/dev/input/event4: EV_KEY       KEY_HOME             UP                  
/dev/input/event4: EV_SYN       SYN_REPORT           00000000     
```

```txt
hid_keyboard: {
0: 0, 1: 0, 2: 0, 3: 0, 4: 30, 5: 48, 6: 46, 7: 32, 8: 18, 9: 33, 10: 34, 11: 35, 12: 23, 13: 36, 14: 37, 15: 38, 16: 50, 
17: 49, 18: 24, 19: 25, 20: 16, 21: 19, 22: 31, 23: 20, 24: 22, 25: 47, 26: 17, 27: 45, 28: 21, 29: 44, 30: 2, 31: 3, 32: 4, 
33: 5, 34: 6, 35: 7, 36: 8, 37: 9, 38: 10, 39: 11, 40: 28, 41: 1, 42: 14, 43: 15, 44: 57, 45: 12, 46: 13, 47: 26, 48: 27, 
49: 43, 50: 43, 51: 39, 52: 40, 53: 41, 54: 51, 55: 52, 56: 53, 57: 58, 58: 59, 59: 60, 60: 61, 61: 62, 62: 63, 63: 64, 
64: 65, 65: 66, 66: 67, 67: 68, 68: 87, 69: 88, 70: 99, 71: 70, 72: 119, 73: 110, 74: 102, 75: 104, 76: 111, 77: 107, 
78: 109, 79: 106, 80: 105, 81: 108, 82: 103, 83: 69, 84: 98, 85: 55, 86: 74, 87: 78, 88: 96, 89: 79, 90: 80, 91: 81, 
92: 75, 93: 76, 94: 77, 95: 71, 96: 72, 97: 73, 98: 82, 99: 83, 100: 86, 101: 127, 102: 116, 103: 117, 104: 183, 105: 184, 
106: 185, 107: 186, 108: 187, 109: 188, 110: 189, 111: 190, 112: 191, 113: 192, 114: 193, 115: 194, 116: 134, 117: 138, 
118: 130, 119: 132, 120: 128, 121: 129, 122: 131, 123: 137, 124: 133, 125: 135, 126: 136, 127: 113, 128: 115, 129: 114, 
133: 121, 135: 89, 136: 93, 137: 124, 138: 92, 139: 94, 140: 95, 144: 122, 145: 123, 146: 90, 147: 91, 148: 85, 156: 111, 
182: 179, 183: 180, 216: 111, 224: 29, 225: 42, 226: 56, 227: 125, 228: 97, 229: 54, 230: 100, 231: 126, 232: 164, 233: 166, 
234: 165, 235: 163, 236: 161, 237: 115, 238: 114, 239: 113, 240: 150, 241: 158, 242: 159, 243: 128, 244: 136, 245: 177, 
246: 178, 247: 176, 248: 142, 249: 152, 250: 173, 251: 140
}

如下文件中可以根据HID值(102)对应的键位KEY_HOME
./include/uapi/linux/input-event-codes.h
./include/dt-bindings/input/rk-input.h
./include/dt-bindings/input/linux-event-codes.h
./arch/arm/boot/dts/include/dt-bindings/input/rk-input.h
./arch/mips/boot/dts/include/dt-bindings/input/rk-input.h
./arch/powerpc/boot/dts/include/dt-bindings/input/rk-input.h
./arch/arm64/boot/dts/include/dt-bindings/input/rk-input.h
./arch/metag/boot/dts/include/dt-bindings/input/rk-input.h
./arch/cris/boot/dts/include/dt-bindings/input/rk-input.h
./arch/arm/boot/dts/imx53-ard.dts
./drivers/macintosh/adbhid.c
./drivers/staging/unisys/visorinput/visorinput.c
```

```txt
Keyboard
0x00: Reserved (no event indicated)
0x01: Keyboard ErrorRollOver
0x02: Keyboard POSTFail
0x03: Keyboard ErrorUndefined
0x04: Keyboard a and A
0x05: Keyboard b and B
0x06: Keyboard c and C
0x07: Keyboard d and D
0x08: Keyboard e and E
0x09: Keyboard f and F
0x0A: Keyboard g and G
0x0B: Keyboard h and H
0x0C: Keyboard i and I
0x0D: Keyboard j and J
0x0E: Keyboard k and K
0x0F: Keyboard l and L
0x10: Keyboard m and M
0x11: Keyboard n and N
0x12: Keyboard o and O
0x13: Keyboard p and P
0x14: Keyboard q and Q
0x15: Keyboard r and R
0x16: Keyboard s and S
0x17: Keyboard t and T
0x18: Keyboard u and U
0x19: Keyboard v and V
0x1A: Keyboard w and W
0x1B: Keyboard x and X
0x1C: Keyboard y and Y
0x1D: Keyboard z and Z
0x1E: Keyboard 1 and !
0x1F: Keyboard 2 and @
0x20: Keyboard 3 and #
0x21: Keyboard 4 and $
0x22: Keyboard 5 and %
0x23: Keyboard 6 and ^
0x24: Keyboard 7 and &
0x25: Keyboard 8 and *
0x26: Keyboard 9 and (
0x27: Keyboard 0 and )
0x28: Keyboard Return (ENTER)
0x29: Keyboard ESCAPE
0x2A: Keyboard DELETE (Backspace)
0x2B: Keyboard Tab
0x2C: Keyboard Spacebar
0x2D: Keyboard - and (underscore)
0x2E: Keyboard = and +
0x2F: Keyboard [ and {
0x30: Keyboard ] and }
0x31: Keyboard \ and |
0x32: Keyboard Non-US # and ~
0x33: Keyboard ; and :
0x34: Keyboard ' and "
0x35: Keyboard Grave Accent and Tilde
0x36: Keyboard, and <
0x37: Keyboard . and >
0x38: Keyboard / and ?
0x39: Keyboard Caps Lock
0x3A: Keyboard F1
0x3B: Keyboard F2
0x3C: Keyboard F3
0x3D: Keyboard F4
0x3E: Keyboard F5
0x3F: Keyboard F6
0x40: Keyboard F7
0x41: Keyboard F8
0x42: Keyboard F9
0x43: Keyboard F10
0x44: Keyboard F11
0x45: Keyboard F12
0x46: Keyboard PrintScreen
0x47: Keyboard Scroll Lock
0x48: Keyboard Pause
0x49: Keyboard Insert
0x4A: Keyboard Home
0x4B: Keyboard PageUp
0x4C: Keyboard Delete Forward
0x4D: Keyboard End
0x4E: Keyboard PageDown
0x4F: Keyboard RightArrow
0x50: Keyboard LeftArrow
0x51: Keyboard DownArrow
0x52: Keyboard UpArrow
0x53: Keypad Num Lock and Clear
0x54: Keypad /
0x55: Keypad *
0x56: Keypad -
0x57: Keypad +
0x58: Keypad ENTER
0x59: Keypad 1 and End
0x5A: Keypad 2 and Down Arrow
0x5B: Keypad 3 and PageDn
0x5C: Keypad 4 and Left Arrow
0x5D: Keypad 5
0x5E: Keypad 6 and Right Arrow
0x5F: Keypad 7 and Home
0x60: Keypad 8 and Up Arrow
0x61: Keypad 9 and PageUp
0x62: Keypad 0 and Insert
0x63: Keypad . and Delete
0x64: Keyboard Non-US \ and |
0x65: Keyboard Application
0x66: Keyboard Power
0x67: Keypad =
0x68: Keyboard F13
0x69: Keyboard F14
0x6A: Keyboard F15
0x6B: Keyboard F16
0x6C: Keyboard F17
0x6D: Keyboard F18
0x6E: Keyboard F19
0x6F: Keyboard F20
0x70: Keyboard F21
0x71: Keyboard F22
0x72: Keyboard F23
0x73: Keyboard F24
0x74: Keyboard Execute
0x75: Keyboard Help
0x76: Keyboard Menu
0x77: Keyboard Select
0x78: Keyboard Stop
0x79: Keyboard Again
0x7A: Keyboard Undo
0x7B: Keyboard Cut
0x7C: Keyboard Copy
0x7D: Keyboard Paste
0x7E: Keyboard Find
0x7F: Keyboard Mute
0x80: Keyboard Volume Up
0x81: Keyboard Volume Down
0x82: Keyboard Locking Caps Lock
0x83: Keyboard Locking Num Lock
0x84: Keyboard Locking Scroll Lock
0x85: Keypad Comma
0x86: Keypad Equal Sign
0x87: Keyboard International1
0x88: Keyboard International2
0x89: Keyboard International3
0x8A: Keyboard International4
0x8B: Keyboard International5
0x8C: Keyboard International6
0x8D: Keyboard International7
0x8E: Keyboard International8
0x8F: Keyboard International9
0x90: Keyboard LANG1
0x91: Keyboard LANG2
0x92: Keyboard LANG3
0x93: Keyboard LANG4
0x94: Keyboard LANG5
0x95: Keyboard LANG6
0x96: Keyboard LANG7
0x97: Keyboard LANG8
0x98: Keyboard LANG9
0x99: Keyboard Alternate Erase
0x9A: Keyboard SysReq/Attention
0x9B: Keyboard Cancel
0x9C: Keyboard Clear
0x9D: Keyboard Prior
0x9E: Keyboard Return
0x9F: Keyboard Separator
0xA0: Keyboard Out
0xA1: Keyboard Oper
0xA2: Keyboard Clear/Again
0xA3: Keyboard CrSel/Props
0xA4: Keyboard ExSel
0xE0: Keyboard LeftControl
0xE1: Keyboard LeftShift
0xE2: Keyboard LeftAlt
0xE3: Keyboard Left GUI
0xE4: Keyboard RightControl
0xE5: Keyboard RightShift
0xE6: Keyboard RightAlt
0xE7: Keyboard Right GUI
```