#include "main.h"




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

int SDP::NAP::getAndParse_SECURITY_DESCRIPTION_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa, PSECURITY_DESCRIPTION security_description_handle, int print)
{
	printf("\n\n*** getAndParse_SECURITY_DESCRIPTION_PAN ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::NAP::SecurityDescription, SDP::NAP::SecurityDescription, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);


		//SDP::NAP::SECURITY_DESCRIPTION* security_description_handle = new SDP::NAP::SECURITY_DESCRIPTION();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::NAP::SECURITY_DESCRIPTION*, BYTE[]>(security_description_handle, bssr_response, 5000);



		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::NAP::SECURITY_DESCRIPTION*, BYTE[]>(security_description_handle, bssr_response, 5000, position);


		security_description_handle->VALUE.security_value |= security_description_handle->VALUE.value[0];
		security_description_handle->VALUE.security_value <<= 8;
		security_description_handle->VALUE.security_value |= security_description_handle->VALUE.value[1];

		if (print == 1)
			security_description_handle->print<SECURITY_DESCRIPTION::VV>(security_description_handle->VALUE);

		return 1;
	}




	return 0;
}

int SDP::NAP::getAndParse_NET_ACCESS_TYPE_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa, PNET_ACCESS_TYPE net_access_type_handle, int print)
{
	printf("\n\n*** getAndParse_NET_ACCESS_TYPE_PAN ***\n");

	BYTE bssr_response[5000]{ 0 };		// TODO: premisli

	BOOL test = SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::NAP::NetAccessType, SDP::NAP::NetAccessType, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);


		//SDP::NAP::NET_ACCESS_TYPE* net_access_type_handle = new SDP::NAP::NET_ACCESS_TYPE();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::NAP::NET_ACCESS_TYPE*, BYTE[]>(net_access_type_handle, bssr_response, 5000);



		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::NAP::NET_ACCESS_TYPE*, BYTE[]>(net_access_type_handle, bssr_response, 5000, position);


		net_access_type_handle->VALUE.NetAccessType |= net_access_type_handle->VALUE.value[0];
		net_access_type_handle->VALUE.NetAccessType <<= 8;
		net_access_type_handle->VALUE.NetAccessType |= net_access_type_handle->VALUE.value[1];

		if (print == 1)
			net_access_type_handle->print<NET_ACCESS_TYPE::VV>(net_access_type_handle->VALUE);



		return 1;
	}

	return 0;
}

int SDP::NAP::getAndParse_MAX_NET_ACCESS_RATE_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa, PMAX_NET_ACCESS_RATE max_net_access_rate_handle, int print)
{
	printf("\n\n*** getAndParse_MAX_NET_ACCESS_RATE_PAN ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::NAP::MaxNetAccessrate, SDP::NAP::MaxNetAccessrate, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		//SDP::NAP::MAX_NET_ACCESS_RATE* max_net_access_rate_handle = new SDP::NAP::MAX_NET_ACCESS_RATE();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::NAP::MAX_NET_ACCESS_RATE*, BYTE[]>(max_net_access_rate_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::NAP::MAX_NET_ACCESS_RATE*, BYTE[]>(max_net_access_rate_handle, bssr_response, 5000, position);

		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate |= max_net_access_rate_handle->VALUE.value[0];
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate <<= 8;
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate |= max_net_access_rate_handle->VALUE.value[1];
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate <<= 8;
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate |= max_net_access_rate_handle->VALUE.value[2];
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate <<= 8;
		max_net_access_rate_handle->VALUE.Maximum_possible_Network_Access_Data_Rate |= max_net_access_rate_handle->VALUE.value[3];


		if (print == 1)
			max_net_access_rate_handle->print<MAX_NET_ACCESS_RATE::VV>(max_net_access_rate_handle->VALUE);

		return 1;
	}

	return 0;
}


/*********************************************************************************************************************/
/* CLASS NAP_PANU_all_attributes functions */



SDP::NAP::NAP_PANU_all_attributes::NAP_PANU_all_attributes(int nap)
{
	// set all objects

	if (nap == 1)
	{
		nap_flag = 1;

		PDEFAULT_OBJECT record_handle = new DEFAULT_OBJECT();
		PSERVICE_CLASS_ID_LIST class_id_handle = new SERVICE_CLASS_ID_LIST();
		PPROTOCOL_DESCRIPTOR_LIST protocol_descriptor_list_handle = new PROTOCOL_DESCRIPTOR_LIST();
		PLANGUAGE_BASE_ATTRIBUTE_ID_LIST language_base_attribute_id_list_handle = new LANGUAGE_BASE_ATTRIBUTE_ID_LIST();
		PBLUETOOTH_PROFILE_DESCRIPTOR_LIST bluetooth_profile_descriptor_list_handle = new BLUETOOTH_PROFILE_DESCRIPTOR_LIST();
		PSERVICE_NAME service_name_handle = new SERVICE_NAME();
		PSERVICE_DESCRIPTION service_description_handle = new SERVICE_DESCRIPTION();


		/* specific */
		PSECURITY_DESCRIPTION security_description_handle = new SECURITY_DESCRIPTION();
		PNET_ACCESS_TYPE net_access_type_handle = new NET_ACCESS_TYPE();
		PMAX_NET_ACCESS_RATE max_net_access_rate_handle = new MAX_NET_ACCESS_RATE();
	}
	else
	{
		nap_flag = 0;

		PDEFAULT_OBJECT record_handle = new DEFAULT_OBJECT();
		PSERVICE_CLASS_ID_LIST class_id_handle = new SERVICE_CLASS_ID_LIST();
		PPROTOCOL_DESCRIPTOR_LIST protocol_descriptor_list_handle = new PROTOCOL_DESCRIPTOR_LIST();
		PLANGUAGE_BASE_ATTRIBUTE_ID_LIST language_base_attribute_id_list_handle = new LANGUAGE_BASE_ATTRIBUTE_ID_LIST();
		PBLUETOOTH_PROFILE_DESCRIPTOR_LIST bluetooth_profile_descriptor_list_handle = new BLUETOOTH_PROFILE_DESCRIPTOR_LIST();
		PSERVICE_NAME service_name_handle = new SERVICE_NAME();
		PSERVICE_DESCRIPTION service_description_handle = new SERVICE_DESCRIPTION();


		/* specific */
		PSECURITY_DESCRIPTION security_description_handle = new SECURITY_DESCRIPTION();
	}



}

