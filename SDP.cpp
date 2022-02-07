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


void SDP::FUNCTIONS::printResponse( BYTE bssr_response[])
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



template<class A, class B>
int SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT(A id_handle, B res, int res_length)
{
	int position = sizeof(BTH_SDP_STREAM_RESPONSE) + 1 + 0;
	
	SDP::PATTRIBUTE_ID_ELEMENT record_handle_element = new SDP::ATTRIBUTE_ID_ELEMENT();
	record_handle_element = (SDP::PATTRIBUTE_ID_ELEMENT)(res + position);
	
	id_handle->attr_id = new ATTR_ID();
	id_handle->attr_id->element = record_handle_element;



	int temp_size = SDP::FUNCTIONS::getElementSize(id_handle->attr_id->element->element.size, &(id_handle->attr_id->additional_bits_flag));

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
int SDP::FUNCTIONS::set_save_VALUE_ELEMENT(A id_handle, B res, int res_length, int position)
{
	SDP::PATTRIBUTE_ID_ELEMENT record_handle_element_2 = new SDP::ATTRIBUTE_ID_ELEMENT();
	record_handle_element_2 = (SDP::PATTRIBUTE_ID_ELEMENT)(res + position);

	id_handle->VALUE.element = record_handle_element_2;

	int temp_size_VALUE = SDP::FUNCTIONS::getElementSize(id_handle->VALUE.element->element.size, &(id_handle->VALUE.additional_bits_flag));

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




int SDP::FUNCTIONS::getAndParse_SERVICE_RECORD_HANDLE(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_RECORD_HANDLE ***\n");
	
	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ServiceRecordHandle, SDP::ServiceRecordHandle, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse( bssr_response);
	
		SDP::PSERVICE_RECORD_HANDLE record_handle = new SDP::SERVICE_RECORD_HANDLE();

		int position = set_save_ATTRIBUTE_ELEMENT<PSERVICE_RECORD_HANDLE, BYTE[]>(record_handle, bssr_response, 5000);



		position = set_save_VALUE_ELEMENT<PSERVICE_RECORD_HANDLE, BYTE[]>(record_handle, bssr_response, 5000, position);

		
		record_handle->print();
		
		
		
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

		printResponse( bssr_response);


		SDP::PSERVICE_CLASS_ID_LIST class_id_handle = new SDP::SERVICE_CLASS_ID_LIST();

		int position = set_save_ATTRIBUTE_ELEMENT<PSERVICE_CLASS_ID_LIST, BYTE[]>(class_id_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<PSERVICE_CLASS_ID_LIST, BYTE[]>(class_id_handle, bssr_response, 5000, position);


		
		class_id_handle->VALUE.num_classes = class_id_handle->VALUE.size_bytes / 3;



		//printf("NUM classes: %d\n", class_id_handle->VALUE.num_classes);

		class_id_handle->VALUE.classes = new SDP::SERVICE_CLASS[class_id_handle->VALUE.num_classes]();

		for (int a = 0, b=0; a < class_id_handle->VALUE.size_bytes; a+=3, b++)
		{
			SDP::ATTRIBUTE_ID_ELEMENT* temp_att_id = new SDP::ATTRIBUTE_ID_ELEMENT();
			temp_att_id = (SDP::ATTRIBUTE_ID_ELEMENT*)(class_id_handle->VALUE.value + a);

			class_id_handle->VALUE.classes[b].element = temp_att_id;

			int temp_size_1 = SDP::FUNCTIONS::getElementSize(class_id_handle->VALUE.classes[b].element->element.size, &(class_id_handle->VALUE.classes[b].additional_bits_flag));

			class_id_handle->VALUE.classes[b].value |= *(class_id_handle->VALUE.value + a + 1);
			class_id_handle->VALUE.classes[b].value <<= 8;
			class_id_handle->VALUE.classes[b].value |= *(class_id_handle->VALUE.value + a + 2);
		}

		//printf("\n");
		//printf("\n");

		class_id_handle->print();

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

		printResponse( bssr_response);


		SDP::PROTOCOL_DESCRIPTOR_LIST *protocol_descriptor_list_handle = new SDP::PROTOCOL_DESCRIPTOR_LIST();

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

		protocol_descriptor_list_handle->print();

		return 1;
	}

	return 0;
}

int SDP::FUNCTIONS::getAndParse_SERVICE_NAME (ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_NAME ***\n");
	
	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ServiceName, SDP::ServiceName, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse( bssr_response);

		SDP::SERVICE_NAME* service_name_handle = new SDP::SERVICE_NAME();

		int position = set_save_ATTRIBUTE_ELEMENT<SERVICE_NAME*, BYTE[]>(service_name_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<SERVICE_NAME*, BYTE[]>(service_name_handle, bssr_response, 5000, position);

		
		service_name_handle->print();



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

	
		bluetooth_profile_descriptor_list_handle->print();


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

		printResponse( bssr_response);


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

		language_base_attribute_id_list_handle->print();

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

		printResponse( bssr_response);


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

		printResponse( bssr_response);

		SDP::SERVICE_DESCRIPTION* service_description_handle = new SDP::SERVICE_DESCRIPTION();

		int position = set_save_ATTRIBUTE_ELEMENT<SERVICE_DESCRIPTION*, BYTE[]>(service_description_handle, bssr_response, 5000);


		position = set_save_VALUE_ELEMENT<SERVICE_DESCRIPTION*, BYTE[]>(service_description_handle, bssr_response, 5000, position);

		
		service_description_handle->print();

		return 1;
	}



	return 0;



	return 0;
}



/*********************************************************************************************************************/
/* NAP and PANU SPECIFIC */

std::string SDP::NAP::getSecurityDescriptionString(SHORT type)
{
	std::string temp;

	switch (type)
	{
		case 0x0000:
			temp = "None";
		break;

		case 0x0001:
			temp = "Service - level enforced Security";
		break;

		case 0x0002:
			temp = "802.1x Security";
		break;
	}

	return temp;
}

std::string SDP::NAP::getNetAccessTypeString(SHORT type)
{
	std::string temp;

	switch (type)
	{
		case 0x0000:
			temp = "PSTN";
		break;

		case 0x0001:
			temp = "ISDN";
		break;

		case 0x0002:
			temp = "DSL";
		break;

		case 0x0003:
			temp = "Cable Modem";
		break;

		case 0x0004:
			temp = "10Mb Ethernet";
		break;

		case 0x0005:
			temp = "100Mb Ethernet";
		break;

		case 0x0006:
			temp = "4 Mb Token Ring";
		break;

		case 0x0007:
			temp = "16 Mb Token Ring";
		break;

		case 0x0008:
			temp = "100 Mb Token Ring";
		break;

		case 0x0009:
			temp = "FDDI";
		break;

		case 0x000A:
			temp = "GSM";
		break;

		case 0x000B:
			temp = "CDMA";
		break;

		case 0x000C:
			temp = "GPRS";
		break;

		case 0x000D:
			temp = "3G Cellular";
		break;

		case 0xFFFE:
			temp = "other";
		break;
	}

	return temp;
}

int SDP::NAP::getAndParse_SECURITY_DESCRIPTION_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SECURITY_DESCRIPTION_PAN ***\n");
	
	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::NAP::SecurityDescription, SDP::NAP::SecurityDescription, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse( bssr_response);


		SDP::NAP::SECURITY_DESCRIPTION* security_description_handle = new SDP::NAP::SECURITY_DESCRIPTION();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::NAP::SECURITY_DESCRIPTION*, BYTE[]>(security_description_handle, bssr_response, 5000);



		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::NAP::SECURITY_DESCRIPTION*, BYTE[]>(security_description_handle, bssr_response, 5000, position);

		
		security_description_handle->VALUE.security_value |= security_description_handle->VALUE.value[0];
		security_description_handle->VALUE.security_value <<= 8;
		security_description_handle->VALUE.security_value |= security_description_handle->VALUE.value[1];




		security_description_handle->print();

		return 1;
	}




	return 0;
}

