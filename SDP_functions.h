#pragma once


namespace SDP
{
	namespace SUB_FUNCTIONS
	{
		std::string getElementTypeString(BYTE type);
		int getElementSize(BYTE size, int* add_bits);
		std::string getProtocolTypeString(SHORT type);
		std::string getNetworkPacketTypeString(SHORT type);

	};


	typedef struct DEFAULT_OBJECT_S
	{
		ATTR_ID* attr_id;

		struct VV : VALUE
		{


		} VALUE;

		void printATTR_ELEMENT()
		{
			printf("ATTRIBUTE ID:\n");
			printf("Type: %s [%d]\n", SDP::SUB_FUNCTIONS::getElementTypeString(attr_id->element->element.type).c_str(), attr_id->element->element.type);

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
		}

		template<class T>
		void printVALUE_ELEMENT(T v)
		{
			printf("VALUE ELEMENT:\n");
			printf("Type: %s [%d]\n", SDP::SUB_FUNCTIONS::getElementTypeString(v.element->element.type).c_str(), v.element->element.type);
			if (v.additional_bits_flag)
			{
				printf("Additional size: %d\n", v.additional_bits_for_size);
				if (v.additional_bits_for_size == 1)
				{
					printf("Data size: %d\n", v.size_bytes);

					printf("Value: ");
					for (int a = 0; a < v.size_bytes; a++)
						printf("0x%02X ", v.value[a]);
					printf("\n");
				}
			}
			else
			{
				printf("Size: %d Bytes [%d]\n", v.size_bytes, v.size_bytes);

				printf("Value: 0x");
				for (int a = 0; a < v.size_bytes; a++)
					printf("%02X", v.value[a]);
				printf("\n");
			}
		}

		template<class T>
		void print(T v)
		{
			printATTR_ELEMENT();

			printVALUE_ELEMENT(v);

			printf("\n");
		}

	} DEFAULT_OBJECT, * PDEFAULT_OBJECT;

	typedef struct SERVICE_CLASS_ID_LIST_S : DEFAULT_OBJECT
	{
		struct VV : VALUE
		{

			int num_classes;
			SERVICE_CLASS* classes;				// pointer to array of SERVICE_CLASS objects
		} VALUE;

		template<class T>
		void print(T v)
		{
			printATTR_ELEMENT();

			printVALUE_ELEMENT(v);

			// TODO: naredi tako da se bodo kreirali objekt za vsak class posebej, ker jih je v prihodnosti lahko vec

			for (int a = 0; a < VALUE.num_classes; a++)
				printf("Class ID [%d]: 0x%04X\n", a, VALUE.classes[a].value);

			printf("\n");
		}

	} SERVICE_CLASS_ID_LIST, * PSERVICE_CLASS_ID_LIST;

