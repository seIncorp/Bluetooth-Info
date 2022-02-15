#include "main.h"




int SDP::SUB_FUNCTIONS::getElementSize(BYTE size, int* add_bits)
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

std::string SDP::SUB_FUNCTIONS::getElementTypeString(BYTE type)
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

std::string SDP::SUB_FUNCTIONS::getProtocolTypeString(SHORT type)
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

std::string SDP::SUB_FUNCTIONS::getNetworkPacketTypeString(SHORT type)
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






void SDP::FUNCTIONS::SDP_INIT_CONNECT::init_for_IOCTL_BTH_SDP_CONNECT(char add[], DEVICE_DATA_SDP* device_data_sdp)
{
	device_data_sdp->btaddr = new BTH_ADDR();

	if (IOCTL_S::str2ba(add, device_data_sdp->btaddr) == 1)
		printf("str2ba ERROR\n");
	device_data_sdp->bsc = new BTH_SDP_CONNECT();

	device_data_sdp->bsc->bthAddress = *(device_data_sdp->btaddr);

	dd.bResult = FALSE;
	dd.junk = 0;
}

int SDP::FUNCTIONS::SDP_INIT_CONNECT::call_IOCTL_BTH_SDP_CONNECT(DEVICE_DATA_SDP* device_data_sdp)
{
	device_data_sdp->bResult = DeviceIoControl(
		dd.hDevice,												// device to be queried
		IOCTL_BTH_SDP_CONNECT,									// operation to perform
		device_data_sdp->bsc, sizeof(*device_data_sdp->bsc),	// no input buffer
		device_data_sdp->bsc, sizeof(*device_data_sdp->bsc),    // output buffer
		&dd.junk,												// # bytes returned
		(LPOVERLAPPED)NULL										// synchronous I/O
	);

	IOCTL_S::printErrorMessage(GetLastError());

	return device_data_sdp->bResult;
}


void SDP::FUNCTIONS::SDP_SERVICE_SEARCH::init_for_IOCTL_BTH_SDP_SERVICE_SEARCH(DEVICE_DATA_SDP* device_data_sdp)
{
	// TODO: preveri ali je res tole uporabno
	dd.service_class_id_in_use = device_data_sdp->current_used_service;

	device_data_sdp->bsssr = new BTH_SDP_SERVICE_SEARCH_REQUEST();
	device_data_sdp->bsssr->HANDLE_SDP_FIELD_NAME = device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME;
	device_data_sdp->bsssr->uuids[0].u.uuid16 = device_data_sdp->current_used_service;
	device_data_sdp->bsssr->uuids[0].uuidType = SDP_ST_UUID16;


}

int SDP::FUNCTIONS::SDP_SERVICE_SEARCH::call_IOCTL_BTH_SDP_SERVICE_SEARCH(DEVICE_DATA_SDP* device_data_sdp)
{
	device_data_sdp->sdp_service_search_res = DeviceIoControl(
		dd.hDevice,															// device to be queried
		IOCTL_BTH_SDP_SERVICE_SEARCH,										// operation to perform
		device_data_sdp->bsssr, sizeof(*device_data_sdp->bsssr),            // no input buffer
		device_data_sdp->buffer_res, sizeof(device_data_sdp->buffer_res),   // output buffer
		&dd.junk,															// # bytes returned
		(LPOVERLAPPED)NULL												// synchronous I/O
	);

	IOCTL_S::printErrorMessage(GetLastError());

	return device_data_sdp->sdp_service_search_res;
}


BOOL SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::call_IOCTL_BTH_SDP_ATTRIBUTE_SEARCH(BTH_SDP_ATTRIBUTE_SEARCH_REQUEST* bsasr, BYTE bssr_response[], int res_length)
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
	IOCTL_S::printErrorMessage(err);

	printf("-- %d\n", dd.junk);

	return test_sdp_call_222;
}

BOOL SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(ULONG recordHandle, HANDLE_SDP_TYPE aa, USHORT minAttr, USHORT maxAttr, BYTE res[], int res_length)
{
	BTH_SDP_ATTRIBUTE_SEARCH_REQUEST* bsasr = new BTH_SDP_ATTRIBUTE_SEARCH_REQUEST();
	bsasr->HANDLE_SDP_FIELD_NAME = aa;
	bsasr->recordHandle = recordHandle;
	bsasr->range[0].minAttribute = minAttr;
	bsasr->range[0].maxAttribute = maxAttr;

	//BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test_sdp_call_222 = false;
	test_sdp_call_222 = SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::call_IOCTL_BTH_SDP_ATTRIBUTE_SEARCH(bsasr, res, res_length);

	return test_sdp_call_222;
}


