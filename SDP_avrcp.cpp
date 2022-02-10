#include "main.h"




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

