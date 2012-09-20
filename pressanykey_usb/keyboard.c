#include "keyboard.h"

static const uint8_t deviceDescriptor[] = {
	0x12,							              //bLength: length of this structure in bytes (18)
	USB_DESC_DEVICE,				        //bDescriptorType: usb device descriptor
	0x00, 0x02,						          //bcdUSB: 0200 (Little Endian) - USB 2.0 compliant
	USB_CLASS_DEVICE,				        //bDeviceClass: Device class (0 = interfaces specify class)
	0x00,							              //bDeviceSubClass: Device subclass (must be 0 if bDeviceClass is 0)
	0x00,							              //bDeviceProtocol: 0 for no specific device-level protocols
	USB_MAX_COMMAND_PACKET_SIZE,	  //bMaxPacketSize0: Max packet size for control endpoint
	0x34, 0x12,                     //idVendor: 16 bit vendor id
	0x78, 0x56,                     //idProduct: 16 bit product id
	0x00, 0x01,						          //bcdDevice: Device release version
	0x01,                           //iManufacturer: Manufacturer string index
	0x02,                           //iProduct: Product string index
	0x03,                           //iSerialNumber: Serial number string index
	0x01                            //bNumConfigurations: Number of configurations
};

static const uint8_t configDescriptor[] = {
	0x09,							      //bLength: length of this descriptor in bytes (9)
	USB_DESC_CONFIGURATION,	//bDescriptorType: configuration descriptor
	0x22, 0x00,						  //wTotalLen: Total length, including attached interface and endpoint descriptors
	0x01,                   //bNumInterfaces: Number of interfaces (1)
	0x01,							      //bConfigurationValue: Number to set to activate this config
	0x00,							      //iConfiguration: configuration string index (0 = not available)
	0x80,							      //bmAttributes: Not self-powered, no remote wakeup
	0x32,							      //bMaxPower: Max power in 2mA steps (0x32 = 50 = 100mA)
	
	// Interface 0: HID
	0x09,           				//bLength: length of this descriptor in bytes (9)
	USB_DESC_INTERFACE,			//bDescriptorType: configuration descriptor
	0x00,							      //bInterfaceNumber: Interface index, 0-based
	0x00,							      //bAlternateSetting
	0x01,							      //bNumEndpoints: Number of endpoints excluding control endpoint
	USB_CLASS_HID,					//bInterfaceClass: interface class
	0x01,							      //bInterfaceSubClass 1 = boot interface (0 for non-boot interface)
	0x01,							      //bInterfaceProtocol 1 = boot keyboard (2 for boot mouse, 0 for all others)
	0x00,							      //iInterface: String index (0x00 = not available)

	// HID descriptor (inserted between interface and endpoints for HID devices)
	0x09,							      //bLength: length of HID descriptor in bytes
	USB_DESC_HID_HID,				//bDescriptorType: HID descriptor
	0x00, 0x01,						  //bcdHID: version 1.0
	0x09,							      //bCountryCode: 9 = German (HID spec 1.11, section 6.2.1 - 0=not supported, 33=US)
	0x01,							      //bNumDescriptors: We have one descriptor
	USB_DESC_HID_REPORT,		//bDescriptorType: It is a report descriptor
	0x3f, 0x00,						  //wDescriptorLength: Length of report descriptor. MUST BE UPDATED WHEN REPORT DESCRIPTOR CHANGES!
	
	// Endpoint descriptor: 1 interrupt in
	0x07,							    //bLength: Length of endpoint descriptor in bytes
	USB_DESC_ENDPOINT,    //bDescriptorType: This is an endpoint descriptor
	0x81,							    //bEndpointAddress: Logical endpoint 1, direction IN
	USB_EPTYPE_INTERRUPT,	//bmAttributesL: Interrput endpoint
	0x08, 0x00,						//wMaxPacketSize: 8 bytes (report size)
	0x0a          				//bInterval: Poll interval in ms
};

static const uint8_t reportDescriptor[] = {
	0x05, 0x01,	// Usage Page (Generic Desktop)
	0x09, 0x06,	// Usage (Keyboard)
	0xa1, 0x01,	// Collection (Application)
	0x75, 0x01,	// Report Size (1)
	0x95, 0x08,	// Report Count (8)
	0x05, 0x07,	// Usage Page (Key Codes)
	0x19, 0xe0,	// Usage Minimum (224)
	0x29, 0xe7,	// Usage Maximum (231)
	0x15, 0x00,	// Logical Minimum (0)
	0x25, 0x01,	// Logical Maximum (1)
	0x81, 0x02,	// Input (Data, Variable, Absolute)
	0x95, 0x01,	// Report Count (1)
	0x75, 0x08,	// Report Size (8)
	0x81, 0x01,	// Input (Constant)
	0x95, 0x05,	// Report Count (5)
	0x75, 0x01,	// Report Size (1)
	0x05, 0x08,	// Usage Page (LEDs)
	0x19, 0x01,	// Usage Minimum (1)
	0x29, 0x05,	// Usage Maximum (5)
	0x91, 0x02,	// Output (Data, Variable, Absolute)
	0x95, 0x01,	// Report Count (1)
	0x75, 0x03,	// Report Size (3)
	0x91, 0x01,	// Output (Constant)
	0x95, 0x06,	// Report Count (6)
	0x75, 0x08,	// Report Size (8)
	0x15, 0x00,	// Logical Minimum (0)
	0x25, 0x65,	// Logical Maximum(101)
	0x05, 0x07,	// Usage Page (Key Codes)
	0x19, 0x00,	// Usage Minimum (0)
	0x29, 0x65,	// Usage Maximum (101)
	0x81, 0x00,	// Input (Data, Array)
	0xc0 		    // End Collection
};

static const uint8_t manufacturerName[] = {
	0x22,							      //bLength: length of this descriptor in bytes (34)
	USB_DESC_STRING,				//bDescriptorType: string descriptor
	'P',0,'r',0,'e',0,'s',0,'s',0,' ',0,'A',0,'n',0,'y',0,' ',0,'K',0,'e',0,'y',0,' ',0,'U',0,'G',0	//bString[]: String (UTF16LE, not terminated)
};

static const uint8_t deviceName[] = {
	0x12,							      //bLength: length of this descriptor in bytes (18)
	USB_DESC_STRING,				//bDescriptorType: string descriptor
	'A',0,'n',0,'y',0,'k',0,'e',0,'y',0,'0',0,'x',0			//bString[]: String (UTF16LE, not terminated)
};

static const uint8_t serialName[] = {
	0x0a,							        //bLength: length of this descriptor in bytes (10)
	USB_DESC_STRING,				  //bDescriptorType: string descriptor
	'V',0,'1',0,'.',0,'0',0		//bString[]: String (UTF16LE, not terminated)
};


void KeyboardInit( uint8_t* inBuffer, 
                   uint8_t* outBuffer, 
                   HidInReportHandler inReportHandler, 
                   HidOutReportHandler outReportHandler) {

	HIDInit(deviceDescriptor, 
          configDescriptor, 
          manufacturerName, 
          deviceName, 
          serialName, 
          configDescriptor+0x12,
			    reportDescriptor, 
          sizeof(reportDescriptor), 
          inBuffer, 
          outBuffer, 
          inReportHandler, 
          outReportHandler);
}
