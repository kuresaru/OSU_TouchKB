#include "usb_desc.h"

/* USB Standard Device Descriptor */ //USB设备描述符 https://www.cnblogs.com/wjgaas/p/3868739.html
const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
{
  0x12,                       /*bLength */
  USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
  0x00,                       /*bcdUSB */
  0x02,
  0x00,                       /*bDeviceClass*/
  0x00,                       /*bDeviceSubClass*/
  0x00,                       /*bDeviceProtocol*/
  0x40,                       /*bMaxPacketSize 64*/
  0x83,                       /*idVendor (0x0483)*/
  0x04,
  0x10,                       /*idProduct = 0x5710*/
  0x57,
  0x00,                       /*bcdDevice rel. 2.00*/
  0x02,
  1,                          /*Index of string descriptor describing
                                                manufacturer */
  2,                          /*Index of string descriptor describing
                                                product*/
  3,                          /*Index of string descriptor describing the
                                                device serial number */
  0x01                        /*bNumConfigurations*/
}; /* Joystick_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Joystick_ConfigDescriptor[CONFIG_DESC_SIZ] =
{
  //USB配置描述符
  0x09, /* bLength: Configuration Descriptor size */
  USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
  /* wTotalLength: Bytes returned */
  CONFIG_DESC_SIZ,
  0x00,
  0x02,         /*bNumInterfaces*/ //两个接口
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
                                    the configuration*/
  0xE0,         /*bmAttributes: Self powered */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/
  /* 09 */

  //USB接口描述符
    //第一个接口 键盘
      0x09,         /*bLength: Interface Descriptor size*/
      USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
      0x00,         /*bInterfaceNumber: Number of Interface*/
      0x00,         /*bAlternateSetting: Alternate setting*/
      0x02,         /*bNumEndpoints*/
      0x03,         /*bInterfaceClass: HID*/
      0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
      0x01,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
      0,            /*iInterface: Index of string descriptor*/
      /* 18 */
      //HID描述符
        0x09,         /*bLength: HID Descriptor size*/
        HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
        0x10,         /*bcdHID: HID Class Spec release number*/
        0x01,
        0x21,         /*bCountryCode: Hardware target country*/
        0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
        0x22,         /*bDescriptorType*/
        KEYBOARD_REPORT_DESC_SIZ,/*wItemLength: Total length of Report descriptor*/
        0x00,
        /* 27 */
      //输入端点描述符
        0x07,          /*bLength: Endpoint Descriptor size*/
        USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/
        0x81,          /*bEndpointAddress: Endpoint Address (IN)*/
        0x03,          /*bmAttributes: Interrupt endpoint*/
        0x10,          /*wMaxPacketSize: 16 Byte max */
        0x00,
        0x01,          /*bInterval: Polling Interval (10 ms)*/
        /* 34 */
      //输出端点描述符
        0x07,          /*bLength: Endpoint Descriptor size*/
        USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/
        0x01,          /*bEndpointAddress: Endpoint Address (OUT)*/
        0x03,          /*bmAttributes: Interrupt endpoint*/
        0x10,          /*wMaxPacketSize: 16 Byte max */
        0x00,
        0x01,          /*bInterval: Polling Interval (10 ms)*/
        /* 41 */
    //第二个接口 鼠标
      0x09,         /*bLength: Interface Descriptor size*/
      USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
      0x01,         /*bInterfaceNumber: Number of Interface*/
      0x00,         /*bAlternateSetting: Alternate setting*/
      0x01,         /*bNumEndpoints*/
      0x03,         /*bInterfaceClass: HID*/
      0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
      0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
      0,            /*iInterface: Index of string descriptor*/
      /* 50 */
      //HID描述符
        0x09,         /*bLength: HID Descriptor size*/
        HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
        0x00,         /*bcdHID: HID Class Spec release number*/
        0x01,
        0x00,         /*bCountryCode: Hardware target country*/
        0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
        0x22,         /*bDescriptorType*/
        MOUSE_REPORT_DESC_SIZ,/*wItemLength: Total length of Report descriptor*/
        0x00,
        /* 59 */
      //输入端点描述符
        0x07,          /*bLength: Endpoint Descriptor size*/
        USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/
        0x82,          /*bEndpointAddress: Endpoint Address (IN)*/
        0x03,          /*bmAttributes: Interrupt endpoint*/
        0x40,          /*wMaxPacketSize: 64 Byte max */
        0x00,
        0x0A,          /*bInterval: Polling Interval (10 ms)*/
        /* 66 */
};

