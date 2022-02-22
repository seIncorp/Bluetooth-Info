#include "main.h"



// TODO: razmisli kaj s tem!!
// information about the specified connected remote radio
int getDeviceInfo()
{
	BTH_RADIO_INFO *bri{ 0 };

	dd.bResult = FALSE;
	dd.junk = 0;

	// CC:98:8B:A6:FF:7C
	BYTE test[sizeof(BTH_RADIO_INFO)]{ 0 };
	/*test[5] = 0xB6;
	test[4] = 0x5A;
	test[3] = 0xE7;
	test[2] = 0x6E;
	test[1] = 0xB8;
	test[0] = 0xA8;*/
	test[5] = 0xcc;
	test[4] = 0x98;
	test[3] = 0x8b;
	test[2] = 0xa6;
	test[1] = 0xff;
	test[0] = 0x7c;


	dd.bResult = DeviceIoControl(
		dd.hDevice, // device to be queried
		IOCTL_BTH_GET_RADIO_INFO, // operation to perform

		//NULL, 0,                       // no input buffer
		test, sizeof(test),                      // no input buffer
		//&bri, sizeof(bri),             // output buffer
		test, sizeof(test),             // output buffer

		&dd.junk,                         // # bytes returned
		(LPOVERLAPPED)NULL);          // synchronous I/O

	IOCTL_S::printErrorMessage(GetLastError());

	//printf("%d\n", dd.junk);

	if (dd.bResult)
	{
		bri = (BTH_RADIO_INFO*)test;

		BTH_DEVICES::PCONNECTED_DEVICE_DATA	connected_device = new BTH_DEVICES::CONNECTED_DEVICE_DATA();

		BTH_DEVICES::RADIO_DATA_S radio_data_temp{ bri->lmpSupportedFeatures, bri->mfg, bri->lmpSubversion, bri->lmpVersion };
		connected_device->radio = &radio_data_temp;

		connected_device->print();

		/*printf("lmpSubversion: %d  -- %X\n",bri->lmpSubversion,bri->lmpSubversion);
		printf("lmpVersion: %d  -- %X\n",bri->lmpVersion,bri->lmpVersion);
		printf("mfg: %d  -- %X\n",bri->mfg,bri->mfg);
		printf("lmpSupportedFeatures: %llu  -- %X\n",bri->lmpSupportedFeatures,bri->lmpSupportedFeatures);*/


		return 1;
	}

	return 0;
}














void IOCTL_S::printErrorMessage(DWORD id)
{
	if (id != 0x00)
		switch (id)
		{
			case 0x3A:
				printf("ERROR [0x%X - %d] [ERROR_BAD_NET_RESP]\n", id, id);
			break;

			case 0x57:
				printf("ERROR [0x%X - %d] [ERROR_INVALID_PARAMETER]\n", id, id);
			break;

			case 0x79:
				printf("ERROR [0x%X - %d] [ERROR_SEM_TIMEOUT]\n", id, id);
			break;

			case 0x7A:
				printf("ERROR [0x%X - %d] [ERROR_INSUFFICIENT_BUFFER]\n", id, id);
			break;

			case 0x32:
				printf("ERROR [0x%X - %d] [ERROR_NOT_SUPPORTED]\n", id, id);
			break;

			case 0x522:
				printf("ERROR [0x%X - %d] [ERROR_PRIVILEGE_NOT_HELD]\n", id, id);
			break;

			case 0x48F:
				printf("ERROR [0x%X - %d] [ERROR_DEVICE_NOT_CONNECTED]\n", id, id);
			break;

			case 0x6F8:
				printf("ERROR [0x%X - %d] [ERROR_INVALID_USER_BUFFER]\n", id, id);
			break;

			default:
				printf("ERROR [0x%X - %d] [????]\n", id, id);
			break;
		}
}