void SDP::FUNCTIONS::SDP_INIT_DISCONNECT::init_for_IOCTL_BTH_SDP_DISCONNECT(DEVICE_DATA_SDP* device_data_sdp)
{
	device_data_sdp->bsd = new BTH_SDP_DISCONNECT();
	device_data_sdp->bsd->HANDLE_SDP_FIELD_NAME = device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME;
}

int SDP::FUNCTIONS::SDP_INIT_DISCONNECT::call_IOCTL_BTH_SDP_DISCONNECT(DEVICE_DATA_SDP* device_data_sdp)
{
	device_data_sdp->disconnection_res = DeviceIoControl(
		dd.hDevice,												// device to be queried
		IOCTL_BTH_SDP_DISCONNECT,								// operation to perform
		device_data_sdp->bsd, sizeof(*device_data_sdp->bsd),	// no input buffer
		NULL, 0,												// output buffer
		&dd.junk,												// # bytes returned
		(LPOVERLAPPED)NULL										// synchronous I/O
	);

	IOCTL_S::printErrorMessage(GetLastError());

	if (device_data_sdp->disconnection_res)
	{
		printf("DISCONNECTED FROM DEVICE!!\n");

		return 1;
	}

	return 0;
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



/*
	TODO:

	razmisli kako bi zmanjsal kodo za spodnje funkcije

	ker prvih 6 vrstic so vedno iste

	npr. s template in se potem klice posamezno funkcijo na podlagi kateri service je

*/




void SDP::FUNCTIONS::parse_SERVICE_CLASS_ID_LIST(PSERVICE_CLASS_ID_LIST handle)
{
	handle->VALUE.num_classes = handle->VALUE.size_bytes / 3;
	handle->VALUE.classes = new SDP::SERVICE_CLASS[handle->VALUE.num_classes]();

	for (int a = 0, b = 0; a < handle->VALUE.size_bytes; a += 3, b++)
	{
		SDP::ATTRIBUTE_ID_ELEMENT* temp_att_id = new SDP::ATTRIBUTE_ID_ELEMENT();
		temp_att_id = (SDP::ATTRIBUTE_ID_ELEMENT*)(handle->VALUE.value + a);

		handle->VALUE.classes[b].element = temp_att_id;

		int temp_size_1 = SDP::SUB_FUNCTIONS::getElementSize(handle->VALUE.classes[b].element->element.size, &(handle->VALUE.classes[b].additional_bits_flag));

		handle->VALUE.classes[b].value |= *(handle->VALUE.value + a + 1);
		handle->VALUE.classes[b].value <<= 8;
		handle->VALUE.classes[b].value |= *(handle->VALUE.value + a + 2);
	}
}

void SDP::FUNCTIONS::parse_PROTOCOL_DESCRIPTOR_LIST(PPROTOCOL_DESCRIPTOR_LIST handle)
{
	/* presteje se koliko je protokolov */
	handle->VALUE.num_protocols = 0;

	for (int aa = 0; aa < handle->VALUE.size_bytes; aa++)
	{
		if (handle->VALUE.value[aa] == 0x35)
		{
			handle->VALUE.num_protocols++;
		}
	}
	handle->VALUE.protocols = new SDP::PROTOCOL_DESCRIPTOR[handle->VALUE.num_protocols]();

	/* napolnejo se podatki za vsak protokol posebej */
	for (int aa = 0, b = 0; aa < handle->VALUE.size_bytes; aa++)
	{
		if (handle->VALUE.value[aa] == 0x35)
		{
			SDP::ATTRIBUTE_ID_ELEMENT* temp_att_id = new SDP::ATTRIBUTE_ID_ELEMENT();
			temp_att_id = (SDP::ATTRIBUTE_ID_ELEMENT*)(handle->VALUE.value + aa);

			handle->VALUE.protocols[b].element = temp_att_id;

			int temp_size_v_1 = SDP::SUB_FUNCTIONS::getElementSize(handle->VALUE.protocols[b].element->element.size, &(handle->VALUE.protocols[b].additional_bits_flag));

			if (handle->VALUE.additional_bits_flag == 1)
			{
				handle->VALUE.protocols[b].additional_bits_for_size = handle->VALUE.value[aa + 1];

				handle->VALUE.protocols[b].value = new BYTE[handle->VALUE.protocols[b].additional_bits_for_size]();

				for (int c = 0; c < handle->VALUE.protocols[b].additional_bits_for_size; c++)
					handle->VALUE.protocols[b].value[c] = handle->VALUE.value[aa + 1 + c + 1];
			}

			b++;
		}
	}

	for (int c = 0; c < handle->VALUE.num_protocols; c++)
	{
		SDP::ATTRIBUTE_ID_ELEMENT* temp_protcol_id = new SDP::ATTRIBUTE_ID_ELEMENT();
		temp_protcol_id = (SDP::ATTRIBUTE_ID_ELEMENT*)(handle->VALUE.protocols[c].value + 0);

		handle->VALUE.protocols[c].element_protocol = temp_protcol_id;

		handle->VALUE.protocols[c].protocol_id |= *(handle->VALUE.protocols[c].value + 1);
		handle->VALUE.protocols[c].protocol_id <<= 8;
		handle->VALUE.protocols[c].protocol_id |= *(handle->VALUE.protocols[c].value + 2);

		// TODO: tukaj naprej so lahko razlicni parametri za razlicne service in protokole

		if (handle->VALUE.protocols[c].additional_bits_for_size > 3)
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
				handle->VALUE.protocols[c].additional_parameters_flag = 1;
				handle->VALUE.protocols[c].pdsp = new SDP::PROTOCOL_DESCRIPTOR_SPECIFIC_PARAMETER();
				handle->VALUE.protocols[c].pdsp->server_channel_num = *(handle->VALUE.protocols[c].value + 4);
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
				if (handle->VALUE.protocols[c].protocol_id == SDP::_L2CAP)
				{
					handle->VALUE.protocols[c].additional_parameters_flag = 1;
					handle->VALUE.protocols[c].pdsp = new SDP::PROTOCOL_DESCRIPTOR_SPECIFIC_PARAMETER();

					handle->VALUE.protocols[c].pdsp->PSM |= *(handle->VALUE.protocols[c].value + 4);
					handle->VALUE.protocols[c].pdsp->PSM <<= 8;
					handle->VALUE.protocols[c].pdsp->PSM |= *(handle->VALUE.protocols[c].value + 5);
				}

				if (handle->VALUE.protocols[c].protocol_id == SDP::_AVDTP ||
					handle->VALUE.protocols[c].protocol_id == SDP::_AVCTP ||
					handle->VALUE.protocols[c].protocol_id == SDP::_BNEP
					)
				{
					handle->VALUE.protocols[c].additional_parameters_flag = 1;
					handle->VALUE.protocols[c].pdsp = new SDP::PROTOCOL_DESCRIPTOR_SPECIFIC_PARAMETER();

					handle->VALUE.protocols[c].pdsp->Version |= *(handle->VALUE.protocols[c].value + 4);
					handle->VALUE.protocols[c].pdsp->Version <<= 8;
					handle->VALUE.protocols[c].pdsp->Version |= *(handle->VALUE.protocols[c].value + 5);
				}

				if (handle->VALUE.protocols[c].protocol_id == SDP::_BNEP)
				{
					handle->VALUE._BNEP_flag = 1;

					for (int cc = 0; cc < handle->VALUE.protocols[c].additional_bits_for_size; cc++)
					{
						if (*(handle->VALUE.protocols[c].value + cc) == 0x35)
						{
							handle->VALUE.protocols[c].pdsp->element_PANU = (SDP::ATTRIBUTE_ID_ELEMENT*)(handle->VALUE.protocols[c].value + cc);

							int temp_size_BNEP = SDP::SUB_FUNCTIONS::getElementSize(handle->VALUE.protocols[c].pdsp->element_PANU->element.size, &(handle->VALUE.protocols[c].pdsp->additional_bits_flag_PANU));
							handle->VALUE.protocols[c].pdsp->additional_bits_for_size_PANU = temp_size_BNEP;

							if (handle->VALUE.protocols[c].pdsp->additional_bits_flag_PANU)
							{
								if (handle->VALUE.protocols[c].pdsp->additional_bits_for_size_PANU == 1)
								{
									handle->VALUE.protocols[c].pdsp->num_of_Supported_Network_Packet_Type_List_PANU = *(handle->VALUE.protocols[c].value + cc + 1) / 3;
									handle->VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List = new SHORT[handle->VALUE.protocols[c].pdsp->num_of_Supported_Network_Packet_Type_List_PANU]();

									int pos = 0;
									for (int aaa = 0; aaa < handle->VALUE.protocols[c].pdsp->num_of_Supported_Network_Packet_Type_List_PANU; aaa++)
									{
										pos = (3 * aaa);
										handle->VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa] |= *(handle->VALUE.protocols[c].value + cc + 2 + (pos + 1));
										handle->VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa] <<= 8;
										handle->VALUE.protocols[c].pdsp->Supported_Network_Packet_Type_List[aaa] |= *(handle->VALUE.protocols[c].value + cc + 2 + (pos + 2));
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
			handle->VALUE.protocols[c].additional_parameters_flag = 0;
		}

	}
}

void SDP::FUNCTIONS::parse_SERVICE_NAME(PSERVICE_NAME handle)
{
	handle->VALUE.service_name = new char[handle->VALUE.size_bytes]();
	memcpy(handle->VALUE.service_name, handle->VALUE.value, handle->VALUE.size_bytes);
}

void SDP::FUNCTIONS::parse_PROVIDER_NAME(PPROVIDER_NAME handle)
{
	handle->VALUE.provider_name = new char[handle->VALUE.size_bytes]();
	memcpy(handle->VALUE.provider_name, handle->VALUE.value, handle->VALUE.size_bytes);

}

void SDP::FUNCTIONS::parse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST(PBLUETOOTH_PROFILE_DESCRIPTOR_LIST handle)
{
	// trenutno narejeno samo za en profile
	handle->VALUE.profile_UUID |= handle->VALUE.value[3];
	handle->VALUE.profile_UUID <<= 8;
	handle->VALUE.profile_UUID |= handle->VALUE.value[4];
	handle->VALUE.profile_version |= handle->VALUE.value[6];
	handle->VALUE.profile_version <<= 8;
	handle->VALUE.profile_version |= handle->VALUE.value[7];

	// TODO: popravi za primer ko jih je vec naenkrat
}

void SDP::FUNCTIONS::parse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST(PLANGUAGE_BASE_ATTRIBUTE_ID_LIST handle)
{
	// TODO: naredi ce je teh tripletov vec kot eden (trenutno je narejeno samo za enega)

		/*
			TRIPLET:
			example:
			0x09 0x65 0x6E 0x09 0x00 0x6A 0x09 0x01 0x00

			0x09 0x65 0x6E <-- identifier representing the natural language
			0x09 0x00 0x6A <-- identifier that specifies a character encoding used for the language
			0x09 0x01 0x00 <-- attribute ID that serves as the base attribute ID
		*/

	handle->VALUE.triplet_id_natural_lang |= handle->VALUE.value[1];
	handle->VALUE.triplet_id_natural_lang <<= 8;
	handle->VALUE.triplet_id_natural_lang |= handle->VALUE.value[2];

	handle->VALUE.triplet_id_char_encoding |= handle->VALUE.value[4];
	handle->VALUE.triplet_id_char_encoding <<= 8;
	handle->VALUE.triplet_id_char_encoding |= handle->VALUE.value[5];

	handle->VALUE.triplet_attribute_id |= handle->VALUE.value[7];
	handle->VALUE.triplet_attribute_id <<= 8;
	handle->VALUE.triplet_attribute_id |= handle->VALUE.value[8];
}

void SDP::FUNCTIONS::parse_SERVICE_DESCRIPTION(PSERVICE_DESCRIPTION handle)
{
	handle->VALUE.description = new char[handle->VALUE.size_bytes]();
	memcpy(handle->VALUE.description, handle->VALUE.value, handle->VALUE.size_bytes);

}



int SDP::FUNCTIONS::getAndParse_SERVICE_AVAILABILITY(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_AVAILABILITY ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::ServiceAvailability, SDP::ServiceAvailability, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		printResponse(bssr_response);


		// TODO: najdi en primer, da se lahko naredi do konca parsanje


		return 1;
	}



	return 0;
}