//键盘的报告描述符
const uint8_t Keyboard_ReportDescriptor[KEYBOARD_REPORT_DESC_SIZ] =
{
  0x05,0x01,          /*Usage Page(Generic Desktop)*/
  0x09,0x06,          /*Usage(KB)*/
  0xA1,0x01,          /*Collection(Application)*/
  0x05,0x07,          /*Usage(KB)*/
  /* 8 */
  0x19,0xE0,
  0x29,0xE7,
  0x15,0x00,
  0x25,0x01,
  /* 16 */
  0x75,0x01,
  0x95,0x08,
  0x81,0x02,
  0x95,0x01,
  0x75,0x08,
  0x81,0x03,
  0x95,0x05,
  0x75,0x01,
  /* 32 */
  0x05,0x08,
  0x19,0x01,
  0x29,0x05,
  0x91,0x02,
  0x95,0x01,
  0x75,0x03,
  0x91,0x03,
  0x95,0x06,
  /* 48 */
  0x75,0x08,
  0x15,0x00,
  0x25,0x65,
  0x05,0x07,
  /* 56 */
  0x19,0x00,
  0x29,0x65,
  0x81,0x00,
  0xC0
  /* 63 */
};

//鼠标的报告描述符
const uint8_t Mouse_ReportDescriptor[MOUSE_REPORT_DESC_SIZ] = {
  0x05,          /*Usage Page(Generic Desktop)*/
  0x01,
  0x09,          /*Usage(Mouse)*/
  0x02,
  0xA1,          /*Collection(Logical)*/
  0x01,
  0x09,          /*Usage(Pointer)*/
  0x01,
  /* 8 */
  0xA1,          /*Collection(Linked)*/
  0x00,
  0x05,          /*Usage Page(Buttons)*/
  0x09,
  0x19,          /*Usage Minimum(1)*/
  0x01,
  0x29,          /*Usage Maximum(3)*/
  0x03,
  /* 16 */
  0x15,          /*Logical Minimum(0)*/
  0x00,
  0x25,          /*Logical Maximum(1)*/
  0x01,
  0x95,          /*Report Count(3)*/
  0x03,
  0x75,          /*Report Size(1)*/
  0x01,
  /* 24 */
  0x81,          /*Input(Variable)*/
  0x02,
  0x95,          /*Report Count(1)*/
  0x01,
  0x75,          /*Report Size(5)*/
  0x05,
  0x81,          /*Input(Constant,Array)*/
  0x01,
  /* 32 */
  0x05,          /*Usage Page(Generic Desktop)*/
  0x01,
  0x09,          /*Usage(X axis)*/
  0x30,
  0x09,          /*Usage(Y axis)*/
  0x31,
  0x09,          /*Usage(Wheel)*/
  0x38,
  /* 40 */
  0x15,          /*Logical Minimum(-127)*/
  0x81,
  0x25,          /*Logical Maximum(127)*/
  0x7F,
  0x75,          /*Report Size(8)*/
  0x08,
  0x95,          /*Report Count(3)*/
  0x03,
  /* 48 */
  0x81,          /*Input(Variable, Relative)*/
  0x06,
  0xC0,          /*End Collection*/
  0x09,
  0x3c,
  0x05,
  0xff,
  0x09,
  /* 56 */
  0x01,
  0x15,
  0x00,
  0x25,
  0x01,
  0x75,
  0x01,
  0x95,
  /* 64 */
  0x02,
  0xb1,
  0x22,
  0x75,
  0x06,
  0x95,
  0x01,
  0xb1,
  /* 72 */
  0x01,
  0xc0
};

/* USB String Descriptors (optional) */
const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
  {
    JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =
  {
    JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
  {
    JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'J', 0,
    'o', 0, 'y', 0, 's', 0, 't', 0, 'i', 0, 'c', 0, 'k', 0
  };
uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
  {
    JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0
  };
