#include "main.h"



/*********************************************************************************************************************/
/* MAP SPECIFIC */

std::string SDP::MAP::getMessageTypesString(SDP::MAP::SUPPORTED_FEATURES_MESSAGES_S* sfm)
{
	std::string temp = "";

	if (sfm->ttt->a0)
	{
		temp += "EMAIL\n";
	}

	if (sfm->ttt->a1)
	{
		temp += "SMS_GSM\n";
	}

	if (sfm->ttt->a2)
	{
		temp += "SMS_CDMA\n";
	}

	if (sfm->ttt->a3)
	{
		temp += "MMS\n";
	}

	if (sfm->ttt->a4)
	{
		temp += "IM\n";
	}

	return temp;
}

std::string SDP::MAP::getSupportedFeaturesString(SDP::MAP::SUPPORTED_FEATURES_MESSAGES_S* sfm)
{
	std::string temp = "";

	if (sfm->aaa->a0)
	{
		temp += "Notification Registration Feature\n";
	}

	if (sfm->aaa->a1)
	{
		temp += "Notification Feature\n";
	}

	if (sfm->aaa->a2)
	{
		temp += "Browsing Feature\n";
	}

	if (sfm->aaa->a3)
	{
		temp += "Uploading Feature\n";
	}

	if (sfm->aaa->a4)
	{
		temp += "Delete Feature\n";
	}

	if (sfm->aaa->a5)
	{
		temp += "Instance Information Feature\n";
	}

	if (sfm->aaa->a6)
	{
		temp += "Extended Event Report 1.1\n";
	}

	if (sfm->aaa->a7)
	{
		temp += "Event Report Version 1.2\n";
	}

	if (sfm->aaa->a8)
	{
		temp += "Message Format Version 1.1\n";
	}

	if (sfm->aaa->a9)
	{
		temp += "MessagesListing Format Version 1.1\n";
	}

	if (sfm->aaa->a10)
	{
		temp += "Persistent Message Handles\n";
	}

	if (sfm->aaa->a11)
	{
		temp += "Database Identifier\n";
	}

	if (sfm->aaa->a12)
	{
		temp += "Folder Version Counter\n";
	}

	if (sfm->aaa->a13)
	{
		temp += "Conversation Version Counters\n";
	}

	if (sfm->aaa->a14)
	{
		temp += "Participant Presence Change Notification\n";
	}

	if (sfm->aaa->a15)
	{
		temp += "Participant Chat State Change Notification\n";
	}

	if (sfm->aaa->a16)
	{
		temp += "PBAP Contact Cross Reference\n";
	}

	if (sfm->aaa->a17)
	{
		temp += "Notification Filtering\n";
	}

	if (sfm->aaa->a18)
	{
		temp += "UTC Offset Timestamp Format\n";
	}

	if (sfm->aaa->a19)
	{
		temp += "MapSupportedFeatures in Connect Request\n";
	}

	if (sfm->aaa->a20)
	{
		temp += "Conversation listing\n";
	}

	if (sfm->aaa->a21)
	{
		temp += "Owner Status\n";
	}

	if (sfm->aaa->a22)
	{
		temp += "Message Forwarding\n";
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

		SHORT temp = 0x00;
		temp |= goepl2cappsm_handle->VALUE.value[0];
		temp <<= 8;
		temp |= goepl2cappsm_handle->VALUE.value[1];

		goepl2cappsm_handle->VALUE.GoepL2CapPsm_value = temp;

		goepl2cappsm_handle->print<GOEPL2CAPPSM::VV>(goepl2cappsm_handle->VALUE);


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

		supported_message_types_handle->VALUE.sfm = new SUPPORTED_FEATURES_MESSAGES_S(supported_message_types_handle->VALUE.value);

		supported_message_types_handle->print<SUPPORTED_MESSAGE_TYPES::VV>(supported_message_types_handle->VALUE);

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

		mas_instance_id_handle->VALUE.instance_ID = mas_instance_id_handle->VALUE.value[0];

		mas_instance_id_handle->print<MAS_INSTANCE_ID::VV>(mas_instance_id_handle->VALUE);



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

		DWORD temp = 0x00;

		temp |= map_supported_features_handle->VALUE.value[0];
		temp <<= 8;
		temp |= map_supported_features_handle->VALUE.value[1];
		temp <<= 8;
		temp |= map_supported_features_handle->VALUE.value[2];
		temp <<= 8;
		temp |= map_supported_features_handle->VALUE.value[3];

		map_supported_features_handle->VALUE.sfm = new SUPPORTED_FEATURES_MESSAGES_S(&temp);

		map_supported_features_handle->print<MAP_SUPPORTED_FEATURES::VV>(map_supported_features_handle->VALUE);

		return 1;
	}

	return 0;
}