void SDP::NAP::NAP_PANU_all_attributes::call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp)
{
	if (nap_flag == 1)
	{
		SDP::FUNCTIONS::getAndParse_SERVICE_RECORD_HANDLE(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, record_handle, 0);
		SDP::FUNCTIONS::getAndParse_SERVICE_CLASS_ID_LIST(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, class_id_handle, 0);
		SDP::FUNCTIONS::getAndParse_PROTOCOL_DESCRIPTOR_LIST(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, protocol_descriptor_list_handle, 0);
		SDP::FUNCTIONS::getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, language_base_attribute_id_list_handle, 0);
		SDP::FUNCTIONS::getAndParse_SERVICE_AVAILABILITY(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME);
		SDP::FUNCTIONS::getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, bluetooth_profile_descriptor_list_handle, 0);
		SDP::FUNCTIONS::getAndParse_SERVICE_NAME(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, service_name_handle, 0);
		SDP::FUNCTIONS::getAndParse_SERVICE_DESCRIPTION(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, service_description_handle, 0);
		
		SDP::NAP::getAndParse_SECURITY_DESCRIPTION_PAN(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, security_description_handle, 0);
		SDP::NAP::getAndParse_NET_ACCESS_TYPE_PAN(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, net_access_type_handle, 0);
		SDP::NAP::getAndParse_MAX_NET_ACCESS_RATE_PAN(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, max_net_access_rate_handle, 0);
	}
	else
	{
		SDP::FUNCTIONS::getAndParse_SERVICE_RECORD_HANDLE(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, record_handle, 0);
		SDP::FUNCTIONS::getAndParse_SERVICE_CLASS_ID_LIST(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, class_id_handle, 0);
		SDP::FUNCTIONS::getAndParse_PROTOCOL_DESCRIPTOR_LIST(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, protocol_descriptor_list_handle, 0);
		SDP::FUNCTIONS::getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, language_base_attribute_id_list_handle, 0);
		SDP::FUNCTIONS::getAndParse_SERVICE_AVAILABILITY(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME);
		SDP::FUNCTIONS::getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, bluetooth_profile_descriptor_list_handle, 0);
		SDP::FUNCTIONS::getAndParse_SERVICE_NAME(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, service_name_handle, 0);
		SDP::FUNCTIONS::getAndParse_SERVICE_DESCRIPTION(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, service_description_handle, 0);

		SDP::NAP::getAndParse_SECURITY_DESCRIPTION_PAN(device_data_sdp->buffer_res[0], device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME, security_description_handle, 0);
	}
}

void SDP::NAP::NAP_PANU_all_attributes::print_ALL_ATTR()
{
	if (nap_flag == 1)
	{
		record_handle->print(record_handle->VALUE);
		class_id_handle->print<SERVICE_CLASS_ID_LIST_S::VV>(class_id_handle->VALUE);
		protocol_descriptor_list_handle->print<PROTOCOL_DESCRIPTOR_LIST_S::VV>(protocol_descriptor_list_handle->VALUE);
		language_base_attribute_id_list_handle->print<LANGUAGE_BASE_ATTRIBUTE_ID_LIST_S::VV>(language_base_attribute_id_list_handle->VALUE);
		bluetooth_profile_descriptor_list_handle->print<BLUETOOTH_PROFILE_DESCRIPTOR_LIST_S::VV>(bluetooth_profile_descriptor_list_handle->VALUE);
		service_name_handle->print<SERVICE_NAME_S::VV>(service_name_handle->VALUE);
		service_description_handle->print<SERVICE_DESCRIPTION_S::VV>(service_description_handle->VALUE);

		security_description_handle->print<SECURITY_DESCRIPTION_S::VV>(security_description_handle->VALUE);
		net_access_type_handle->print<NET_ACCESS_TYPE_S::VV>(net_access_type_handle->VALUE);
		max_net_access_rate_handle->print<MAX_NET_ACCESS_RATE_S::VV>(max_net_access_rate_handle->VALUE);
	}
	else
	{
		record_handle->print(record_handle->VALUE);
		class_id_handle->print<SERVICE_CLASS_ID_LIST_S::VV>(class_id_handle->VALUE);
		protocol_descriptor_list_handle->print<PROTOCOL_DESCRIPTOR_LIST_S::VV>(protocol_descriptor_list_handle->VALUE);
		language_base_attribute_id_list_handle->print<LANGUAGE_BASE_ATTRIBUTE_ID_LIST_S::VV>(language_base_attribute_id_list_handle->VALUE);
		bluetooth_profile_descriptor_list_handle->print<BLUETOOTH_PROFILE_DESCRIPTOR_LIST_S::VV>(bluetooth_profile_descriptor_list_handle->VALUE);
		service_name_handle->print<SERVICE_NAME_S::VV>(service_name_handle->VALUE);
		service_description_handle->print<SERVICE_DESCRIPTION_S::VV>(service_description_handle->VALUE);

		security_description_handle->print<SECURITY_DESCRIPTION_S::VV>(security_description_handle->VALUE);
	}
	
}










