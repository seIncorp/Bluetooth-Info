#pragma once

namespace SDP
{

	namespace OBEX
	{
		typedef enum
		{
			GoepL2capPsm = 0x0200,
			ServiceVersion = 0x0300,
			SupportedFormatsList = 0x0303

		} ATTRIBUTE_ID_OBEX;

		std::string getSupportedFormatsString(BYTE data[], int size);

		typedef struct SERVICE_VERSION_S : DEFAULT_OBJECT
		{

		} SERVICE_VERSION, * PSERVICE_VERSION;

		typedef struct SUPPORTED_FORMATS_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				int num_of_formats;
				BYTE* formats;

			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Number of supported formats: %d\n", v.num_of_formats);

				printf("Supported formats: \n");
				for (int aa = 0; aa < v.num_of_formats; aa++)
					printf("0x%02X ", v.formats[aa]);
				printf("\n");

				printf("Formats: \n%s\n", getSupportedFormatsString(v.formats, v.num_of_formats).c_str());
			}

		} SUPPORTED_FORMATS, * PSUPPORTED_FORMATS;

		// GoepL2CapPsm use from MAP

		int getAndParse_SERVICE_VERSION_OBEX(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SUPPORTED_FORMATS_LIST_OBEX(ULONG recordHandle, HANDLE_SDP_TYPE aa);

	};

};