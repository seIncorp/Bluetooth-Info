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



void SDP::MAP::parse_GOEPL2CAPPSM_MAP(PGOEPL2CAPPSM handle)
{
	SHORT temp = 0x00;
	temp |= handle->VALUE.value[0];
	temp <<= 8;
	temp |= handle->VALUE.value[1];

	handle->VALUE.GoepL2CapPsm_value = temp;
}

void SDP::MAP::parse_SUPPORTED_MESSAGE_TYPES_MAP(PSUPPORTED_MESSAGE_TYPES handle)
{
	handle->VALUE.sfm = new SUPPORTED_FEATURES_MESSAGES_S(handle->VALUE.value);
}

void SDP::MAP::parse_MAS_INSTANCE_ID_MAP(PMAS_INSTANCE_ID handle)
{
	handle->VALUE.instance_ID = handle->VALUE.value[0];
}

void SDP::MAP::parse_MAP_SUPPORTED_FEATURES_MAP(PMAP_SUPPORTED_FEATURES handle)
{
	DWORD temp = 0x00;

	temp |= handle->VALUE.value[0];
	temp <<= 8;
	temp |= handle->VALUE.value[1];
	temp <<= 8;
	temp |= handle->VALUE.value[2];
	temp <<= 8;
	temp |= handle->VALUE.value[3];

	handle->VALUE.sfm = new SUPPORTED_FEATURES_MESSAGES_S(&temp);
}


/*********************************************************************************************************************/
/* CLASS MAP_all_attributes functions */


SDP::MAP::MAP_all_attributes::MAP_all_attributes()
{
	// set all objects
	setDefaultObjects();

	goepl2cappsm_handle = new GOEPL2CAPPSM();
	supported_message_types_handle = new SUPPORTED_MESSAGE_TYPES();
	mas_instance_id_handle = new MAS_INSTANCE_ID();
	map_supported_features_handle = new MAP_SUPPORTED_FEATURES();
}

void SDP::MAP::MAP_all_attributes::call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp)
{
	callDefaultAttributes(device_data_sdp);

	FUNCTIONS::getAndParse_DEAFULT<PGOEPL2CAPPSM, GOEPL2CAPPSM::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		goepl2cappsm_handle,
		SDP::MAP::GoepL2capPsm,
		SDP::MAP::GoepL2capPsm,
		device_data_sdp,
		0
	);
	
	FUNCTIONS::getAndParse_DEAFULT<PSUPPORTED_MESSAGE_TYPES, SUPPORTED_MESSAGE_TYPES::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		supported_message_types_handle,
		SDP::MAP::SupportedMessageTypes,
		SDP::MAP::SupportedMessageTypes,
		device_data_sdp,
		0
	);

	FUNCTIONS::getAndParse_DEAFULT<PMAS_INSTANCE_ID, MAS_INSTANCE_ID::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		mas_instance_id_handle,
		SDP::MAP::MASInstanceID,
		SDP::MAP::MASInstanceID,
		device_data_sdp,
		0
	);

	FUNCTIONS::getAndParse_DEAFULT<PMAP_SUPPORTED_FEATURES, MAP_SUPPORTED_FEATURES::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		map_supported_features_handle,
		SDP::MAP::MapSupportedFeatures,
		SDP::MAP::MapSupportedFeatures,
		device_data_sdp,
		0
	);
}

void SDP::MAP::MAP_all_attributes::print_ALL_ATTR()
{
	printDefaultData();


	goepl2cappsm_handle->print<GOEPL2CAPPSM_S::VV>(goepl2cappsm_handle->VALUE);
	supported_message_types_handle->print<SUPPORTED_MESSAGE_TYPES_S::VV>(supported_message_types_handle->VALUE);
	mas_instance_id_handle->print<MAS_INSTANCE_ID_S::VV>(mas_instance_id_handle->VALUE);
	map_supported_features_handle->print<MAP_SUPPORTED_FEATURES_S::VV>(map_supported_features_handle->VALUE);
}


