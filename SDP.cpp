#include "main.h"



int SDP::FUNCTIONS::getElementSize(BYTE size, int* add_bits)
{
	switch (size)
	{
	case SDP::_1_byte:
		*add_bits = 0;
		return 1;
		break;

	case SDP::_2_bytes:
		*add_bits = 0;
		return 2;
		break;

	case SDP::_4_bytes:
		*add_bits = 0;
		return 4;
		break;

	case SDP::_8_bytes:
		*add_bits = 0;
		return 8;
		break;

	case SDP::_16_bytes:
		*add_bits = 0;
		return 16;
		break;

	case SDP::_additional_8_bits:
		*add_bits = 1;
		return 1;
		break;

	case SDP::_additional_16_bits:
		*add_bits = 1;
		return 2;
		break;

	case SDP::_additional_32_bits:
		*add_bits = 1;
		return 4;
		break;
	}
}

std::string SDP::FUNCTIONS::getElementTypeString(BYTE type)
{
	std::string temp;

	switch (type)
	{
	case SDP::_Nil:
		temp = "NIL";
		break;

	case SDP::_Unsigned_int:
		temp = "Unsigned int";
		break;

	case SDP::_Signed_twos_complement_int:
		temp = "Signed twos complement int";
		break;

	case SDP::_UUID:
		temp = "UUID";
		break;

	case SDP::_Text_string:
		temp = "Text string";
		break;

	case SDP::_Boolean:
		temp = "Boolean";
		break;

	case SDP::_Data_element_sequence:
		temp = "Data element sequence";
		break;

	case SDP::_Data_element_alternative:
		temp = "Data element alternative";
		break;

	case SDP::_URL:
		temp = "URL";
		break;
	}

	return temp;
}

std::string SDP::FUNCTIONS::getProtocolTypeString(SHORT type)
{
	std::string temp;

	switch (type)
	{
	case SDP::_SDP:
		temp = "SDP";
		break;

	case SDP::_UDP:
		temp = "UDP";
		break;

	case SDP::_RFCOMM:
		temp = "RFCOMM";
		break;

	case SDP::_TCP:
		temp = "TCP";
		break;

	case SDP::_TCS_BIN:
		temp = "TCS‐BIN";
		break;

	case SDP::_TCS_AT:
		temp = "TCS‐AT";
		break;

	case SDP::_ATT:
		temp = "ATT";
		break;

	case SDP::_OBEX:
		temp = "OBEX";
		break;

	case SDP::_IP:
		temp = "IP";
		break;

	case SDP::_FTP:
		temp = "FTP";
		break;

	case SDP::_HTTP:
		temp = "HTTP";
		break;

	case SDP::_WSP:
		temp = "WSP";
		break;

	case SDP::_BNEP:
		temp = "BNEP";
		break;

	case SDP::_UPNP:
		temp = "UPNP";
		break;

	case SDP::_HIDP:
		temp = "HIDP";
		break;

	case SDP::_AVCTP:
		temp = "AVCTP";
		break;

	case SDP::_AVDTP:
		temp = "AVDTP";
		break;

	case SDP::_CMTP:
		temp = "CMTP";
		break;

	case SDP::_L2CAP:
		temp = "L2CAP";
		break;

	default:
		temp = "Unknown type";
		break;
	}

	return temp;
}

std::string SDP::FUNCTIONS::getNetworkPacketTypeString(SHORT type)
{
	std::string temp;

	switch (type)
	{
	case SDP::IPv4:
		temp = "Internet Protocol Version 4 (IPv4)";
		break;

	case SDP::ARP:
		temp = "Address Resolution Protocol (ARP)";
		break;

	case SDP::FRARP:
		temp = "Frame Relay ARP";
		break;

	case SDP::IPv6:
		temp = "Internet Protocol Version 6 (IPv6)";
		break;
	}

	return temp;
}


BOOL SDP::FUNCTIONS::call_IOCTL_BTH_SDP_ATTRIBUTE_SEARCH(BTH_SDP_ATTRIBUTE_SEARCH_REQUEST* bsasr, BYTE bssr_response[], int res_length)
{
	BOOL test_sdp_call_222;

	test_sdp_call_222 = DeviceIoControl(
		dd.hDevice, // device to be queried
		IOCTL_BTH_SDP_ATTRIBUTE_SEARCH, // operation to perform

		bsasr, sizeof(*bsasr),                       // no input buffer

		bssr_response, res_length,             // output buffer

		&dd.junk,                         // # bytes returned
		(LPOVERLAPPED)NULL);          // synchronous I/O

	DWORD err = GetLastError();
	printErrorMessage(err);

	printf("-- %d\n", dd.junk);

	return test_sdp_call_222;
}

