#include "main.h"


/*********************************************************************************************************************/
/* OBEX SPECIFIC */

// FOR	 GoepL2CapPsm YOU CAN USE FROM MAP

std::string SDP::OBEX::getSupportedFormatsString(BYTE data_arr[], int size)
{
	std::string temp = "";

	for (int aa = 0; aa < size; aa++)
		switch (data_arr[aa])
		{
		case 0x01:
			temp += "vCard 2.1\n";
			break;

		case 0x02:
			temp += "vCard 3.0\n";
			break;

		case 0x03:
			temp += "vCal 1.0\n";
			break;

		case 0x04:
			temp += "iCal 2.0\n";
			break;

		case 0x05:
			temp += "vNote\n";
			break;

		case 0x06:
			temp += "vMessage\n";
			break;

		case 0xff:
			temp += "any type of object\n";
			break;
		};

	return temp;
}

int SDP::OBEX::getAndParse_SERVICE_VERSION_OBEX(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SERVICE_VERSION_OBEX ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::OBEX::ServiceVersion, SDP::OBEX::ServiceVersion, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::OBEX::SERVICE_VERSION* service_version_handle = new SDP::OBEX::SERVICE_VERSION();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::OBEX::SERVICE_VERSION*, BYTE[]>(service_version_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::OBEX::SERVICE_VERSION*, BYTE[]>(service_version_handle, bssr_response, 5000, position);

		// TODO: najdi neki primer zaradi parsanja

		service_version_handle->print<SERVICE_VERSION::VV>(service_version_handle->VALUE);

		return 1;
	}

	return 0;
}

int SDP::OBEX::getAndParse_SUPPORTED_FORMATS_LIST_OBEX(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SUPPORTED_FORMATS_LIST_OBEX ***\n");

	BYTE bssr_response[5000]{ 0 };

	BOOL test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, SDP::OBEX::SupportedFormatsList, SDP::OBEX::SupportedFormatsList, bssr_response, 5000);

	if (test)
	{
		printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

		SDP::FUNCTIONS::printResponse(bssr_response);

		SDP::OBEX::SUPPORTED_FORMATS* supported_formats_handle = new SDP::OBEX::SUPPORTED_FORMATS();

		int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::OBEX::SUPPORTED_FORMATS*, BYTE[]>(supported_formats_handle, bssr_response, 5000);


		position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::OBEX::SUPPORTED_FORMATS*, BYTE[]>(supported_formats_handle, bssr_response, 5000, position);

		supported_formats_handle->VALUE.num_of_formats = supported_formats_handle->VALUE.size_bytes / 2;

		supported_formats_handle->VALUE.formats = new BYTE[supported_formats_handle->VALUE.num_of_formats]();

		for (int aa = 1, bb = 0; aa < supported_formats_handle->VALUE.size_bytes; aa += 2, bb++)
		{
			supported_formats_handle->VALUE.formats[bb] = supported_formats_handle->VALUE.value[aa];
		}
		supported_formats_handle->print<SUPPORTED_FORMATS::VV>(supported_formats_handle->VALUE);

		return 1;
	}

	return 0;
}

