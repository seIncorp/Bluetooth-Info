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
		ServiceDescription					= 0x0101

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


	namespace FUNCTIONS
	{
		std::string getElementTypeString(BYTE type);
		int getElementSize(BYTE size, int* add_bits);
		std::string getProtocolTypeString(SHORT type);
		std::string getNetworkPacketTypeString(SHORT type);

		BOOL call_IOCTL_BTH_SDP_ATTRIBUTE_SEARCH(BTH_SDP_ATTRIBUTE_SEARCH_REQUEST* bsasr, BYTE bssr_response[], int res_length);
		BOOL set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(ULONG recordHandle, HANDLE_SDP_TYPE aa, USHORT minAttr, USHORT maxAttr, BYTE res[], int res_length);

		void printResponse( BYTE bssr_response[]);

		int getAndParse_SERVICE_RECORD_HANDLE(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_CLASS_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_PROTOCOL_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_NAME(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_AVAILABILITY(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_DESCRIPTION(ULONG recordHandle, HANDLE_SDP_TYPE aa);

		template<class A, class B>
		int set_save_ATTRIBUTE_ELEMENT(A id_handle, B res, int res_length);

		template<class A, class B>
		int set_save_VALUE_ELEMENT(A id_handle, B res, int res_length, int position);

	};

	typedef struct SERVICE_RECORD_HANDLE_S
	{
		ATTR_ID* attr_id;

		struct VV : VALUE
		{

		} VALUE;


		void print()
		{
			printf("ATTRIBUTE ID:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

			if (attr_id->additional_bits_flag)
			{
				printf("Additional size: %d\n", attr_id->additional_bits_for_size);

			}
			else
			{
				printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < attr_id->size_bytes; a++)
					printf("%02X", attr_id->value[a]);
				printf("\n");
			}

			printf("VALUE ELEMENT:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
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

	} SERVICE_RECORD_HANDLE, * PSERVICE_RECORD_HANDLE;

	typedef struct SERVICE_CLASS_ID_LIST_S
	{
		ATTR_ID* attr_id;

		struct VV : VALUE
		{

			int num_classes;
			SERVICE_CLASS* classes;				// pointer to array of SERVICE_CLASS objects
		} VALUE;


		void print()
		{
			printf("ATTRIBUTE ID:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

			if (attr_id->additional_bits_flag)
			{
				printf("Additional size: %d\n", attr_id->additional_bits_for_size);

			}
			else
			{
				printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < attr_id->size_bytes; a++)
					printf("%02X", attr_id->value[a]);
				printf("\n");
			}

			printf("VALUE ELEMENT:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
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
				printf("Class ID [%d]: 0x%04X\n", a, VALUE.classes[a].value);


			printf("\n");
			printf("\n");
			printf("\n");
		}

	} SERVICE_CLASS_ID_LIST, * PSERVICE_CLASS_ID_LIST;

	typedef struct PROTOCOL_DESCRIPTOR_LIST_S
	{
		ATTR_ID* attr_id;

		struct VV : VALUE
		{
			int num_protocols;

			PROTOCOL_DESCRIPTOR* protocols;

			int _BNEP_flag;
			
		} VALUE;


		void print()
		{
			printf("ATTRIBUTE ID:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

			if (attr_id->additional_bits_flag)
			{
				printf("Additional size: %d\n", attr_id->additional_bits_for_size);

			}
			else
			{
				printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < attr_id->size_bytes; a++)
					printf("%02X", attr_id->value[a]);
				printf("\n");
			}


			printf("VALUE ELEMENT:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
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
				if (VALUE._BNEP_flag == 1 && c < (VALUE.num_protocols -1))
				{
					/* za vse protokole ki so BNEP  */
					printf("Protocol [%d]:\n", c);

					printf("\tValue: ");
					for (int d = 0; d < VALUE.protocols[c].additional_bits_for_size; d++)
						printf("0x%X ", VALUE.protocols[c].value[d]);
					printf("\n");

					printf("\tID [0x%04X][%s]\n", VALUE.protocols[c].protocol_id, FUNCTIONS::getProtocolTypeString(VALUE.protocols[c].protocol_id).c_str());
					if (VALUE.protocols[c].additional_parameters_flag)
					{
						if (dd.service_class_id_in_use == Handsfree ||
							dd.service_class_id_in_use == Headset ||
							dd.service_class_id_in_use == Headset_Audio_Gateway ||
							dd.service_class_id_in_use == OBEXObjectPush ||
							dd.service_class_id_in_use == OBEXFileTransfer ||
							dd.service_class_id_in_use == SDP::HandsfreeAudioGateway ||
							dd.service_class_id_in_use == SDP::Phonebook_Access_PSE ||
							dd.service_class_id_in_use == SDP::Phonebook_Access ||
							dd.service_class_id_in_use == SDP::Message_Access_Server ||
							dd.service_class_id_in_use == SDP::Message_Access_Profile ||
							dd.service_class_id_in_use == SDP::GenericAudio
							)
							printf("\tChannel number: %d\n", VALUE.protocols[c].pdsp->server_channel_num);

						if (dd.service_class_id_in_use == AudioSource ||
							dd.service_class_id_in_use == AudioSink ||
							dd.service_class_id_in_use == A_V_RemoteControlTarget ||
							dd.service_class_id_in_use == A_V_RemoteControl ||
							dd.service_class_id_in_use == A_V_RemoteControlController ||
							dd.service_class_id_in_use == PANU ||
							dd.service_class_id_in_use == _NAP
							)
						{
							if (VALUE.protocols[c].protocol_id == _L2CAP)
								printf("\tPSM: 0x%04X\n", VALUE.protocols[c].pdsp->PSM);

							if (VALUE.protocols[c].protocol_id == _AVDTP ||
								VALUE.protocols[c].protocol_id == _AVCTP ||
								VALUE.protocols[c].protocol_id == _BNEP
								)
								printf("\tVersion: 0x%04X\n", VALUE.protocols[c].pdsp->Version);

							if (VALUE.protocols[c].protocol_id == _BNEP)
							{
								printf("\tNumber of supported network packet type: %d\n", VALUE.protocols[c].pdsp->num_of_Supported_Network_Packet_Type_List_PANU);

								for (int aaa = 0; aaa < VALUE.protocols[c].pdsp->num_of_Supported_Network_Packet_Type_List_PANU; aaa++)
								{
									printf("\tnetwork packet type [0x%04X][%s]\n", VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa], FUNCTIONS::getNetworkPacketTypeString(VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa]).c_str());
								}
							}

						}
					}
				}
				else if (VALUE._BNEP_flag != 1)
				{
					/* za vse protokole ki niso BNEP */
					
					printf("Protocol [%d]:\n", c);

					printf("\tValue: ");
					for (int d = 0; d < VALUE.protocols[c].additional_bits_for_size; d++)
						printf("0x%X ", VALUE.protocols[c].value[d]);
					printf("\n");

					printf("\tID [0x%04X][%s]\n", VALUE.protocols[c].protocol_id, FUNCTIONS::getProtocolTypeString(VALUE.protocols[c].protocol_id).c_str());
					if (VALUE.protocols[c].additional_parameters_flag)
					{
						if (dd.service_class_id_in_use == Handsfree ||
							dd.service_class_id_in_use == Headset ||
							dd.service_class_id_in_use == Headset_Audio_Gateway ||
							dd.service_class_id_in_use == OBEXObjectPush ||
							dd.service_class_id_in_use == OBEXFileTransfer ||
							dd.service_class_id_in_use == SDP::HandsfreeAudioGateway ||
							dd.service_class_id_in_use == SDP::Phonebook_Access_PSE ||
							dd.service_class_id_in_use == SDP::Phonebook_Access ||
							dd.service_class_id_in_use == SDP::Message_Access_Server ||
							dd.service_class_id_in_use == SDP::Message_Access_Profile ||
							dd.service_class_id_in_use == SDP::GenericAudio
							)
							printf("\tChannel number: %d\n", VALUE.protocols[c].pdsp->server_channel_num);

						if (dd.service_class_id_in_use == AudioSource ||
							dd.service_class_id_in_use == AudioSink ||
							dd.service_class_id_in_use == A_V_RemoteControlTarget ||
							dd.service_class_id_in_use == A_V_RemoteControl ||
							dd.service_class_id_in_use == A_V_RemoteControlController ||
							dd.service_class_id_in_use == PANU ||
							dd.service_class_id_in_use == _NAP
							)
						{
							if (VALUE.protocols[c].protocol_id == _L2CAP)
								printf("\tPSM: 0x%04X\n", VALUE.protocols[c].pdsp->PSM);

							if (VALUE.protocols[c].protocol_id == _AVDTP ||
								VALUE.protocols[c].protocol_id == _AVCTP ||
								VALUE.protocols[c].protocol_id == _BNEP
								)
								printf("\tVersion: 0x%04X\n", VALUE.protocols[c].pdsp->Version);
						}
					}
				}
			}
			printf("\n");

		}

	} PROTOCOL_DESCRIPTOR_LIST, * PPROTOCOL_DESCRIPTOR_LIST;

	typedef struct SERVICE_NAME_S
	{
		ATTR_ID* attr_id;

		struct VV : VALUE
		{} VALUE;


		void print()
		{
			printf("ATTRIBUTE ID:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

			if (attr_id->additional_bits_flag)
			{
				printf("Additional size: %d\n", attr_id->additional_bits_for_size);
			}
			else
			{
				printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < attr_id->size_bytes; a++)
					printf("%02X", attr_id->value[a]);
				printf("\n");
			}

			printf("VALUE ELEMENT:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
			if (VALUE.additional_bits_flag)
			{
				printf("Additional size: %d\n", VALUE.additional_bits_for_size);
				if (VALUE.additional_bits_for_size == 1)
				{
					printf("Data size: %d\n", VALUE.size_bytes);

					printf("Value: ");
					for (int a = 0; a < VALUE.size_bytes; a++)
						printf("%c", VALUE.value[a]);
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
		}

	} SERVICE_NAME, *PSERVICE_NAME;
	
	typedef struct BLUETOOTH_PROFILE_DESCRIPTOR_LIST_S
	{
		ATTR_ID* attr_id;

		struct VV : VALUE
		{
			/* PROFILES */

			SHORT profile_UUID;
			SHORT profile_version;

			// samo za vec profilov
			//int num_Profiles_list;
			//BLUETOOTH_PROFILE* pProfile_list;
		} VALUE;

		void print()
		{
			printf("ATTRIBUTE ID:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

			if (attr_id->additional_bits_flag)
			{
				printf("Additional size: %d\n", attr_id->additional_bits_for_size);
			}
			else
			{
				printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < attr_id->size_bytes; a++)
					printf("%02X", attr_id->value[a]);
				printf("\n");
			}

			printf("VALUE ELEMENT:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
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

			printf("Profile UUID: 0x%04X\n", VALUE.profile_UUID);
			printf("Profile version: 0x%04X\n", VALUE.profile_version);


		}


	} BLUETOOTH_PROFILE_DESCRIPTOR_LIST, *PBLUETOOTH_PROFILE_DESCRIPTOR_LIST;

	typedef struct LANGUAGE_BASE_ATTRIBUTE_ID_LIST_S
	{
		ATTR_ID* attr_id;

		struct VV : VALUE
		{
			// TODO: naredi ce je teh tripletov vec kot eden (trenutno je narejeno samo za enega)

			SHORT triplet_id_natural_lang;
			SHORT triplet_id_char_encoding;
			SHORT triplet_attribute_id;
		} VALUE;

		void print()
		{
			printf("ATTRIBUTE ID:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

			if (attr_id->additional_bits_flag)
			{
				printf("Additional size: %d\n", attr_id->additional_bits_for_size);
			}
			else
			{
				printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < attr_id->size_bytes; a++)
					printf("%02X", attr_id->value[a]);
				printf("\n");
			}

			printf("VALUE ELEMENT:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
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

			printf("Natural language ID: 0x%04X\n", VALUE.triplet_id_natural_lang);
			printf("Character encoding ID: 0x%04X\n", VALUE.triplet_id_char_encoding);
			printf("Attribute ID: 0x%04X\n", VALUE.triplet_attribute_id);

		}



	} LANGUAGE_BASE_ATTRIBUTE_ID_LIST, *PLANGUAGE_BASE_ATTRIBUTE_ID_LIST;

	typedef struct SERVICE_DESCRIPTION_S
	{
		ATTR_ID* attr_id;

		struct VV : VALUE
		{} VALUE;


		void print()
		{
			printf("ATTRIBUTE ID:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

			if (attr_id->additional_bits_flag)
			{
				printf("Additional size: %d\n", attr_id->additional_bits_for_size);
			}
			else
			{
				printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < attr_id->size_bytes; a++)
					printf("%02X", attr_id->value[a]);
				printf("\n");
			}

			printf("VALUE ELEMENT:\n");
			printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
			if (VALUE.additional_bits_flag)
			{
				printf("Additional size: %d\n", VALUE.additional_bits_for_size);
				if (VALUE.additional_bits_for_size == 1)
				{
					printf("Data size: %d\n", VALUE.size_bytes);

					printf("Value: ");
					for (int a = 0; a < VALUE.size_bytes; a++)
						printf("%c", VALUE.value[a]);
					printf("\n");
				}
			}
			else
			{
				printf("Size: %d Bytes [%d]\n", VALUE.size_bytes, VALUE.size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < VALUE.size_bytes; a++)
					printf("%c", VALUE.value[a]);
				printf("\n");
			}
		}





	} SERVICE_DESCRIPTION, *PSERVICE_DESCRIPTION;

	
	/* USED ONLY IN NAP and PANU */
	namespace NAP
	{
		typedef enum
		{
			IpSubnet				= 0x0200,
			SecurityDescription		= 0x030A,
			NetAccessType			= 0x030B,
			MaxNetAccessrate		= 0x030C,
			IPv4Subnet				= 0x030D,		// TODO:
			IPv6Subnet				= 0x030E		// TODO:

		} ATTRIBUTE_ID_PAN;

		std::string getSecurityDescriptionString(SHORT type);
		std::string getNetAccessTypeString(SHORT type);

		typedef struct SECURITY_DESCRIPTION_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{
				SHORT security_value;
			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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

				printf("Security Description [0x%04X][%s]\n", VALUE.security_value, getSecurityDescriptionString(VALUE.security_value).c_str());

			}


		} SECURITY_DESCRIPTION, *PSECURITY_DESCRIPTION;

		typedef struct NET_ACCESS_TYPE_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{
				SHORT NetAccessType;
			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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

				printf("Type of Network Access Available[0x%04X][%s]\n", VALUE.NetAccessType, getNetAccessTypeString(VALUE.NetAccessType).c_str());
			}

		} NET_ACCESS_TYPE, *PNET_ACCESS_TYPE;
		
		typedef struct MAX_NET_ACCESS_RATE_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{
				DWORD Maximum_possible_Network_Access_Data_Rate;
			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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

				printf("Maximum possible Network Access Data Rate: 0x%08X\n",VALUE.Maximum_possible_Network_Access_Data_Rate);
			}

		} MAX_NET_ACCESS_RATE, *PMAX_NET_ACCESS_RATE;


		int getAndParse_SECURITY_DESCRIPTION_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_NET_ACCESS_TYPE_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_MAX_NET_ACCESS_RATE_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa);


	};
	
	namespace MAP
	{
		typedef enum
		{
			GoepL2capPsm			= 0x0200,
			MASInstanceID			= 0x0315,
			SupportedMessageTypes	= 0x0316,
			MapSupportedFeatures	= 0x0317

		} ATTRIBUTE_ID_MAP;

		struct SUPPORTED_FEATURES_MESSAGES_S
		{
			struct SMT_S
			{
				BYTE a0 : 1;
				BYTE a1 : 1;
				BYTE a2 : 1;
				BYTE a3 : 1;
				BYTE a4 : 1;
				BYTE : 3;
			};

			SMT_S* ttt;


			struct SF_S
			{
				BYTE a0 : 1;
				BYTE a1 : 1;
				BYTE a2 : 1;
				BYTE a3 : 1;
				BYTE a4 : 1;
				BYTE a5 : 1;
				BYTE a6 : 1;
				BYTE a7 : 1;
				BYTE a8 : 1;
				BYTE a9 : 1;
				BYTE a10 : 1;
				BYTE a11 : 1;
				BYTE a12 : 1;
				BYTE a13 : 1;
				BYTE a14 : 1;
				BYTE a15 : 1;
				BYTE a16 : 1;
				BYTE a17 : 1;
				BYTE a18 : 1;
				BYTE a19 : 1;
				BYTE a20 : 1;
				BYTE a21 : 1;
				BYTE a22 : 1;
				BYTE : 6;
				BYTE : 3;
			};

			SF_S* aaa;
			
			SUPPORTED_FEATURES_MESSAGES_S(BYTE *a) : ttt((SMT_S*)a)
			{
				//printf("FROM STRUCT --> %X\n", *a);
			};

			SUPPORTED_FEATURES_MESSAGES_S(DWORD* a) : aaa((SF_S*)a)
			{
				//printf("FROM STRUCT --> %X\n", *a);
			};
			
			
		} ;

		std::string getMessageTypesString(SUPPORTED_FEATURES_MESSAGES_S* sfm);
		std::string getSupportedFeaturesString(SUPPORTED_FEATURES_MESSAGES_S* sfm);


		typedef struct GOEPL2CAPPSM_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{
				
			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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

			}


		} GOEPL2CAPPSM, * PGOEPL2CAPPSM;

		typedef struct SUPPORTED_MESSAGE_TYPES_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{
				SUPPORTED_FEATURES_MESSAGES_S* sfm;

			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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

				printf("Message types: \n%s\n", getMessageTypesString(VALUE.sfm).c_str());
			}


		} SUPPORTED_MESSAGE_TYPES, * PSUPPORTED_MESSAGE_TYPES;

		typedef struct MAS_INSTANCE_ID_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{

			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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

			}


		} MAS_INSTANCE_ID, * PMAS_INSTANCE_ID;

		typedef struct MAP_SUPPORTED_FEATURES_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{
				SUPPORTED_FEATURES_MESSAGES_S* sfm;

			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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

				printf("Features: \n%s\n", getSupportedFeaturesString(VALUE.sfm).c_str());


			}


		} MAP_SUPPORTED_FEATURES, * PMAP_SUPPORTED_FEATURES;


		int getAndParse_GOEPL2CAPPSM_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SUPPORTED_MESSAGE_TYPES_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_MAS_INSTANCE_ID_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_MAP_SUPPORTED_FEATURES_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
	};

	namespace PBAP
	{
		typedef enum
		{
			GoepL2capPsm = 0x0200,
			SupportedRepositories = 0x0314,
			PbapSupportedFeatures = 0x0317

		} ATTRIBUTE_ID_PBAP;


		typedef struct SUPPORTED_REPOSITORIES_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{
				

			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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

				
			}


		} SUPPORTED_REPOSITORIES, * PSUPPORTED_REPOSITORIES;

		typedef struct PBAP_SUPPORTED_FEATURES_S
		{
			ATTR_ID* attr_id;

			struct VV : VALUE
			{


			} VALUE;

			void print()
			{
				printf("ATTRIBUTE ID:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

				if (attr_id->additional_bits_flag)
				{
					printf("Additional size: %d\n", attr_id->additional_bits_for_size);
				}
				else
				{
					printf("Size: %d Bytes [%d]\n", attr_id->size_bytes, attr_id->size_bytes);

					printf("Value: 0x");
					for (int a = 0; a < attr_id->size_bytes; a++)
						printf("%02X", attr_id->value[a]);
					printf("\n");
				}

				printf("VALUE ELEMENT:\n");
				printf("Type: %s [%d]\n", FUNCTIONS::getElementTypeString(VALUE.element->element.type).c_str(), VALUE.element->element.type);
				if (VALUE.additional_bits_flag)
				{
					printf("Additional size: %d\n", VALUE.additional_bits_for_size);
					if (VALUE.additional_bits_for_size == 1)
					{
						printf("Data size: %d\n", VALUE.size_bytes);

						printf("Value: ");
						for (int a = 0; a < VALUE.size_bytes; a++)
							printf("%02X", VALUE.value[a]);
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


			}


		} PBAP_SUPPORTED_FEATURES, * PPBAP_SUPPORTED_FEATURES;

		// GoepL2CapPsm use from MAP

		int getAndParse_SUPPORTED_REPOSITORIES_PBAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_PBAP_SUPPORTED_FEATURES_PBAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);






	};




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