BOOL SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(ULONG recordHandle, HANDLE_SDP_TYPE aa, USHORT minAttr, USHORT maxAttr, BYTE res[], int res_length)
{
	BTH_SDP_ATTRIBUTE_SEARCH_REQUEST* bsasr = new BTH_SDP_ATTRIBUTE_SEARCH_REQUEST();
	bsasr->HANDLE_SDP_FIELD_NAME = aa;
	bsasr->recordHandle = recordHandle;
	bsasr->range[0].minAttribute = minAttr;
	bsasr->range[0].maxAttribute = maxAttr;

	//BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test_sdp_call_222 = false;
	test_sdp_call_222 = SDP::FUNCTIONS::call_IOCTL_BTH_SDP_ATTRIBUTE_SEARCH(bsasr, res, res_length);

	return test_sdp_call_222;
}


void SDP::FUNCTIONS::printResponse(BYTE bssr_response[])
{
	BTH_SDP_STREAM_RESPONSE* bssr_temp = new BTH_SDP_STREAM_RESPONSE();
	bssr_temp = (BTH_SDP_STREAM_RESPONSE*)bssr_response;

	int MAX_length_response = (sizeof(BTH_SDP_STREAM_RESPONSE) + bssr_temp->responseSize);


	for (int t = sizeof(BTH_SDP_STREAM_RESPONSE) + 1, a = 0; t < MAX_length_response; t++, a++)
	{
		if (a == 10)
		{
			printf("\n");
			a = 0;
		}
		printf("0x%02X ", bssr_response[t]);
	}
	printf("\n");
}




