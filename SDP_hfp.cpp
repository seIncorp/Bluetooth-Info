#include "main.h"


/*********************************************************************************************************************/
/* HFP SPECIFIC */


int SDP::HFP::getAndParse_NETWORK_HFP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_NETWORK_HFP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::HFP::Network, SDP::HFP::Network, bssr_response, 5000);

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

	BOOL test = SDP::FUNCTIONS::SDP_ATTRIBUTE_SEARCH::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::HFP::SupportedFeatures, SDP::HFP::SupportedFeatures, bssr_response, 5000);

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

