#include "main.h"




/*********************************************************************************************************************/
/* AVRCP SPECIFIC */

void SDP::AVRCP::parse_SUPPORTED_FEATURES_AVRCP(PSUPPORTED_FEATURES handle, SHORT current_used_service)
{
	SHORT temp = 0x00;

	temp |= handle->VALUE.value[0];
	temp <<= 8;
	temp |= handle->VALUE.value[1];


	handle->VALUE.supported_features_value = temp;

	// TODO: preveri ce se pravilno shrani oz. na pravo mesto
	 
	if (current_used_service == SDP::A_V_RemoteControl ||
		current_used_service == SDP::A_V_RemoteControlController
		)
	{
		handle->VALUE.sfds = new SUPPORTED_FEATURES_DATA_S(&temp, 0);
	}

	if (current_used_service == SDP::A_V_RemoteControlTarget)
		handle->VALUE.sfds = new SUPPORTED_FEATURES_DATA_S(&temp,1);
}


/*********************************************************************************************************************/
/* CLASS AVRCP_all_attributes functions */


SDP::AVRCP::AVRCP_all_attributes::AVRCP_all_attributes()
{
	setDefaultObjects();

	provider_name_handle = new PROVIDER_NAME();
	supported_features_handle = new SUPPORTED_FEATURES();
}

void SDP::AVRCP::AVRCP_all_attributes::call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp)
{
	callDefaultAttributes(device_data_sdp);

	FUNCTIONS::getAndParse_DEAFULT<PPROVIDER_NAME, PROVIDER_NAME::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		provider_name_handle,
		SDP::ProviderName,
		SDP::ProviderName,
		device_data_sdp,
		1
	);

	FUNCTIONS::getAndParse_DEAFULT<PSUPPORTED_FEATURES, SUPPORTED_FEATURES::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		supported_features_handle,
		SupportedFeatures,
		SupportedFeatures,
		device_data_sdp,
		0
	);

	dds = device_data_sdp;
}

void SDP::AVRCP::AVRCP_all_attributes::print_ALL_ATTR()
{
	printDefaultData();

	supported_features_handle->print<SUPPORTED_FEATURES::VV>(supported_features_handle->VALUE);
}



