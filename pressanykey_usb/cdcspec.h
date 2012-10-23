/** Definitions taken from the USB CDC Spec, V1.1.
 These definitions should be largely platform-independent. */

#ifndef _USBCDCSPEC_
#define _USBCDCSPEC_

/** class specific interface classes - use in interface bClass fields */
typedef enum USB_CDC_INTERFACE_CLASS {
	USB_CDC_INTERFACE_COMMUNICATION_INTERFACE			= 0x02,
	USB_CDC_INTERFACE_DATA_INTERFACE					= 0x0a 
} USB_CDC_INTERFACE_CLASS;
	
/** communication interface subclass - use in interface subclass field 
 *  USB CDC subclass ids, defined in usbcdc11.pdf Table 16 p.28 (p.39 pdf)*/
typedef enum USB_CDC_CI_SUBCLASS {
	USB_CDC_SUBCLASS_UNDEFINED                         = 0x00,
	USB_CDC_SUBCLASS_DIRECT_LINE_CONTROL_MODEL         = 0x01,
	USB_CDC_SUBCLASS_ABSTRACT_CONTROL_MODEL            = 0x02,
	USB_CDC_SUBCLASS_TELEPHONE_CONTROL_MODEL           = 0x03,
	USB_CDC_SUBCLASS_MULTICHANNEL_CONTROL_MODEL        = 0x04,
	USB_CDC_SUBCLASS_CAPI_CONTROL_MODEL                = 0x05,
	USB_CDC_SUBCLASS_ETHERNET_NETWORKING_CONTROL_MODEL = 0x06,
	USB_CDC_SUBCLASS_ATM_NETWORKING_CONTROL_MODEL      = 0x07
} USB_CDC_CI_SUBCLASS;

/** communication interface protocol - use in interface bProtocol field */
typedef enum USB_CDC_CI_PROTOCOL {
	USB_CDC_CI_PROTOCOL_NONE							= 0x00,
	USB_CDC_CI_PROTOCOL_V25TER							= 0x01,
	USB_CDC_CI_PROTOCOL_VENDOR							= 0xff
} USB_CDC_CI_PROTOCOL;

/** data interface protocol - use in interface bProtocol field */
typedef enum USB_CDC_DI_PROTOCOL {
	USB_CDC_DI_PROTOCOL_NONE							= 0x00,
	USB_CDC_DI_PROTOCOL_I430							= 0x30,
	USB_CDC_DI_PROTOCOL_ISO3309							= 0x31,
	USB_CDC_DI_PROTOCOL_TRANSPARENT						= 0x32,
	USB_CDC_DI_PROTOCOL_Q921M							= 0x50,
	USB_CDC_DI_PROTOCOL_Q921							= 0x51,
	USB_CDC_DI_PROTOCOL_Q921TM							= 0x52,
	USB_CDC_DI_PROTOCOL_V42BIS							= 0x90,
	USB_CDC_DI_PROTOCOL_Q931							= 0x91,
	USB_CDC_DI_PROTOCOL_V120							= 0x92,
	USB_CDC_DI_PROTOCOL_CAPI20							= 0x93,
	USB_CDC_DI_PROTOCOL_PROT_UNIT_FUNC_DESC				= 0xfe,
	USB_CDC_DI_PROTOCOL_VENDOR							= 0xff
} USB_CDC_DI_PROTOCOL;

/** descriptor types for CDC-specific descriptors */
typedef enum USB_CDC_DESCRIPTOR_TYPE {
	USB_CDC_HEADER_FUNC_DESC							= 0x00,
	USB_CDC_CALL_MGMT_FUNC_DESC							= 0x01,
	USB_CDC_ABSTRACT_CONTROL_MODEL_FUNC_DESC			= 0x02,
	USB_CDC_DIRECT_LINE_MGMT_FUNC_DESC					= 0x03,
	USB_CDC_TEL_RINGER_FUNC_DESC						= 0x04,
	USB_CDC_TEL_LINE_STATE_REPORT_CAP_FUNC_DESC			= 0x05,
	USB_CDC_UNION_FUNC_DESC								= 0x06,
	USB_CDC_TEL_OP_MODES_FUNC_DESC						= 0x07,
	USB_CDC_USB_TERM_FUNC_DESC							= 0x08
} USB_CDC_DESCRIPTOR_TYPE;

#endif