int SDP::NAP::getAndParse_NET_ACCESS_TYPE_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_NET_ACCESS_TYPE_PAN ***\n");
	
	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::NAP::NetAccessType, SDP::NAP::NetAccessType, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse( bssr_response);


		SDP::NAP::NET_ACCESS_TYPE* net_access_type_handle = new SDP::NAP::NET_ACCESS_TYPE();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::NAP::NET_ACCESS_TYPE*, BYTE[]>(net_access_type_handle, bssr_response, 5000);



		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::NAP::NET_ACCESS_TYPE*, BYTE[]>(net_access_type_handle, bssr_response, 5000, position);

		
		net_access_type_handle->VALUE.NetAccessType |= net_access_type_handle->VALUE.value[0];
		net_access_type_handle->VALUE.NetAccessType <<= 8;
		net_access_type_handle->VALUE.NetAccessType |= net_access_type_handle->VALUE.value[1];


		net_access_type_handle->print();



		return 1;
	}

	return 0;
}

int SDP::NAP::getAndParse_MAX_NET_ACCESS_RATE_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_MAX_NET_ACCESS_RATE_PAN ***\n");
	
	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::NAP::MaxNetAccessrate, SDP::NAP::MaxNetAccessrate, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse( bssr_response);

		SDP::NAP::MAX_NET_ACCESS_RATE* max_net_access_rate_handle = new SDP::NAP::MAX_NET_ACCESS_RATE();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::NAP::MAX_NET_ACCESS_RATE*, BYTE[]>(max_net_access_rate_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::NAP::MAX_NET_ACCESS_RATE*, BYTE[]>(max_net_access_rate_handle, bssr_response, 5000, position);

		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate |= max_net_access_rate_handle->VALUE.value[0];
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate <<= 8;
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate |= max_net_access_rate_handle->VALUE.value[1];
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate <<= 8;
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate |= max_net_access_rate_handle->VALUE.value[2];
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate <<= 8;
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate |= max_net_access_rate_handle->VALUE.value[3];
		

		max_net_access_rate_handle->print();

		return 1;
	}

	return 0;
}



