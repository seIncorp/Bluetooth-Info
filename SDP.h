#pragma once

namespace SDP
{
	typedef enum
	{
		Headset = 0x1108,
		AudioSource = 0x110A,
		AudioSink = 0x110B,
		//AdvancedAudioDistribution = 0x110D,		<-- profile not service
		Headset_Audio_Gateway = 0x1112,
		Handsfree = 0x111E,
		OBEXObjectPush = 0x1105,
		OBEXFileTransfer = 0x1106,
		A_V_RemoteControl = 0x110E,
		A_V_RemoteControlTarget = 0x110C,
		A_V_RemoteControlController = 0x110F


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
		ServiceRecordHandle = 0x0000,
		ServiceClassIDList = 0x0001,
		ServiceRecordState = 0x0002,
		ServiceID = 0x0003,
		ProtocolDescriptorList = 0x0004,
		BrowseGroupList = 0x0005,
		LanguageBaseAttributeIDList = 0x0006,
		ServiceInfoTimeToLive = 0x0007,
		ServiceAvailability = 0x0008,
		BluetoothProfileDescriptorList = 0x0009,
		DocumentationURL = 0x000A,
		ClientExecutableURL = 0x000B,
		IconURL = 0x000C,
		AdditionalProtocolDescriptorList = 0x000D


	} ATTRIBUTE_ID;






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


std::string getElementTypeString(BYTE type);
int getElementSize(BYTE size, int *add_bits);
std::string getProtocolTypeString(SHORT type);




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



typedef struct SERVICE_RECORD_HANDLE_S
{
	struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)


		BYTE *value;
	} ATTR_ID;

	struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)


		BYTE* value;

	} VALUE;

	void print()
	{
		printf("ATTRIBUTE ID:\n");
		printf("Type: %s [%d]\n", getElementTypeString(ATTR_ID.element->element.type).c_str(), ATTR_ID.element->element.type);

		if (ATTR_ID.additional_bits_flag)
		{
			printf("Additional size: %d\n", ATTR_ID.additional_bits_for_size);

		}
		else
		{
			printf("Size: %d Bytes [%d]\n", ATTR_ID.size_bytes, ATTR_ID.size_bytes);
			
			printf("Value: 0x");
			for (int a = 0; a < ATTR_ID.size_bytes; a++)
				printf("%02X", ATTR_ID.value[a]);
			printf("\n");
		}

		printf("VALUE ELEMENT:\n");
		printf("Type: %s [%d]\n", getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
		if (VALUE.additional_bits_flag)
		{
			printf("Additional size: %d\n", VALUE.additional_bits_for_size);

		}
		else
		{
			printf("Size: %d Bytes [%d]\n", VALUE.size_bytes, VALUE.size_bytes);

			printf("Value: 0x");
			for (int a = 0; a < VALUE.size_bytes; a++)
				printf("%02X", VALUE.value[a]);
			printf("\n");
		}



		printf("\n");
		printf("\n");
		printf("\n");
	}

	/*void setSie()
	{
		if (ATTR_ID.element.size == _2_bytes)
			ATTR_ID.value = (BYTE*)malloc( 2 * sizeof(BYTE));
	};*/

} SERVICE_RECORD_HANDLE, *PSERVICE_RECORD_HANDLE;

typedef struct SERVICE_CLASS_ID_LIST_S
{
	struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)

		BYTE* value;

	} ATTR_ID;

	struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)
		ULONG size_bytes_additional;

		BYTE* value;

		int num_classes;
		SERVICE_CLASS *classes;				// pointer to array of SERVICE_CLASS objects

	} VALUE;

	void print()
	{
		printf("ATTRIBUTE ID:\n");
		printf("Type: %s [%d]\n", getElementTypeString(ATTR_ID.element->element.type).c_str(), ATTR_ID.element->element.type);

		if (ATTR_ID.additional_bits_flag)
		{
			printf("Additional size: %d\n", ATTR_ID.additional_bits_for_size);

		}
		else
		{
			printf("Size: %d Bytes [%d]\n", ATTR_ID.size_bytes, ATTR_ID.size_bytes);

			printf("Value: 0x");
			for (int a = 0; a < ATTR_ID.size_bytes; a++)
				printf("%02X", ATTR_ID.value[a]);
			printf("\n");
		}

		printf("VALUE ELEMENT:\n");
		printf("Type: %s [%d]\n", getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
		if (VALUE.additional_bits_flag)
		{
			printf("Additional size: %d\n", VALUE.additional_bits_for_size);
			if (VALUE.additional_bits_for_size == 1)
			{
				printf("Data size: %d\n", VALUE.size_bytes);

				printf("Value: ");
				for (int a = 0; a < VALUE.size_bytes; a++)
					printf("0x%02X ", VALUE.value[a]);
				printf("\n");

			}
		}
		else
		{
			printf("Size: %d Bytes [%d]\n", VALUE.size_bytes, VALUE.size_bytes);

			printf("Value: 0x");
			for (int a = 0; a < VALUE.size_bytes; a++)
				printf("%02X", VALUE.value[a]);
			printf("\n");
		}


		// TODO: naredi tako da se bodo kreirali objekt za vsak class posebej, ker jih je v prihodnosti lahko vec
		//printf("CLASS 0: 0x%02X%02X\n", VALUE.value[1], VALUE.value[2]);
		//printf("CLASS 1: 0x%02X%02X\n", VALUE.value[4], VALUE.value[5]);

		for (int a = 0; a < VALUE.num_classes; a++)
			printf("Class ID [%d]: 0x%04X\n",a,VALUE.classes[a].value);


		printf("\n");
		printf("\n");
		printf("\n");
	}

} SERVICE_CLASS_ID_LIST, *PSERVICE_CLASS_ID_LIST;

