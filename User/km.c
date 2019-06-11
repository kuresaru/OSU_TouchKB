#include "km.h"
#include "usb_sil.h"
#include "usb_regs.h"

__IO u8 flagSent = 0xFF;
__IO u8 KB_LED = 0;

void Mouse_Send(u8 key, u8 x, u8 y, u8 wheel) {
    if (flagSent & FLAG_MOUSE_SENT) {
        flagSent &= ~FLAG_MOUSE_SENT;
        u8 buf[] = {key, x, y, wheel};
        USB_SIL_Write(EP2_IN, buf, 4);
        SetEPTxValid(ENDP2);
    }
}

void Mouse_SendReset() {
    Mouse_Send(0, 0, 0, 0);
}

void Keyboard_Send(u8 special, u8 key1, u8 key2, u8 key3, u8 key4, u8 key5, u8 key6) {
    if (flagSent & FLAG_KEYBOARD_SENT) {
        flagSent &= ~FLAG_KEYBOARD_SENT;
        u8 buf[] = {special, 0, key1, key2, key3, key4, key5, key6};
        USB_SIL_Write(EP1_IN, buf, 8);
        SetEPTxValid(ENDP1);
    }
}

void Keyboard_SendReset() {
    Keyboard_Send(0, 0, 0, 0, 0, 0, 0);
}

/*BYTE1 --
    |--bit7:   1   表示 Y 坐标的变化量超出－256~255的范围，0表示没有溢出
    |--bit6:   1   表示 X 坐标的变化量超出－256~255的范围，0表示没有溢出 
    |--bit5:   Y   坐标变化的符号位，1表示负数，即鼠标向下移动 
    |--bit4:   X   坐标变化的符号位，1表示负数，即鼠标向左移动 
    |--bit3:   恒为1 
    |--bit2:   1表示中键按下 
    |--bit1:   1表示右键按下 
    |--bit0:   1表示左键按下 
BYTE2 -- X坐标变化量，与byte的bit4组成9位符号数，负数表示向左移，正数表右移。用补码表示变化量 
BYTE3 -- Y坐标变化量，与byte的bit5组成9位符号数，负数表示向下移，正数表上移。用补码表示变化量
BYTE4 -- 滚轮变化。*/