int IOCTL_S::connectToDevice(const wchar_t* name)
{
	dd.hDevice = CreateFileW(
		DEFAULT_DEVICE,							// drive to open
		//GENERIC_READ | GENERIC_WRITE,			// no access to the drive
		FILE_READ_DATA | FILE_WRITE_DATA,			// no access to the drive
		FILE_SHARE_READ | FILE_SHARE_WRITE,		// share mode
		NULL,									// default security attributes
		OPEN_EXISTING,							// disposition
		0,										// file attributes
		NULL);									// do not copy file attributes

	if (dd.hDevice == INVALID_HANDLE_VALUE)
	{
		printErrorMessage(GetLastError());

		return 0;
	}

	return 1;
}

void IOCTL_S::closeConnectionToDevice()
{
	if (CloseHandle(dd.hDevice) == 0)
		printErrorMessage(GetLastError());
}         

int IOCTL_S::str2ba(const char* straddr, BTH_ADDR* btaddr)
{
	int i;
	unsigned int aaddr[6];
	BTH_ADDR tmpaddr = 0;

	if (sscanf_s(straddr, "%02x:%02x:%02x:%02x:%02x:%02x",
		&aaddr[0], &aaddr[1], &aaddr[2],
		&aaddr[3], &aaddr[4], &aaddr[5]) != 6)
		return 1;
	*btaddr = 0;
	for (i = 0; i < 6; i++) {
		tmpaddr = (BTH_ADDR)(aaddr[i] & 0xff);
		*btaddr = ((*btaddr) << 8) + tmpaddr;
	}
	return 0;
}

