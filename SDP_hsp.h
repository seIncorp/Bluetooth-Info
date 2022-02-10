#pragma once


namespace SDP
{

	namespace HSP
	{
		typedef enum
		{
			RemoteAudioVolumeControl = 0x0302

		} ATTRIBUTE_ID_DEVICE_HSP;

		typedef struct REMOTE_AUDIO_VOLUME_CONTROL_S : DEFAULT_OBJECT
		{
			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				// TODO: najdi primer za parsanje
			}

		} REMOTE_AUDIO_VOLUME_CONTROL, * PREMOTE_AUDIO_VOLUME_CONTROL;


		int getAndParse_REMOTE_AUDIO_VOLUME_CONTROL_HSP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
	};



};