typedef struct PROTOCOL_DESCRIPTOR_LIST_S
{
	struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)

		BYTE* value;

	} ATTR_ID;

	struct
	{
		ATTRIBUTE_ID_ELEMENT* element;

		int size_bytes;						// size value for element value
		int additional_bits_flag;
		int additional_bits_for_size;		// additional bytes for size value (after this you must read those bytes for real size of element value)
		ULONG size_bytes_additional;

		BYTE* value;						// celotna vsebina Value-a

		int num_protocols;

		PROTOCOL_DESCRIPTOR* protocols;


	} VALUE;

	void print()
	{
		printf("ATTRIBUTE ID:\n");
		printf("Type: %s [%d]\n", getElementTypeString(ATTR_ID.element->element.type).c_str(), ATTR_ID.element->element.type);

		if (ATTR_ID.additional_bits_flag)
		{
			printf("Additional size: %d\n", ATTR_ID.additional_bits_for_size);

		}
		else
		{
			printf("Size: %d Bytes [%d]\n", ATTR_ID.size_bytes, ATTR_ID.size_bytes);

			printf("Value: 0x");
			for (int a = 0; a < ATTR_ID.size_bytes; a++)
				printf("%02X", ATTR_ID.value[a]);
			printf("\n");
		}


		printf("VALUE ELEMENT:\n");
		printf("Type: %s [%d]\n", getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
		if (VALUE.additional_bits_flag)
		{
			printf("Additional size: %d\n", VALUE.additional_bits_for_size);
			if (VALUE.additional_bits_for_size == 1)
			{
				printf("Data size: %d\n", VALUE.size_bytes);

				printf("Value: ");
				for (int a = 0; a < VALUE.size_bytes; a++)
					printf("0x%02X ", VALUE.value[a]);
				printf("\n");

			}
		}
		else
		{
			printf("Size: %d Bytes [%d]\n", VALUE.size_bytes, VALUE.size_bytes);

			printf("Value: 0x");
			for (int a = 0; a < VALUE.size_bytes; a++)
				printf("%02X", VALUE.value[a]);
			printf("\n");
		}

		for (int c = 0; c < VALUE.num_protocols; c++)
		{
			printf("Protocol [%d]:\n", c);

			printf("\tValue: ");
			for (int d = 0; d < VALUE.protocols[c].additional_bits_for_size; d++)
				printf("0x%X ", VALUE.protocols[c].value[d]);
			printf("\n");

			printf("\tID [0x%04X][%s]\n", VALUE.protocols[c].protocol_id, getProtocolTypeString(VALUE.protocols[c].protocol_id).c_str());
			if (VALUE.protocols[c].additional_parameters_flag)
			{
				if (dd.service_class_id_in_use == SDP::Handsfree || dd.service_class_id_in_use == SDP::Headset || dd.service_class_id_in_use == SDP::Headset_Audio_Gateway || dd.service_class_id_in_use == SDP::OBEXObjectPush || dd.service_class_id_in_use == SDP::OBEXFileTransfer)
					printf("\tChannel number: %d\n", VALUE.protocols[c].pdsp->server_channel_num);

				if (dd.service_class_id_in_use == SDP::AudioSource ||
					dd.service_class_id_in_use == SDP::AudioSink ||
					dd.service_class_id_in_use == SDP::A_V_RemoteControlTarget ||
					dd.service_class_id_in_use == SDP::A_V_RemoteControl ||
					dd.service_class_id_in_use == SDP::A_V_RemoteControlController
				)
				{
					if (VALUE.protocols[c].protocol_id == SDP::_L2CAP)
						printf("\tPSM: 0x%04X\n", VALUE.protocols[c].pdsp->PSM);
					if (VALUE.protocols[c].protocol_id == SDP::_AVDTP || VALUE.protocols[c].protocol_id == SDP::_AVCTP)
						printf("\tVersion: 0x%04X\n", VALUE.protocols[c].pdsp->Version);
				}
			}
		}
		printf("\n");


	}


} PROTOCOL_DESCRIPTOR_LIST, *PPROTOCOL_DESCRIPTOR_LIST;



BOOL call_IOCTL_BTH_SDP_ATTRIBUTE_SEARCH(BTH_SDP_ATTRIBUTE_SEARCH_REQUEST* bsasr, BYTE bssr_response[], int res_length);

int getAndParse_SERVICE_RECORD_HANDLE(ULONG recordHandle, HANDLE_SDP_TYPE aa);
int getAndParse_SERVICE_CLASS_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
int getAndParse_PROTOCOL_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);