int IOCTL_S::SDPsearch()	// TODO: preimenuj v pravo ime
{
	/********************************************************************/
	/* INIT */

	SDP::DEVICE_DATA_SDP* device_data_sdp = new SDP::DEVICE_DATA_SDP();
	//char test_add[] = "A8:B8:6E:E7:5A:B6";
	char test_add[] = "00:9E:C8:AF:BD:13";

	SDP::FUNCTIONS::SDP_INIT_CONNECT::init_for_IOCTL_BTH_SDP_CONNECT(test_add, device_data_sdp);

	/********************************************************************/
	/* CONNECT TO DEVICE */

	if (SDP::FUNCTIONS::SDP_INIT_CONNECT::call_IOCTL_BTH_SDP_CONNECT(device_data_sdp))
	{
		printf("DEVICE CONNECTED!!\n");

		/******************************************/
		/* SERVICE SEARCH */

		// TODO: naredi se za ostale service (trenutno je samo za enega)

		device_data_sdp->current_used_service = SDP::AudioSource;

		SDP::FUNCTIONS::SDP_SERVICE_SEARCH::init_for_IOCTL_BTH_SDP_SERVICE_SEARCH(device_data_sdp);

		if (SDP::FUNCTIONS::SDP_SERVICE_SEARCH::call_IOCTL_BTH_SDP_SERVICE_SEARCH(device_data_sdp))
		{
			printf("SERVICE FOUNDED!! [0x%04X]\n", device_data_sdp->current_used_service);

			/******************************************/
			/* ATTRIBUTES SEARCH (for current service) */
			
			if (device_data_sdp->current_used_service == SDP::Message_Access_Server)
			{
				// DONE!
				SDP::MAP::MAP_all_attributes test_aa = SDP::MAP::MAP_all_attributes();
				test_aa.call_ALL_ATTR(device_data_sdp);
				test_aa.print_ALL_ATTR();
			}

			if (device_data_sdp->current_used_service == SDP::_NAP)
			{
				// DONE!
				SDP::NAP::NAP_PANU_all_attributes test_vv = SDP::NAP::NAP_PANU_all_attributes(1);
				test_vv.call_ALL_ATTR(device_data_sdp);
				test_vv.print_ALL_ATTR();
			}

			if (device_data_sdp->current_used_service == SDP::Phonebook_Access_PSE)
			{
				// DONE!
				SDP::PBAP::PBAP_all_attributes test_bb = SDP::PBAP::PBAP_all_attributes();
				test_bb.call_ALL_ATTR(device_data_sdp);
				test_bb.print_ALL_ATTR();
			}

			if (device_data_sdp->current_used_service == SDP::OBEXObjectPush)
			{
				// DONE!
				SDP::OBEX::OBEX_all_attributes test_bb = SDP::OBEX::OBEX_all_attributes();
				test_bb.call_ALL_ATTR(device_data_sdp);
				test_bb.print_ALL_ATTR();
			}

			if (device_data_sdp->current_used_service == SDP::Handsfree)
			{
				// DONE!
				SDP::HFP::HFP_class test_bb = SDP::HFP::HFP_class();
				test_bb.call_ALL_ATTR(device_data_sdp);
				test_bb.print_ALL_ATTR();
			}
			
			if (device_data_sdp->current_used_service == SDP::PnPInformation)
			{
				// DONE!
				if (SDP::PNPINFO::getAndParse_SPECIFICATION_ID_PNPINFO(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME) == 0)
					printf("ERROR [getAndParse_SPECIFICATION_ID_PNPINFO]\n");
			}

			if (device_data_sdp->current_used_service == SDP::AudioSource)
			{
				// DONE!
				SDP::A2DP::A2DP_all_attributes test_bb = SDP::A2DP::A2DP_all_attributes();
				test_bb.call_ALL_ATTR(device_data_sdp);
				test_bb.print_ALL_ATTR();
			}

			if (device_data_sdp->current_used_service == SDP::A_V_RemoteControl			|| 
				device_data_sdp->current_used_service == SDP::A_V_RemoteControlTarget	|| 
				device_data_sdp->current_used_service == SDP::A_V_RemoteControlController
			)
			{
				// DONE!
				SDP::AVRCP::AVRCP_all_attributes test_bb = SDP::AVRCP::AVRCP_all_attributes();
				test_bb.call_ALL_ATTR(device_data_sdp);
				test_bb.print_ALL_ATTR();
			}

			if (device_data_sdp->current_used_service == SDP::Headset || 
				device_data_sdp->current_used_service == SDP::Headset_Audio_Gateway ||
				device_data_sdp->current_used_service == 0x1131
			)
			{
				// DONE!
				SDP::HSP::HSP_all_attributes test_bb = SDP::HSP::HSP_all_attributes();
				test_bb.call_ALL_ATTR(device_data_sdp);
				test_bb.print_ALL_ATTR();
			}


			if (device_data_sdp->current_used_service == SDP::GenericAudio)
			{
				// DONE!
				SDP::DEFAULT_class test_bb = SDP::DEFAULT_class();
				test_bb.callDefaultAttributes(device_data_sdp);
				test_bb.printDefaultData();
			}



			//if (SDP::FUNCTIONS::getAndParse_SERVICE_NAME(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SERVICE_NAME]\n");

			//if (SDP::FUNCTIONS::getAndParse_PROVIDER_NAME(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_PROVIDER_NAME]\n");

			//if (SDP::FUNCTIONS::getAndParse_SERVICE_DESCRIPTION(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SERVICE_DESCRIPTION]\n");

			//if (SDP::NAP::getAndParse_SECURITY_DESCRIPTION_PAN(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SECURITY_DESCRIPTION_PAN]\n");
			
			//if (SDP::NAP::getAndParse_NET_ACCESS_TYPE_PAN(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_NET_ACCESS_TYPE_PAN]\n");

			//if (SDP::NAP::getAndParse_MAX_NET_ACCESS_RATE_PAN(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_MAX_NET_ACCESS_RATE_PAN]\n");

			//if (SDP::MAP::getAndParse_GOEPL2CAPPSM_MAP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_GOEPL2CAPPSM_MAP]\n");

			//if (SDP::MAP::getAndParse_SUPPORTED_MESSAGE_TYPES_MAP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SUPPORTED_MESSAGE_TYPES_MAP]\n");

			//if (SDP::MAP::getAndParse_MAP_SUPPORTED_FEATURES_MAP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_MAP_SUPPORTED_FEATURES_MAP]\n");

			//if (SDP::MAP::getAndParse_MAS_INSTANCE_ID_MAP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_MAS_INSTANCE_ID_MAP]\n");

			//if (SDP::PBAP::getAndParse_SUPPORTED_REPOSITORIES_PBAP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SUPPORTED_REPOSITORIES_PBAP]\n");

			//if (SDP::PBAP::getAndParse_PBAP_SUPPORTED_FEATURES_PBAP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_PBAP_SUPPORTED_FEATURES_PBAP]\n");

			//if (SDP::OBEX::getAndParse_SERVICE_VERSION_OBEX(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SERVICE_VERSION_OBEX]\n");

			//if (SDP::OBEX::getAndParse_SUPPORTED_FORMATS_LIST_OBEX(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SUPPORTED_FORMATS_LIST_OBEX]\n");

			//if (SDP::HFP::getAndParse_SUPPORTED_FEATURES_HFP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SUPPORTED_FEATURES_HFP]\n");

			//if (SDP::HFP::getAndParse_NETWORK_HFP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_NETWORK_HFP]\n");

			//if (SDP::PNPINFO::getAndParse_SPECIFICATION_ID_PNPINFO(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SPECIFICATION_ID_PNPINFO]\n");

			//if (SDP::A2DP::getAndParse_SUPPORTED_FEATURES_A2DP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SUPPORTED_FEATURES_A2DP]\n");

			//if (SDP::AVRCP::getAndParse_SUPPORTED_FEATURES_AVRCP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_SUPPORTED_FEATURES_AVRCP]\n");

			//if (SDP::HSP::getAndParse_REMOTE_AUDIO_VOLUME_CONTROL_HSP(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
				//printf("ERROR [getAndParse_REMOTE_AUDIO_VOLUME_CONTROL_HSP]\n");


			// 14 - currently max attributes in ATTRIBUTE_ID enum
			for (int a = 0; a < 14; a++)
			{
				switch (a)
				{
					/*case SDP::ServiceRecordHandle:
						if (SDP::FUNCTIONS::getAndParse_SERVICE_RECORD_HANDLE(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME) == 0)
							printf("ERROR [getAndParse_SERVICE_RECORD_HANDLE]\n");
					break;*/
					
					/*case SDP::ServiceClassIDList:
						if (SDP::FUNCTIONS::getAndParse_SERVICE_CLASS_ID_LIST(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
							printf("ERROR [getAndParse_SERVICE_CLASS_ID_LIST]\n");
					break;*/
					
					/*case SDP::ProtocolDescriptorList:
						if (SDP::FUNCTIONS::getAndParse_PROTOCOL_DESCRIPTOR_LIST(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
							printf("ERROR [getAndParse_PROTOCOL_DESCRIPTOR_LIST]\n");
					break;*/

					

					/*case SDP::BluetoothProfileDescriptorList:
						if (SDP::FUNCTIONS::getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
							printf("ERROR [getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST]\n");
					break;*/

					/*case SDP::LanguageBaseAttributeIDList:
						if (SDP::FUNCTIONS::getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
							printf("ERROR [getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST]\n");
					break;*/

					/*case SDP::ServiceAvailability:
						if (SDP::FUNCTIONS::getAndParse_SERVICE_AVAILABILITY(buffer_res[0], bsc->HANDLE_SDP_FIELD_NAME) == 0)
							printf("ERROR [getAndParse_SERVICE_AVAILABILITY]\n");
					break;*/

				}
			}
		}

		/******************************************/
		/* DISCONNECTION FROM DEVICE (IMPORTANT!!!) */

		SDP::FUNCTIONS::SDP_INIT_DISCONNECT::init_for_IOCTL_BTH_SDP_DISCONNECT(device_data_sdp);

		return SDP::FUNCTIONS::SDP_INIT_DISCONNECT::call_IOCTL_BTH_SDP_DISCONNECT(device_data_sdp);
	}

	return 0;
}