/*********************************************************************************************************************/
/* MAP SPECIFIC */

std::string SDP::MAP::getMessageTypesString(SUPPORTED_FEATURES_MESSAGES_S* sfm)
{
	std::string temp;

	if (sfm->ttt->a0)
	{
		temp = "EMAIL";
	}

	if (sfm->ttt->a1)
	{
		temp = "SMS_GSM";
	}

	if (sfm->ttt->a2)
	{
		temp = "SMS_CDMA";
	}

	if (sfm->ttt->a3)
	{
		temp = "MMS";
	}

	if (sfm->ttt->a4)
	{
		temp = "IM";
	}

	return temp;
}

std::string SDP::MAP::getSupportedFeaturesString(SUPPORTED_FEATURES_MESSAGES_S* sfm)
{
	std::string temp;

	if (sfm->aaa->a0)
	{
		temp = "Notification Registration Feature";
	}

	if (sfm->aaa->a1)
	{
		temp = "Notification Feature";
	}

	if (sfm->aaa->a2)
	{
		temp = "Browsing Feature";
	}

	if (sfm->aaa->a3)
	{
		temp = "Uploading Feature";
	}

	if (sfm->aaa->a4)
	{
		temp = "Delete Feature";
	}

	if (sfm->aaa->a5)
	{
		temp = "Instance Information Feature";
	}

	if (sfm->aaa->a6)
	{
		temp = " Extended Event Report 1.1";
	}

	if (sfm->aaa->a7)
	{
		temp = "Event Report Version 1.2";
	}

	if (sfm->aaa->a8)
	{
		temp = "Message Format Version 1.1";
	}

	if (sfm->aaa->a9)
	{
		temp = "MessagesListing Format Version 1.1";
	}

	if (sfm->aaa->a10)
	{
		temp = "Persistent Message Handles";
	}

	if (sfm->aaa->a11)
	{
		temp = "Database Identifier";
	}

	if (sfm->aaa->a12)
	{
		temp = "Folder Version Counter";
	}

	if (sfm->aaa->a13)
	{
		temp = "Conversation Version Counters";
	}

	if (sfm->aaa->a14)
	{
		temp = "Participant Presence Change Notification";
	}

	if (sfm->aaa->a15)
	{
		temp = "Participant Chat State Change Notification";
	}

	if (sfm->aaa->a16)
	{
		temp = "PBAP Contact Cross Reference";
	}

	if (sfm->aaa->a17)
	{
		temp = "Notification Filtering";
	}

	if (sfm->aaa->a18)
	{
		temp = "UTC Offset Timestamp Format";
	}

	if (sfm->aaa->a19)
	{
		temp = "MapSupportedFeatures in Connect Request";
	}

	if (sfm->aaa->a20)
	{
		temp = "Conversation listing";
	}

	if (sfm->aaa->a21)
	{
		temp = "Owner Status";
	}

	if (sfm->aaa->a22)
	{
		temp = "Message Forwarding";
	}

	return temp;
}




