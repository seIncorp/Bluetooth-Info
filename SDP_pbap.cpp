#include "main.h"


/*********************************************************************************************************************/
/* PBAP SPECIFIC */

// FOR	 GoepL2CapPsm YOU CAN USE FROM MAP



void SDP::PBAP::parse_SUPPORTED_REPOSITORIES_PBAP(PSUPPORTED_REPOSITORIES handle)
{
	handle->VALUE.srs = new SUPPORTED_REPOSITORIES_DATA_S(handle->VALUE.value);
}

void SDP::PBAP::parse_PBAP_SUPPORTED_FEATURES_PBAP(PPBAP_SUPPORTED_FEATURES handle)
{
	// TODO: prevedi values kaj pomeni
	// TODO: poisci device ki ima verzijo 1.2 ali vec
}



/*********************************************************************************************************************/
/* CLASS PBAP_all_attributes functions */


SDP::PBAP::PBAP_all_attributes::PBAP_all_attributes()
{
	// set all objects
	setDefaultObjects();

	goepl2cappsm_handle = new SDP::MAP::GOEPL2CAPPSM();
	supported_repositories_handle = new SUPPORTED_REPOSITORIES();
	pbap_supported_features_handle = new PBAP_SUPPORTED_FEATURES();
}

void SDP::PBAP::PBAP_all_attributes::call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp)
{
	callDefaultAttributes(device_data_sdp);

	FUNCTIONS::getAndParse_DEAFULT<SDP::MAP::PGOEPL2CAPPSM, SDP::MAP::GOEPL2CAPPSM::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		goepl2cappsm_handle,
		SDP::MAP::GoepL2capPsm,
		SDP::MAP::GoepL2capPsm,
		device_data_sdp,
		0
	);

	FUNCTIONS::getAndParse_DEAFULT<PSUPPORTED_REPOSITORIES, SUPPORTED_REPOSITORIES::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		supported_repositories_handle,
		SupportedRepositories,
		SupportedRepositories,
		device_data_sdp,
		0
	);

	FUNCTIONS::getAndParse_DEAFULT<PPBAP_SUPPORTED_FEATURES, PBAP_SUPPORTED_FEATURES::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		pbap_supported_features_handle,
		PbapSupportedFeatures,
		PbapSupportedFeatures,
		device_data_sdp,
		0
	);
}

void SDP::PBAP::PBAP_all_attributes::print_ALL_ATTR()
{
	printDefaultData();

	goepl2cappsm_handle->print<SDP::MAP::GOEPL2CAPPSM_S::VV>(goepl2cappsm_handle->VALUE);
	supported_repositories_handle->print<SUPPORTED_REPOSITORIES::VV>(supported_repositories_handle->VALUE);
	pbap_supported_features_handle->print<PBAP_SUPPORTED_FEATURES::VV>(pbap_supported_features_handle->VALUE);
}