// LIST OF CACHED BTH SEARCHED DEVICES
int IOCTL_S::getBthDeviceInfo(int print)
{
	BYTE data[sizeof(BTH_DEVICE_INFO_LIST) + (MAX_SEARCHED_SHOWED_DEVICE - 1) * sizeof(BTH_DEVICE_INFO)]{ 0 };

	dd.bResult = DeviceIoControl(
		dd.hDevice,						// device to be queried
		IOCTL_BTH_GET_DEVICE_INFO,		// operation to perform
		NULL, 0,						// no input buffer
		data, sizeof(data),             // output buffer
		&dd.junk,                       // # bytes returned
		(LPOVERLAPPED)NULL);			// synchronous I/O

	printErrorMessage(GetLastError());

	if (dd.bResult)
	{
		BTH_DEVICE_INFO_LIST* bdil = (BTH_DEVICE_INFO_LIST*)data;
		BTH_DEVICE_INFO* bdi = bdil->deviceList;

		BTH_DEVICES::PSEARCHED_CACHED_DEVICES devices = new BTH_DEVICES::SEARCHED_CACHED_DEVICES();
		devices->numOfDevices = bdil->numOfDevices;

		for (int a = 0; a < bdil->numOfDevices; a++)
		{
			BLUETOOTH_ADDRESS_STRUCT* bas = (BLUETOOTH_ADDRESS_STRUCT*)&((bdi + a)->address);

			BTH_DEVICES::CACHED_DEVICE_S temp{ (bdi + a)->name, bas->rgBytes, (bdi + a)->flags };

			devices->devices.push_back(temp);
		}

		if(print == 1)
			devices->print();

		return 1;
	}
	else
		return 0;
}