int SDP::MAP::getAndParse_GOEPL2CAPPSM_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_GOEPL2CAPPSM_MAP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::MAP::GoepL2capPsm, SDP::MAP::GoepL2capPsm, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::MAP::GOEPL2CAPPSM* goepl2cappsm_handle = new SDP::MAP::GOEPL2CAPPSM();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::MAP::GOEPL2CAPPSM*, BYTE[]>(goepl2cappsm_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::MAP::GOEPL2CAPPSM*, BYTE[]>(goepl2cappsm_handle, bssr_response, 5000, position);

		// TODO: prevedi pomen vrednosti


		goepl2cappsm_handle->print();


		return 1;
	}


	return 0;
}

int SDP::MAP::getAndParse_SUPPORTED_MESSAGE_TYPES_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SUPPORTED_MESSAGE_TYPES_MAP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::MAP::SupportedMessageTypes, SDP::MAP::SupportedMessageTypes, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::MAP::SUPPORTED_MESSAGE_TYPES* supported_message_types_handle = new SDP::MAP::SUPPORTED_MESSAGE_TYPES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::MAP::SUPPORTED_MESSAGE_TYPES*, BYTE[]>(supported_message_types_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::MAP::SUPPORTED_MESSAGE_TYPES*, BYTE[]>(supported_message_types_handle, bssr_response, 5000, position);

		// TODO: prevedi pomen vrednosti

		supported_message_types_handle->VALUE.sfm = new SUPPORTED_FEATURES_MESSAGES_S(supported_message_types_handle->VALUE.value);
		printf("0x%02X - 0x%02X - 0x%02X - 0x%02X - 0x%02X\n",
			supported_message_types_handle->VALUE.sfm->ttt->a0,
			supported_message_types_handle->VALUE.sfm->ttt->a1,
			supported_message_types_handle->VALUE.sfm->ttt->a2,
			supported_message_types_handle->VALUE.sfm->ttt->a3,
			supported_message_types_handle->VALUE.sfm->ttt->a4
		);



		supported_message_types_handle->print();



		return 1;
	}

	return 0;
}

int SDP::MAP::getAndParse_MAS_INSTANCE_ID_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_MAS_INSTANCE_ID_MAP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::MAP::MASInstanceID, SDP::MAP::MASInstanceID, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::MAP::MAS_INSTANCE_ID* mas_instance_id_handle = new SDP::MAP::MAS_INSTANCE_ID();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::MAP::MAS_INSTANCE_ID*, BYTE[]>(mas_instance_id_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::MAP::MAS_INSTANCE_ID*, BYTE[]>(mas_instance_id_handle, bssr_response, 5000, position);

		// TODO: prevedi pomen vrednosti


		mas_instance_id_handle->print();



		return 1;
	}

	return 0;
}

int SDP::MAP::getAndParse_MAP_SUPPORTED_FEATURES_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_MAP_SUPPORTED_FEATURES_MAP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::MAP::MapSupportedFeatures, SDP::MAP::MapSupportedFeatures, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::MAP::MAP_SUPPORTED_FEATURES* map_supported_features_handle = new SDP::MAP::MAP_SUPPORTED_FEATURES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::MAP::MAP_SUPPORTED_FEATURES*, BYTE[]>(map_supported_features_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::MAP::MAP_SUPPORTED_FEATURES*, BYTE[]>(map_supported_features_handle, bssr_response, 5000, position);

		// TODO: prevedi pomen vrednosti

		DWORD temp = 0x00;

		temp |= map_supported_features_handle->VALUE.value[0];
		temp <<= 8;
		temp |= map_supported_features_handle->VALUE.value[1];
		temp <<= 8;
		temp |= map_supported_features_handle->VALUE.value[2];
		temp <<= 8;
		temp |= map_supported_features_handle->VALUE.value[3];

		map_supported_features_handle->VALUE.sfm = new SUPPORTED_FEATURES_MESSAGES_S(&temp);

		printf("0x%02X - 0x%02X - 0x%02X - 0x%02X - 0x%02X - 0x%02X - 0x%02X - 0x%02X - 0x%02X\n",
			map_supported_features_handle->VALUE.sfm->aaa->a0,
			map_supported_features_handle->VALUE.sfm->aaa->a1,
			map_supported_features_handle->VALUE.sfm->aaa->a2,
			map_supported_features_handle->VALUE.sfm->aaa->a3,
			map_supported_features_handle->VALUE.sfm->aaa->a4,
			map_supported_features_handle->VALUE.sfm->aaa->a5,
			map_supported_features_handle->VALUE.sfm->aaa->a6,
			map_supported_features_handle->VALUE.sfm->aaa->a7,
			map_supported_features_handle->VALUE.sfm->aaa->a8
		);





		map_supported_features_handle->print();



		return 1;
	}

	return 0;
}










