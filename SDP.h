#pragma once



namespace SDP
{
	typedef enum
	{
		// DONE
		Headset								= 0x1108,
		AudioSource							= 0x110A,
		AudioSink							= 0x110B,
		Headset_Audio_Gateway				= 0x1112,
		Handsfree							= 0x111E,
		OBEXObjectPush						= 0x1105,
		OBEXFileTransfer					= 0x1106,
		A_V_RemoteControl					= 0x110E,
		A_V_RemoteControlTarget				= 0x110C,
		A_V_RemoteControlController			= 0x110F,
		PANU								= 0x1115,
		_NAP								= 0x1116,
		HandsfreeAudioGateway				= 0x111F,
		Phonebook_Access_PSE				= 0x112F,
		Phonebook_Access					= 0x1130,
		Message_Access_Server				= 0x1132,
		Message_Access_Profile				= 0x1134,
		PnPInformation						= 0x1200,
		GenericAudio						= 0x1203,

		// TODO: 
		Phonebook_Access_PCE				= 0x112E,
		Message_Notification_Server			= 0x1133

	} SERVICE_CLASS_ID;

	typedef enum
	{
		_Nil = 0,
		_Unsigned_int,
		_Signed_twos_complement_int,
		_UUID,
		_Text_string,
		_Boolean,
		_Data_element_sequence,
		_Data_element_alternative,
		_URL,
		_Reserved

	} DATA_ELEMENT_TYPE_DESCRIPTOR_VALUE;

	typedef enum
	{
		_1_byte = 0,
		_2_bytes,
		_4_bytes,
		_8_bytes,
		_16_bytes,
		_additional_8_bits,		//unsigned integer
		_additional_16_bits,	//unsigned integer
		_additional_32_bits		//unsigned integer

	} DATA_ELEMENT_SIZE_DESCRIPTOR_VALUE;

	typedef enum
	{
		SDP_ERROR_RSP = 1,
		SDP_SERVICE_SEARCH_REQ,
		SDP_SERVICE_SEARCH_RSP,
		SDP_SERVICE_ATTR_REQ,
		SDP_SERVICE_ATTR_RSP,
		SDP_SERVICE_SEARCH_ATTR_REQ,
		SDP_SERVICE_SEARCH_ATTR_RSP

	} PDU_ID;

	typedef enum
	{
		_SDP = 0x0001,
		_UDP = 0x0002,
		_RFCOMM = 0x0003,
		_TCP = 0x0004,
		_TCS_BIN = 0x0005,
		_TCS_AT = 0x0006,
		_ATT = 0x0007,
		_OBEX = 0x0008,
		_IP = 0x0009,
		_FTP = 0x000a,
		_HTTP = 0x000c,
		_WSP = 0x000e,
		_BNEP = 0x000f,
		_UPNP = 0x0010,
		_HIDP = 0x0011,
		_AVCTP = 0x0017,
		_AVDTP = 0x0019,
		_CMTP = 0x001b,
		_L2CAP = 0x0100

	} PROTOCOL_ID;

	typedef enum
	{
		IPv4		= 0x0800,
		ARP			= 0x0806,
		FRARP		= 0x0808,
		IPv6		= 0x86DD
		// https://www.rfc-editor.org/rfc/pdfrfc/rfc7042.txt.pdf


	} NETWORK_PACKET_TYPE;

	typedef enum
	{
		ServiceRecordHandle					= 0x0000,
		ServiceClassIDList					= 0x0001,
		ServiceRecordState					= 0x0002,
		ServiceID							= 0x0003,
		ProtocolDescriptorList				= 0x0004,
		BrowseGroupList						= 0x0005,
		LanguageBaseAttributeIDList			= 0x0006,
		ServiceInfoTimeToLive				= 0x0007,
		ServiceAvailability					= 0x0008,
		BluetoothProfileDescriptorList		= 0x0009,
		DocumentationURL					= 0x000A,
		ClientExecutableURL					= 0x000B,
		IconURL								= 0x000C,
		AdditionalProtocolDescriptorList	= 0x000D,
		ServiceName							= 0x0100,
		ServiceDescription					= 0x0101,
		ProviderName						= 0x0102

	} ATTRIBUTE_ID;

	


	typedef struct
	{
		struct
		{
			BYTE size : 3;		// ID for enum
			BYTE type : 5;		// ID for enum
		} element;
	} ATTRIBUTE_ID_ELEMENT, * PATTRIBUTE_ID_ELEMENT;

	typedef struct
	{
		ATTRIBUTE_ID_ELEMENT* element;			// pointer to ATTRIBUTE_ID_ELEMENT
		int additional_bits_flag;				// depricated
		SHORT value;								// UUID of class

	} SERVICE_CLASS, * PSERVICE_CLASS;

	typedef struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int server_channel_num;						// for Handsfree, Headset
		SHORT PSM;									// for AudioSource
		SHORT Version;								// for AudioSource
		
		/* for PANU */
		ATTRIBUTE_ID_ELEMENT* element_PANU;			
		int additional_bits_flag_PANU;
		int additional_bits_for_size_PANU;
		int num_of_Supported_Network_Packet_Type_List_PANU;
		SHORT *Supported_Network_Packet_Type_List;	

	} PROTOCOL_DESCRIPTOR_SPECIFIC_PARAMETER;

	typedef struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)

		BYTE* value;

		ATTRIBUTE_ID_ELEMENT* element_protocol;
		SHORT protocol_id;

		int additional_parameters_flag;
		PROTOCOL_DESCRIPTOR_SPECIFIC_PARAMETER* pdsp;

	} PROTOCOL_DESCRIPTOR;

	typedef struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)

		BYTE* value;

	} BLUETOOTH_PROFILE, *PBLUETOOTH_PROFILE;

	typedef struct ATTR_ID_S
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)

		BYTE* value;

	} ATTR_ID;
	
	typedef struct VALUE_S
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)
		ULONG size_bytes_additional;

		BYTE* value;

	} VALUE;



};



/*
	Core_v5.2%20(1).pdf --> 1224 page
	DATA ELEMET:

	Without addititonal bits
	Data element --> 1 Byte --> [0000 0 - TYPE] [000 - SIZE] ...

	With additional bits:
	Data element --> [1 Byte --> [0000 0 - TYPE] [000 - SIZE] ] [ 1 Byte (_additional_8_bits) size] ...

	... --> moving to Value

*/









// TODO: probi dobiti celoten PDU, kjer so se vsi ostali podatki

// TODO: dodaj se za pdu error response