// information about the local Bluetooth system and radio
void IOCTL_S::getLocalBthInfo()
{
	BTH_LOCAL_RADIO_INFO blri{ 0 };

	dd.bResult = DeviceIoControl(
		dd.hDevice,					// device to be queried
		IOCTL_BTH_GET_LOCAL_INFO,	// operation to perform
		NULL, 0,                    // no input buffer
		&blri, sizeof(blri),        // output buffer
		&dd.junk,                   // # bytes returned
		(LPOVERLAPPED)NULL);        // synchronous I/O

	printErrorMessage(GetLastError());

	if (dd.bResult)
	{
		BTH_DEVICE_INFO bdi = blri.localInfo;
		BTH_RADIO_INFO* bri = &blri.radioInfo;

		BTH_DEVICES::PLOCAL_RADIO_DEVICE_DATA local_device_radio = new BTH_DEVICES::LOCAL_RADIO_DEVICE_DATA(
																blri.flags,
																blri.hciRevision,
																blri.hciVersion
		);

		BTH_DEVICES::DEVICE_DATA_S temp_d;

		temp_d.init(
			((BLUETOOTH_ADDRESS_STRUCT*)(&bdi.address))->rgBytes,
			bdi.flags,
			bdi.name
		);
		local_device_radio->device = &temp_d;

		COD_PARSER::PDEVICE_PARSED_COD_DATA cod_temp = new COD_PARSER::DEVICE_PARSED_COD_DATA();
		parseCODdata((COD_PARSER::COD_data*)&bdi.classOfDevice, cod_temp);
		local_device_radio->device->cod = cod_temp;

		BTH_DEVICES::RADIO_DATA_S temp_s{ bri->lmpSupportedFeatures ,bri->mfg,bri->lmpSubversion, bri->lmpVersion };
		local_device_radio->radio = &temp_s;

		// TODO: preveri tezavo s prikazom zunaj
		local_device_radio->print();
	}
}


