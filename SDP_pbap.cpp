#include "main.h"


/*********************************************************************************************************************/
/* PBAP SPECIFIC */

// FOR	 GoepL2CapPsm YOU CAN USE FROM MAP

int SDP::PBAP::getAndParse_SUPPORTED_REPOSITORIES_PBAP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SUPPORTED_REPOSITORIES_PBAP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::PBAP::SupportedRepositories, SDP::PBAP::SupportedRepositories, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::PBAP::SUPPORTED_REPOSITORIES* supported_repositories_handle = new SDP::PBAP::SUPPORTED_REPOSITORIES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::PBAP::SUPPORTED_REPOSITORIES*, BYTE[]>(supported_repositories_handle, bssr_response, 5000);

		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::PBAP::SUPPORTED_REPOSITORIES*, BYTE[]>(supported_repositories_handle, bssr_response, 5000, position);

		supported_repositories_handle->VALUE.srs = new SUPPORTED_REPOSITORIES_DATA_S(supported_repositories_handle->VALUE.value);

		supported_repositories_handle->print<SUPPORTED_REPOSITORIES::VV>(supported_repositories_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::PBAP::getAndParse_PBAP_SUPPORTED_FEATURES_PBAP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_PBAP_SUPPORTED_FEATURES_PBAP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::PBAP::PbapSupportedFeatures, SDP::PBAP::PbapSupportedFeatures, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::PBAP::PBAP_SUPPORTED_FEATURES* pbap_supported_features_handle = new SDP::PBAP::PBAP_SUPPORTED_FEATURES();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::PBAP::PBAP_SUPPORTED_FEATURES*, BYTE[]>(pbap_supported_features_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::PBAP::PBAP_SUPPORTED_FEATURES*, BYTE[]>(pbap_supported_features_handle, bssr_response, 5000, position);

		// TODO: prevedi values kaj pomeni
		// TODO: poisci device ki ima verzijo 1.2 ali vec

		pbap_supported_features_handle->print<PBAP_SUPPORTED_FEATURES::VV>(pbap_supported_features_handle->VALUE);

		return 1;
	}

	return 0;
}

