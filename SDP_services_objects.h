#pragma once



namespace SDP
{

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

}