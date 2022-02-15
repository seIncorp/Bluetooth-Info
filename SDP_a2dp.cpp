#include "main.h"



/*********************************************************************************************************************/
/* A2DP SPECIFIC */

void SDP::A2DP::parse_SUPPORTED_FEATURES_A2DP(PSUPPORTED_FEATURES handle)
{
	SHORT temp = 0x00;
	temp |= handle->VALUE.value[0];
	temp <<= 8;
	temp |= handle->VALUE.value[1];

	handle->VALUE.supported_features_value = temp;

	handle->VALUE.sfds = new SUPPORTED_FEATURES_DATA_S(&handle->VALUE.supported_features_value);

}


/*********************************************************************************************************************/
/* CLASS A2DP_all_attributes functions */


SDP::A2DP::A2DP_all_attributes::A2DP_all_attributes()
{
	setDefaultObjects();

	provider_name_handle = new PROVIDER_NAME();
	supported_features_handle = new SUPPORTED_FEATURES();
}

void SDP::A2DP::A2DP_all_attributes::call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp)
{
	callDefaultAttributes(device_data_sdp);

	FUNCTIONS::getAndParse_DEAFULT<PPROVIDER_NAME, PROVIDER_NAME::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		provider_name_handle,
		SDP::ProviderName,
		SDP::ProviderName,
		device_data_sdp,
		0
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
}

void SDP::A2DP::A2DP_all_attributes::print_ALL_ATTR()
{
	printDefaultData();

	supported_features_handle->print<SUPPORTED_FEATURES_S::VV>(supported_features_handle->VALUE);
}




