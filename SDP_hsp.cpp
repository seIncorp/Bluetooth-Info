#include "main.h"




/*********************************************************************************************************************/
/* HSP SPECIFIC */


int SDP::HSP::getAndParse_REMOTE_AUDIO_VOLUME_CONTROL_HSP(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_REMOTE_AUDIO_VOLUME_CONTROL_HSP ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::HSP::RemoteAudioVolumeControl, SDP::HSP::RemoteAudioVolumeControl, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::HSP::REMOTE_AUDIO_VOLUME_CONTROL* remote_audio_volume_control_handle = new SDP::HSP::REMOTE_AUDIO_VOLUME_CONTROL();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::HSP::REMOTE_AUDIO_VOLUME_CONTROL*, BYTE[]>(remote_audio_volume_control_handle, bssr_response, 5000);


		position = FUNCTIONS::set_save_VALUE_ELEMENT<SDP::HSP::REMOTE_AUDIO_VOLUME_CONTROL*, BYTE[]>(remote_audio_volume_control_handle, bssr_response, 5000, position);


		remote_audio_volume_control_handle->print<REMOTE_AUDIO_VOLUME_CONTROL::VV>(remote_audio_volume_control_handle->VALUE);

		return 1;
	}

	return 0;
}