	typedef struct PROTOCOL_DESCRIPTOR_LIST_S : DEFAULT_OBJECT
	{
		struct VV : VALUE
		{
			int num_protocols;

			PROTOCOL_DESCRIPTOR* protocols;

			int _BNEP_flag;

		} VALUE;

		template<class T>
		void print(T v)
		{
			printATTR_ELEMENT();

			printVALUE_ELEMENT(v);

			for (int c = 0; c < VALUE.num_protocols; c++)
			{
				if (VALUE._BNEP_flag == 1 && c < (VALUE.num_protocols - 1))
				{
					/* za vse protokole ki so BNEP  */
					printf("Protocol [%d]:\n", c);

					printf("\tValue: ");
					for (int d = 0; d < VALUE.protocols[c].additional_bits_for_size; d++)
						printf("0x%X ", VALUE.protocols[c].value[d]);
					printf("\n");

					printf("\tID [0x%04X][%s]\n", VALUE.protocols[c].protocol_id, SUB_FUNCTIONS::getProtocolTypeString(VALUE.protocols[c].protocol_id).c_str());
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
									printf("\tnetwork packet type [0x%04X][%s]\n", VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa], SUB_FUNCTIONS::getNetworkPacketTypeString(VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa]).c_str());
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

					printf("\tID [0x%04X][%s]\n", VALUE.protocols[c].protocol_id, SUB_FUNCTIONS::getProtocolTypeString(VALUE.protocols[c].protocol_id).c_str());
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

	typedef struct SERVICE_NAME_S : DEFAULT_OBJECT
	{
		struct VV : VALUE
		{
			char* service_name;

		} VALUE;

		template<class T>
		void print(T v)
		{
			printATTR_ELEMENT();

			printVALUE_ELEMENT(v);

			printf("Service name: %s\n", v.service_name);
			printf("\n");
		}

	} SERVICE_NAME, * PSERVICE_NAME;

	typedef struct PROVIDER_NAME_S : DEFAULT_OBJECT
	{
		struct VV : VALUE
		{
			char* provider_name;

		} VALUE;

		template<class T>
		void print(T v)
		{
			printATTR_ELEMENT();

			printVALUE_ELEMENT(v);

			printf("Provider name: %s\n", v.provider_name);
			printf("\n");
		}

	} PROVIDER_NAME, * PPROVIDER_NAME;

	typedef struct BLUETOOTH_PROFILE_DESCRIPTOR_LIST_S : DEFAULT_OBJECT
	{
		struct VV : VALUE
		{
			/* PROFILES */

			SHORT profile_UUID;
			SHORT profile_version;

			// samo za vec profilov
			//int num_Profiles_list;
			//BLUETOOTH_PROFILE* pProfile_list;
		} VALUE;

		template<class T>
		void print(T v)
		{
			printATTR_ELEMENT();

			printVALUE_ELEMENT(v);

			printf("Profile UUID: 0x%04X\n", VALUE.profile_UUID);
			printf("Profile version: 0x%04X\n", VALUE.profile_version);
			printf("\n");
		}

	} BLUETOOTH_PROFILE_DESCRIPTOR_LIST, * PBLUETOOTH_PROFILE_DESCRIPTOR_LIST;

	typedef struct LANGUAGE_BASE_ATTRIBUTE_ID_LIST_S : DEFAULT_OBJECT
	{
		struct VV : VALUE
		{
			// TODO: naredi ce je teh tripletov vec kot eden (trenutno je narejeno samo za enega)

			SHORT triplet_id_natural_lang;
			SHORT triplet_id_char_encoding;
			SHORT triplet_attribute_id;
		} VALUE;

		template<class T>
		void print(T v)
		{
			printATTR_ELEMENT();

			printVALUE_ELEMENT(v);

			printf("Natural language ID: 0x%04X\n", VALUE.triplet_id_natural_lang);
			printf("Character encoding ID: 0x%04X\n", VALUE.triplet_id_char_encoding);
			printf("Attribute ID: 0x%04X\n", VALUE.triplet_attribute_id);
			printf("\n");
		}

	} LANGUAGE_BASE_ATTRIBUTE_ID_LIST, * PLANGUAGE_BASE_ATTRIBUTE_ID_LIST;

	typedef struct SERVICE_DESCRIPTION_S : DEFAULT_OBJECT
	{
		struct VV : VALUE
		{
			char* description;

		} VALUE;

		template<class T>
		void print(T v)
		{
			printATTR_ELEMENT();

			printVALUE_ELEMENT(v);

			printf("Description: %s\n", v.description);
			printf("\n");
		}

	} SERVICE_DESCRIPTION, * PSERVICE_DESCRIPTION;


	namespace FUNCTIONS
	{
		namespace SDP_INIT_CONNECT
		{
			/* SET, CONNECT, DISCONNECT FROM SDP DEVICE */
			void init_for_IOCTL_BTH_SDP_CONNECT(char add[], DEVICE_DATA_SDP* device_data_sdp);
			int call_IOCTL_BTH_SDP_CONNECT(DEVICE_DATA_SDP* device_data_sdp);
		};

		namespace SDP_SERVICE_SEARCH
		{
			void init_for_IOCTL_BTH_SDP_SERVICE_SEARCH(DEVICE_DATA_SDP* device_data_sdp);
			int call_IOCTL_BTH_SDP_SERVICE_SEARCH(DEVICE_DATA_SDP* device_data_sdp);
		};

		namespace SDP_ATTRIBUTE_SEARCH
		{
			BOOL call_IOCTL_BTH_SDP_ATTRIBUTE_SEARCH(BTH_SDP_ATTRIBUTE_SEARCH_REQUEST* bsasr, BYTE bssr_response[], int res_length);
			BOOL set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(ULONG recordHandle, HANDLE_SDP_TYPE aa, USHORT minAttr, USHORT maxAttr, BYTE res[], int res_length);
		};

		namespace SDP_INIT_DISCONNECT
		{
			void init_for_IOCTL_BTH_SDP_DISCONNECT(DEVICE_DATA_SDP* device_data_sdp);
			int call_IOCTL_BTH_SDP_DISCONNECT(DEVICE_DATA_SDP* device_data_sdp);
		};


		void printResponse(BYTE bssr_response[]);

		int getAndParse_SERVICE_RECORD_HANDLE(ULONG recordHandle, HANDLE_SDP_TYPE aa, PDEFAULT_OBJECT record_handle = new DEFAULT_OBJECT(), int print = 1);
		int getAndParse_SERVICE_CLASS_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa, PSERVICE_CLASS_ID_LIST class_id_handle = new SERVICE_CLASS_ID_LIST(), int print = 1);
		int getAndParse_PROTOCOL_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa, PPROTOCOL_DESCRIPTOR_LIST protocol_descriptor_list_handle = new PROTOCOL_DESCRIPTOR_LIST(), int print = 1);
		int getAndParse_SERVICE_NAME(ULONG recordHandle, HANDLE_SDP_TYPE aa, PSERVICE_NAME service_name_handle = new SERVICE_NAME(), int print = 1);
		int getAndParse_PROVIDER_NAME(ULONG recordHandle, HANDLE_SDP_TYPE aa, PPROVIDER_NAME provider_name_handle = new PROVIDER_NAME(), int print = 1);
		int getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa, PBLUETOOTH_PROFILE_DESCRIPTOR_LIST bluetooth_profile_descriptor_list_handle = new BLUETOOTH_PROFILE_DESCRIPTOR_LIST(), int print = 1);
		int getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa, PLANGUAGE_BASE_ATTRIBUTE_ID_LIST language_base_attribute_id_list_handle = new LANGUAGE_BASE_ATTRIBUTE_ID_LIST(), int print = 1);
		int getAndParse_SERVICE_AVAILABILITY(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_DESCRIPTION(ULONG recordHandle, HANDLE_SDP_TYPE aa, PSERVICE_DESCRIPTION service_description_handle = new SERVICE_DESCRIPTION(), int print = 1);
	
		template<class A, class B>
		int set_save_ATTRIBUTE_ELEMENT(A id_handle, B res, int res_length) 
		{
			int position = sizeof(BTH_SDP_STREAM_RESPONSE) + 1 + 0;

			SDP::PATTRIBUTE_ID_ELEMENT record_handle_element = new SDP::ATTRIBUTE_ID_ELEMENT();
			record_handle_element = (SDP::PATTRIBUTE_ID_ELEMENT)(res + position);

			id_handle->attr_id = new ATTR_ID();
			id_handle->attr_id->element = record_handle_element;



			int temp_size = SDP::SUB_FUNCTIONS::getElementSize(id_handle->attr_id->element->element.size, &(id_handle->attr_id->additional_bits_flag));

			if (id_handle->attr_id->additional_bits_flag)
			{
				id_handle->attr_id->additional_bits_for_size = temp_size;

				// TODO: nadaljuj z branjem dodatnih byte-ov
			}
			else
			{
				id_handle->attr_id->size_bytes = temp_size;
				position++;

				id_handle->attr_id->value = (BYTE*)malloc(id_handle->attr_id->size_bytes * sizeof(BYTE));
				memset(id_handle->attr_id->value, 0x00, id_handle->attr_id->size_bytes);
				for (int a = 0; a < id_handle->attr_id->size_bytes; a++)
				{
					position += a;
					//printf("%X ", *(res + position));
					id_handle->attr_id->value[a] = *(res + position);
				}
				printf("\n");
			}

			position++;

			return position;
		}

		template<class A, class B>
		int set_save_VALUE_ELEMENT(A id_handle, B res, int res_length, int position) 
		{
			SDP::PATTRIBUTE_ID_ELEMENT record_handle_element_2 = new SDP::ATTRIBUTE_ID_ELEMENT();
			record_handle_element_2 = (SDP::PATTRIBUTE_ID_ELEMENT)(res + position);

			id_handle->VALUE.element = record_handle_element_2;

			int temp_size_VALUE = SDP::SUB_FUNCTIONS::getElementSize(id_handle->VALUE.element->element.size, &(id_handle->VALUE.additional_bits_flag));

			if (id_handle->VALUE.additional_bits_flag)
			{
				id_handle->VALUE.additional_bits_for_size = temp_size_VALUE;

				if (id_handle->VALUE.additional_bits_for_size = 1)
				{
					position++;
					id_handle->VALUE.size_bytes = *(res + position);

					id_handle->VALUE.value = (BYTE*)malloc(id_handle->VALUE.size_bytes * sizeof(BYTE));
					memset(id_handle->VALUE.value, 0x00, id_handle->VALUE.size_bytes);

					position++;
					for (int b = 0; b < id_handle->VALUE.size_bytes; b++)
						id_handle->VALUE.value[b] = *(res + position + b);

				}

				// TODO: naredi se za ostale velikosti 2 in 4
			}
			else
			{
				id_handle->VALUE.size_bytes = temp_size_VALUE;
				position++;

				id_handle->VALUE.value = (BYTE*)malloc(id_handle->VALUE.size_bytes * sizeof(BYTE));
				memset(id_handle->VALUE.value, 0x00, id_handle->VALUE.size_bytes);
				for (int b = 0; b < id_handle->VALUE.size_bytes; b++)
				{

					id_handle->VALUE.value[b] = *(res + position + b);
				}
			}

			position += id_handle->VALUE.size_bytes;

			return position;
		}
	};






}