int SDP::FUNCTIONS::getAndParse_SERVICE_RECORD_HANDLE(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_RECORD_HANDLE ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ServiceRecordHandle, SDP::ServiceRecordHandle, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);

		SDP::PDEFAULT_OBJECT record_handle = new SDP::DEFAULT_OBJECT();

		int position = set_save_ATTRIBUTE_ELEMENT<PDEFAULT_OBJECT, BYTE[]>(record_handle, bssr_response, 5000);

		position = set_save_VALUE_ELEMENT<PDEFAULT_OBJECT, BYTE[]>(record_handle, bssr_response, 5000, position);

		record_handle->print(record_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::FUNCTIONS::getAndParse_SERVICE_CLASS_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("*** getAndParse_SERVICE_CLASS_ID_LIST ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ServiceClassIDList, SDP::ServiceClassIDList, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);


		SDP::PSERVICE_CLASS_ID_LIST class_id_handle = new SDP::SERVICE_CLASS_ID_LIST();

		int position = set_save_ATTRIBUTE_ELEMENT<PSERVICE_CLASS_ID_LIST, BYTE[]>(class_id_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<PSERVICE_CLASS_ID_LIST, BYTE[]>(class_id_handle, bssr_response, 5000, position);



		class_id_handle->VALUE.num_classes = class_id_handle->VALUE.size_bytes / 3;



		//printf("NUM classes: %d\n", class_id_handle->VALUE.num_classes);

		class_id_handle->VALUE.classes = new SDP::SERVICE_CLASS[class_id_handle->VALUE.num_classes]();

		for (int a = 0, b = 0; a < class_id_handle->VALUE.size_bytes; a += 3, b++)
		{
			SDP::ATTRIBUTE_ID_ELEMENT* temp_att_id = new SDP::ATTRIBUTE_ID_ELEMENT();
			temp_att_id = (SDP::ATTRIBUTE_ID_ELEMENT*)(class_id_handle->VALUE.value + a);

			class_id_handle->VALUE.classes[b].element = temp_att_id;

			int temp_size_1 = SDP::FUNCTIONS::getElementSize(class_id_handle->VALUE.classes[b].element->element.size, &(class_id_handle->VALUE.classes[b].additional_bits_flag));

			class_id_handle->VALUE.classes[b].value |= *(class_id_handle->VALUE.value + a + 1);
			class_id_handle->VALUE.classes[b].value <<= 8;
			class_id_handle->VALUE.classes[b].value |= *(class_id_handle->VALUE.value + a + 2);
		}

		class_id_handle->print<SERVICE_CLASS_ID_LIST_S::VV>(class_id_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::FUNCTIONS::getAndParse_PROTOCOL_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_PROTOCOL_DESCRIPTOR_LIST ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ProtocolDescriptorList, SDP::ProtocolDescriptorList, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);


		SDP::PROTOCOL_DESCRIPTOR_LIST* protocol_descriptor_list_handle = new SDP::PROTOCOL_DESCRIPTOR_LIST();

		int position = set_save_ATTRIBUTE_ELEMENT<PROTOCOL_DESCRIPTOR_LIST*, BYTE[]>(protocol_descriptor_list_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<PROTOCOL_DESCRIPTOR_LIST*, BYTE[]>(protocol_descriptor_list_handle, bssr_response, 5000, position);


		/* presteje se koliko je protokolov */
		protocol_descriptor_list_handle->VALUE.num_protocols = 0;

		for (int aa = 0; aa < protocol_descriptor_list_handle->VALUE.size_bytes; aa++)
		{
			if (protocol_descriptor_list_handle->VALUE.value[aa] == 0x35)
			{
				protocol_descriptor_list_handle->VALUE.num_protocols++;
			}
		}
		protocol_descriptor_list_handle->VALUE.protocols = new SDP::PROTOCOL_DESCRIPTOR[protocol_descriptor_list_handle->VALUE.num_protocols]();

		/* napolnejo se podatki za vsak protokol posebej */
		for (int aa = 0, b = 0; aa < protocol_descriptor_list_handle->VALUE.size_bytes; aa++)
		{
			if (protocol_descriptor_list_handle->VALUE.value[aa] == 0x35)
			{
				SDP::ATTRIBUTE_ID_ELEMENT* temp_att_id = new SDP::ATTRIBUTE_ID_ELEMENT();
				temp_att_id = (SDP::ATTRIBUTE_ID_ELEMENT*)(protocol_descriptor_list_handle->VALUE.value + aa);

				protocol_descriptor_list_handle->VALUE.protocols[b].element = temp_att_id;

				int temp_size_v_1 = SDP::FUNCTIONS::getElementSize(protocol_descriptor_list_handle->VALUE.protocols[b].element->element.size, &(protocol_descriptor_list_handle->VALUE.protocols[b].additional_bits_flag));

				if (protocol_descriptor_list_handle->VALUE.additional_bits_flag == 1)
				{
					protocol_descriptor_list_handle->VALUE.protocols[b].additional_bits_for_size = protocol_descriptor_list_handle->VALUE.value[aa + 1];

					protocol_descriptor_list_handle->VALUE.protocols[b].value = new BYTE[protocol_descriptor_list_handle->VALUE.protocols[b].additional_bits_for_size]();

					for (int c = 0; c < protocol_descriptor_list_handle->VALUE.protocols[b].additional_bits_for_size; c++)
						protocol_descriptor_list_handle->VALUE.protocols[b].value[c] = protocol_descriptor_list_handle->VALUE.value[aa + 1 + c + 1];
				}

				b++;
			}
		}

		for (int c = 0; c < protocol_descriptor_list_handle->VALUE.num_protocols; c++)
		{
			SDP::ATTRIBUTE_ID_ELEMENT* temp_protcol_id = new SDP::ATTRIBUTE_ID_ELEMENT();
			temp_protcol_id = (SDP::ATTRIBUTE_ID_ELEMENT*)(protocol_descriptor_list_handle->VALUE.protocols[c].value + 0);

			protocol_descriptor_list_handle->VALUE.protocols[c].element_protocol = temp_protcol_id;

			protocol_descriptor_list_handle->VALUE.protocols[c].protocol_id |= *(protocol_descriptor_list_handle->VALUE.protocols[c].value + 1);
			protocol_descriptor_list_handle->VALUE.protocols[c].protocol_id <<= 8;
			protocol_descriptor_list_handle->VALUE.protocols[c].protocol_id |= *(protocol_descriptor_list_handle->VALUE.protocols[c].value + 2);

			// TODO: tukaj naprej so lahko razlicni parametri za razlicne service in protokole

			if (protocol_descriptor_list_handle->VALUE.protocols[c].additional_bits_for_size > 3)
			{

				if (dd.service_class_id_in_use == SDP::Handsfree ||
					dd.service_class_id_in_use == SDP::Headset ||
					dd.service_class_id_in_use == SDP::Headset_Audio_Gateway ||
					dd.service_class_id_in_use == SDP::OBEXObjectPush ||
					dd.service_class_id_in_use == SDP::OBEXFileTransfer ||
					dd.service_class_id_in_use == SDP::HandsfreeAudioGateway ||
					dd.service_class_id_in_use == SDP::Phonebook_Access_PSE ||
					dd.service_class_id_in_use == SDP::Phonebook_Access ||
					dd.service_class_id_in_use == SDP::Message_Access_Server ||
					dd.service_class_id_in_use == SDP::Message_Access_Profile ||
					dd.service_class_id_in_use == SDP::GenericAudio
					)
				{
					protocol_descriptor_list_handle->VALUE.protocols[c].additional_parameters_flag = 1;
					protocol_descriptor_list_handle->VALUE.protocols[c].pdsp = new SDP::PROTOCOL_DESCRIPTOR_SPECIFIC_PARAMETER();
					protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->server_channel_num = *(protocol_descriptor_list_handle->VALUE.protocols[c].value + 4);
				}

				if (dd.service_class_id_in_use == SDP::AudioSource ||
					dd.service_class_id_in_use == SDP::AudioSink ||
					dd.service_class_id_in_use == SDP::A_V_RemoteControlTarget ||
					dd.service_class_id_in_use == SDP::A_V_RemoteControl ||
					dd.service_class_id_in_use == SDP::A_V_RemoteControlController ||
					dd.service_class_id_in_use == SDP::PANU ||
					dd.service_class_id_in_use == SDP::_NAP
					)
				{
					if (protocol_descriptor_list_handle->VALUE.protocols[c].protocol_id == SDP::_L2CAP)
					{
						protocol_descriptor_list_handle->VALUE.protocols[c].additional_parameters_flag = 1;
						protocol_descriptor_list_handle->VALUE.protocols[c].pdsp = new SDP::PROTOCOL_DESCRIPTOR_SPECIFIC_PARAMETER();

						protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->PSM |= *(protocol_descriptor_list_handle->VALUE.protocols[c].value + 4);
						protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->PSM <<= 8;
						protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->PSM |= *(protocol_descriptor_list_handle->VALUE.protocols[c].value + 5);
					}

					if (protocol_descriptor_list_handle->VALUE.protocols[c].protocol_id == SDP::_AVDTP ||
						protocol_descriptor_list_handle->VALUE.protocols[c].protocol_id == SDP::_AVCTP ||
						protocol_descriptor_list_handle->VALUE.protocols[c].protocol_id == SDP::_BNEP
						)
					{
						protocol_descriptor_list_handle->VALUE.protocols[c].additional_parameters_flag = 1;
						protocol_descriptor_list_handle->VALUE.protocols[c].pdsp = new SDP::PROTOCOL_DESCRIPTOR_SPECIFIC_PARAMETER();

						protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->Version |= *(protocol_descriptor_list_handle->VALUE.protocols[c].value + 4);
						protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->Version <<= 8;
						protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->Version |= *(protocol_descriptor_list_handle->VALUE.protocols[c].value + 5);
					}

					if (protocol_descriptor_list_handle->VALUE.protocols[c].protocol_id == SDP::_BNEP)
					{
						protocol_descriptor_list_handle->VALUE._BNEP_flag = 1;

						for (int cc = 0; cc < protocol_descriptor_list_handle->VALUE.protocols[c].additional_bits_for_size; cc++)
						{
							if (*(protocol_descriptor_list_handle->VALUE.protocols[c].value + cc) == 0x35)
							{
								protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->element_PANU = (SDP::ATTRIBUTE_ID_ELEMENT*)(protocol_descriptor_list_handle->VALUE.protocols[c].value + cc);

								int temp_size_BNEP = SDP::FUNCTIONS::getElementSize(protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->element_PANU->element.size, &(protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->additional_bits_flag_PANU));
								protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->additional_bits_for_size_PANU = temp_size_BNEP;

								if (protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->additional_bits_flag_PANU)
								{
									if (protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->additional_bits_for_size_PANU == 1)
									{
										protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->num_of_Supported_Network_Packet_Type_List_PANU = *(protocol_descriptor_list_handle->VALUE.protocols[c].value + cc + 1) / 3;
										protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List = new SHORT[protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->num_of_Supported_Network_Packet_Type_List_PANU]();

										int pos = 0;
										for (int aaa = 0; aaa < protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->num_of_Supported_Network_Packet_Type_List_PANU; aaa++)
										{
											pos = (3 * aaa);
											protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa] |= *(protocol_descriptor_list_handle->VALUE.protocols[c].value + cc + 2 + (pos + 1));
											protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa] <<= 8;
											protocol_descriptor_list_handle->VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa] |= *(protocol_descriptor_list_handle->VALUE.protocols[c].value + cc + 2 + (pos + 2));
										}
									}
									// TODO: naredi se za ostale velikosti 2 in 4
								}
							}
						}

					}

				}
			}
			else
			{
				protocol_descriptor_list_handle->VALUE.protocols[c].additional_parameters_flag = 0;
			}

















		}

		protocol_descriptor_list_handle->print<PROTOCOL_DESCRIPTOR_LIST::VV>(protocol_descriptor_list_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::FUNCTIONS::getAndParse_SERVICE_NAME(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_NAME ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ServiceName, SDP::ServiceName, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);

		SDP::SERVICE_NAME* service_name_handle = new SDP::SERVICE_NAME();

		int position = set_save_ATTRIBUTE_ELEMENT<SERVICE_NAME*, BYTE[]>(service_name_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<SERVICE_NAME*, BYTE[]>(service_name_handle, bssr_response, 5000, position);

		service_name_handle->VALUE.service_name = new char[service_name_handle->VALUE.size_bytes]();
		memcpy(service_name_handle->VALUE.service_name, service_name_handle->VALUE.value, service_name_handle->VALUE.size_bytes);

		service_name_handle->print<SERVICE_NAME::VV>(service_name_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::FUNCTIONS::getAndParse_PROVIDER_NAME(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_PROVIDER_NAME ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ProviderName, SDP::ProviderName, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);

		SDP::PROVIDER_NAME* provider_name_handle = new SDP::PROVIDER_NAME();

		int position = set_save_ATTRIBUTE_ELEMENT<PROVIDER_NAME*, BYTE[]>(provider_name_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<PROVIDER_NAME*, BYTE[]>(provider_name_handle, bssr_response, 5000, position);

		provider_name_handle->VALUE.provider_name = new char[provider_name_handle->VALUE.size_bytes]();
		memcpy(provider_name_handle->VALUE.provider_name, provider_name_handle->VALUE.value, provider_name_handle->VALUE.size_bytes);

		provider_name_handle->print<PROVIDER_NAME::VV>(provider_name_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::FUNCTIONS::getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::BluetoothProfileDescriptorList, SDP::BluetoothProfileDescriptorList, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);


		SDP::BLUETOOTH_PROFILE_DESCRIPTOR_LIST* bluetooth_profile_descriptor_list_handle = new SDP::BLUETOOTH_PROFILE_DESCRIPTOR_LIST();

		int position = set_save_ATTRIBUTE_ELEMENT<BLUETOOTH_PROFILE_DESCRIPTOR_LIST*, BYTE[]>(bluetooth_profile_descriptor_list_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<BLUETOOTH_PROFILE_DESCRIPTOR_LIST*, BYTE[]>(bluetooth_profile_descriptor_list_handle, bssr_response, 5000, position);


		// trenutno narejeno samo za en profile
		bluetooth_profile_descriptor_list_handle->VALUE.profile_UUID |= bluetooth_profile_descriptor_list_handle->VALUE.value[3];
		bluetooth_profile_descriptor_list_handle->VALUE.profile_UUID <<= 8;
		bluetooth_profile_descriptor_list_handle->VALUE.profile_UUID |= bluetooth_profile_descriptor_list_handle->VALUE.value[4];
		bluetooth_profile_descriptor_list_handle->VALUE.profile_version |= bluetooth_profile_descriptor_list_handle->VALUE.value[6];
		bluetooth_profile_descriptor_list_handle->VALUE.profile_version <<= 8;
		bluetooth_profile_descriptor_list_handle->VALUE.profile_version |= bluetooth_profile_descriptor_list_handle->VALUE.value[7];

		// TODO: popravi za primer ko jih je vec naenkrat


		bluetooth_profile_descriptor_list_handle->print<BLUETOOTH_PROFILE_DESCRIPTOR_LIST::VV>(bluetooth_profile_descriptor_list_handle->VALUE);


		return 1;
	}


	return 0;
}

int SDP::FUNCTIONS::getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::LanguageBaseAttributeIDList, SDP::LanguageBaseAttributeIDList, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);


		SDP::LANGUAGE_BASE_ATTRIBUTE_ID_LIST* language_base_attribute_id_list_handle = new SDP::LANGUAGE_BASE_ATTRIBUTE_ID_LIST();

		int position = set_save_ATTRIBUTE_ELEMENT<LANGUAGE_BASE_ATTRIBUTE_ID_LIST*, BYTE[]>(language_base_attribute_id_list_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<LANGUAGE_BASE_ATTRIBUTE_ID_LIST*, BYTE[]>(language_base_attribute_id_list_handle, bssr_response, 5000, position);


		// TODO: naredi ce je teh tripletov vec kot eden (trenutno je narejeno samo za enega)

		/*
			TRIPLET:
			example:
			0x09 0x65 0x6E 0x09 0x00 0x6A 0x09 0x01 0x00

			0x09 0x65 0x6E <-- identifier representing the natural language
			0x09 0x00 0x6A <-- identifier that specifies a character encoding used for the language
			0x09 0x01 0x00 <-- attribute ID that serves as the base attribute ID
		*/

		language_base_attribute_id_list_handle->VALUE.triplet_id_natural_lang |= language_base_attribute_id_list_handle->VALUE.value[1];
		language_base_attribute_id_list_handle->VALUE.triplet_id_natural_lang <<= 8;
		language_base_attribute_id_list_handle->VALUE.triplet_id_natural_lang |= language_base_attribute_id_list_handle->VALUE.value[2];

		language_base_attribute_id_list_handle->VALUE.triplet_id_char_encoding |= language_base_attribute_id_list_handle->VALUE.value[4];
		language_base_attribute_id_list_handle->VALUE.triplet_id_char_encoding <<= 8;
		language_base_attribute_id_list_handle->VALUE.triplet_id_char_encoding |= language_base_attribute_id_list_handle->VALUE.value[5];

		language_base_attribute_id_list_handle->VALUE.triplet_attribute_id |= language_base_attribute_id_list_handle->VALUE.value[7];
		language_base_attribute_id_list_handle->VALUE.triplet_attribute_id <<= 8;
		language_base_attribute_id_list_handle->VALUE.triplet_attribute_id |= language_base_attribute_id_list_handle->VALUE.value[8];

		language_base_attribute_id_list_handle->print<LANGUAGE_BASE_ATTRIBUTE_ID_LIST::VV>(language_base_attribute_id_list_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::FUNCTIONS::getAndParse_SERVICE_AVAILABILITY(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_AVAILABILITY ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ServiceAvailability, SDP::ServiceAvailability, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);


		// TODO: najdi en primer, da se lahko naredi do konca parsanje


		return 1;
	}



	return 0;
}

int SDP::FUNCTIONS::getAndParse_SERVICE_DESCRIPTION(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_DESCRIPTION ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ServiceDescription, SDP::ServiceDescription, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);

		SDP::SERVICE_DESCRIPTION* service_description_handle = new SDP::SERVICE_DESCRIPTION();

		int position = set_save_ATTRIBUTE_ELEMENT<SERVICE_DESCRIPTION*, BYTE[]>(service_description_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<SERVICE_DESCRIPTION*, BYTE[]>(service_description_handle, bssr_response, 5000, position);

		service_description_handle->VALUE.description = new char[service_description_handle->VALUE.size_bytes]();
		memcpy(service_description_handle->VALUE.description, service_description_handle->VALUE.value, service_description_handle->VALUE.size_bytes);

		service_description_handle->print<SERVICE_DESCRIPTION::VV>(service_description_handle->VALUE);

		return 1;
	}



	return 0;



	return 0;
}























/*********************************************************************************************************************/
/* PBAP SPECIFIC */

// FOR	 GoepL2CapPsm YOU CAN USE FROM MAP

int SDP::PBAP::getAndParse_SUPPORTED_REPOSITORIES_PBAP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SUPPORTED_REPOSITORIES_PBAP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::PBAP::SupportedRepositories, SDP::PBAP::SupportedRepositories, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::PBAP::SUPPORTED_REPOSITORIES* supported_repositories_handle = new SDP::PBAP::SUPPORTED_REPOSITORIES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::PBAP::SUPPORTED_REPOSITORIES*, BYTE[]>(supported_repositories_handle, bssr_response, 5000);

		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::PBAP::SUPPORTED_REPOSITORIES*, BYTE[]>(supported_repositories_handle, bssr_response, 5000, position);

		supported_repositories_handle->VALUE.srs = new SUPPORTED_REPOSITORIES_DATA_S(supported_repositories_handle->VALUE.value);

		supported_repositories_handle->print<SUPPORTED_REPOSITORIES::VV>(supported_repositories_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::PBAP::getAndParse_PBAP_SUPPORTED_FEATURES_PBAP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_PBAP_SUPPORTED_FEATURES_PBAP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::PBAP::PbapSupportedFeatures, SDP::PBAP::PbapSupportedFeatures, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::PBAP::PBAP_SUPPORTED_FEATURES* pbap_supported_features_handle = new SDP::PBAP::PBAP_SUPPORTED_FEATURES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::PBAP::PBAP_SUPPORTED_FEATURES*, BYTE[]>(pbap_supported_features_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::PBAP::PBAP_SUPPORTED_FEATURES*, BYTE[]>(pbap_supported_features_handle, bssr_response, 5000, position);

		// TODO: prevedi values kaj pomeni
		// TODO: poisci device ki ima verzijo 1.2 ali vec

		pbap_supported_features_handle->print<PBAP_SUPPORTED_FEATURES::VV>(pbap_supported_features_handle->VALUE);

		return 1;
	}

	return 0;
}


/*********************************************************************************************************************/
/* OBEX SPECIFIC */

// FOR	 GoepL2CapPsm YOU CAN USE FROM MAP

std::string SDP::OBEX::getSupportedFormatsString(BYTE data_arr[], int size)
{
	std::string temp = "";

	for(int aa = 0; aa < size; aa++)
		switch (data_arr[aa])
		{
			case 0x01:
				temp += "vCard 2.1\n";
			break;

			case 0x02:
				temp += "vCard 3.0\n";
				break;

			case 0x03:
				temp += "vCal 1.0\n";
				break;

			case 0x04:
				temp += "iCal 2.0\n";
				break;

			case 0x05:
				temp += "vNote\n";
				break;

			case 0x06:
				temp += "vMessage\n";
				break;

			case 0xff:
				temp += "any type of object\n";
				break;
		};

	return temp;
}

int SDP::OBEX::getAndParse_SERVICE_VERSION_OBEX(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_VERSION_OBEX ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::OBEX::ServiceVersion, SDP::OBEX::ServiceVersion, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::OBEX::SERVICE_VERSION* service_version_handle = new SDP::OBEX::SERVICE_VERSION();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::OBEX::SERVICE_VERSION*, BYTE[]>(service_version_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::OBEX::SERVICE_VERSION*, BYTE[]>(service_version_handle, bssr_response, 5000, position);

		// TODO: najdi neki primer zaradi parsanja
		
		service_version_handle->print<SERVICE_VERSION::VV>(service_version_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::OBEX::getAndParse_SUPPORTED_FORMATS_LIST_OBEX(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SUPPORTED_FORMATS_LIST_OBEX ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::OBEX::SupportedFormatsList, SDP::OBEX::SupportedFormatsList, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::OBEX::SUPPORTED_FORMATS* supported_formats_handle = new SDP::OBEX::SUPPORTED_FORMATS();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::OBEX::SUPPORTED_FORMATS*, BYTE[]>(supported_formats_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::OBEX::SUPPORTED_FORMATS*, BYTE[]>(supported_formats_handle, bssr_response, 5000, position);

		supported_formats_handle->VALUE.num_of_formats = supported_formats_handle->VALUE.size_bytes / 2;

		supported_formats_handle->VALUE.formats = new BYTE[supported_formats_handle->VALUE.num_of_formats]();

		for (int aa = 1, bb = 0; aa < supported_formats_handle->VALUE.size_bytes; aa += 2, bb++)
		{
			supported_formats_handle->VALUE.formats[bb] = supported_formats_handle->VALUE.value[aa];
		}
		supported_formats_handle->print<SUPPORTED_FORMATS::VV>(supported_formats_handle->VALUE);

		return 1;
	}

	return 0;
}



/*********************************************************************************************************************/
/* HFP SPECIFIC */


int SDP::HFP::getAndParse_NETWORK_HFP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_NETWORK_HFP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::HFP::Network, SDP::HFP::Network, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::HFP::NETWORK* network_handle = new SDP::HFP::NETWORK();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::HFP::NETWORK*, BYTE[]>(network_handle, bssr_response, 5000);

		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::HFP::NETWORK*, BYTE[]>(network_handle, bssr_response, 5000, position);

		network_handle->print<NETWORK::VV>(network_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::HFP::getAndParse_SUPPORTED_FEATURES_HFP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SUPPORTED_FEATURES_HFP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::HFP::SupportedFeatures, SDP::HFP::SupportedFeatures, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::HFP::SUPPORTED_FEATURES* supported_features_handle = new SDP::HFP::SUPPORTED_FEATURES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::HFP::SUPPORTED_FEATURES*, BYTE[]>(supported_features_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::HFP::SUPPORTED_FEATURES*, BYTE[]>(supported_features_handle, bssr_response, 5000, position);

		SHORT temp = 0x00;

		temp |= supported_features_handle->VALUE.value[0];
		temp <<= 8;
		temp |= supported_features_handle->VALUE.value[1];


		supported_features_handle->VALUE.supported_features_value = temp;

		supported_features_handle->VALUE.sfds = new SUPPORTED_FEATURES_DATA_S(&temp);

		supported_features_handle->print<SUPPORTED_FEATURES::VV>(supported_features_handle->VALUE);

		return 1;
	}

	return 0;
}



/*********************************************************************************************************************/
/* PNPINFO SPECIFIC */

int SDP::PNPINFO::getAndParse_SPECIFICATION_ID_PNPINFO(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SPECIFICATION_ID_PNPINFO ***\n");

	BYTE bssr_response[5000]{ 0 };
	SDP::PNPINFO::INFO* ttt_handle = new SDP::PNPINFO::INFO();

	BOOL test = FALSE;

	for (SHORT bb = SpecificationID; bb < (VendorIDSource + 0x01); bb++)
	{
		printf("0x%04X\n",bb);

		test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, bb, bb, bssr_response, 5000);

		if (test)
		{
			printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

			SDP::FUNCTIONS::printResponse(bssr_response);
			int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::PNPINFO::INFO*, BYTE[]>(ttt_handle, bssr_response, 5000);

			position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::PNPINFO::INFO*, BYTE[]>(ttt_handle, bssr_response, 5000, position);

			if (bb == PrimaryRecord)
			{
				ttt_handle->setIDdata<BOOL>(bb, ttt_handle->VALUE.value[0]);
			}
			else
			{
				SHORT temp = 0x00;
				temp |= ttt_handle->VALUE.value[0];
				temp <<= 8;
				temp |= ttt_handle->VALUE.value[1];
				ttt_handle->setIDdata<SHORT>(bb, temp);
			}
		}
	}

	ttt_handle->print<INFO_S::VV>(ttt_handle->VALUE);

	return 1;
}



/*********************************************************************************************************************/
/* A2DP SPECIFIC */

int SDP::A2DP::getAndParse_SUPPORTED_FEATURES_A2DP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SUPPORTED_FEATURES_A2DP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::A2DP::SupportedFeatures, SDP::A2DP::SupportedFeatures, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::A2DP::SUPPORTED_FEATURES* supported_features_handle = new SDP::A2DP::SUPPORTED_FEATURES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::A2DP::SUPPORTED_FEATURES*, BYTE[]>(supported_features_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::A2DP::SUPPORTED_FEATURES*, BYTE[]>(supported_features_handle, bssr_response, 5000, position);

		
		SHORT temp = 0x00;
		temp |= supported_features_handle->VALUE.value[0];
		temp <<= 8;
		temp |= supported_features_handle->VALUE.value[1];

		supported_features_handle->VALUE.supported_features_value = temp;

		supported_features_handle->VALUE.sfds = new SUPPORTED_FEATURES_DATA_S(&supported_features_handle->VALUE.supported_features_value);


		supported_features_handle->print<SUPPORTED_FEATURES::VV>(supported_features_handle->VALUE);

		return 1;
	}

	return 0;
}




/*********************************************************************************************************************/
/* AVRCP SPECIFIC */


int SDP::AVRCP::getAndParse_SUPPORTED_FEATURES_AVRCP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SUPPORTED_FEATURES_AVRCP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::AVRCP::SupportedFeatures, SDP::AVRCP::SupportedFeatures, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::AVRCP::SUPPORTED_FEATURES* supported_features_handle = new SDP::AVRCP::SUPPORTED_FEATURES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::AVRCP::SUPPORTED_FEATURES*, BYTE[]>(supported_features_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::AVRCP::SUPPORTED_FEATURES*, BYTE[]>(supported_features_handle, bssr_response, 5000, position);

		SHORT temp = 0x00;

		temp |= supported_features_handle->VALUE.value[0];
		temp <<= 8;
		temp |= supported_features_handle->VALUE.value[1];


		supported_features_handle->VALUE.supported_features_value = temp;

		supported_features_handle->VALUE.sfds = new SUPPORTED_FEATURES_DATA_S(&temp);

		supported_features_handle->print<SUPPORTED_FEATURES::VV>(supported_features_handle->VALUE);

		return 1;
	}

	return 0;
}



/*********************************************************************************************************************/
/* HSP SPECIFIC */


int SDP::HSP::getAndParse_REMOTE_AUDIO_VOLUME_CONTROL_HSP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_REMOTE_AUDIO_VOLUME_CONTROL_HSP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::HSP::RemoteAudioVolumeControl, SDP::HSP::RemoteAudioVolumeControl, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::HSP::REMOTE_AUDIO_VOLUME_CONTROL* remote_audio_volume_control_handle = new SDP::HSP::REMOTE_AUDIO_VOLUME_CONTROL();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::HSP::REMOTE_AUDIO_VOLUME_CONTROL*, BYTE[]>(remote_audio_volume_control_handle, bssr_response, 5000);


		position = FUNCTIONS::set_save_VALUE_ELEMENT<SDP::HSP::REMOTE_AUDIO_VOLUME_CONTROL*, BYTE[]>(remote_audio_volume_control_handle, bssr_response, 5000, position);


		remote_audio_volume_control_handle->print<REMOTE_AUDIO_VOLUME_CONTROL::VV>(remote_audio_volume_control_handle->VALUE);

		return 1;
	}

	return 0;
}

