#include "main.h"



/*********************************************************************************************************************/
/* PNPINFO SPECIFIC */

int SDP::PNPINFO::getAndParse_SPECIFICATION_ID_PNPINFO(ULONG recordHandle, HANDLE_SDP_TYPE aa)
{
	printf("\n\n*** getAndParse_SPECIFICATION_ID_PNPINFO ***\n");

	BYTE bssr_response[5000]{ 0 };
	SDP::PNPINFO::INFO* ttt_handle = new SDP::PNPINFO::INFO();

	BOOL test = FALSE;

	for (SHORT bb = SpecificationID; bb < (VendorIDSource + 0x01); bb++)
	{
		printf("0x%04X\n", bb);

		test = SDP::FUNCTIONS::set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(recordHandle, aa, bb, bb, bssr_response, 5000);

		if (test)
		{
			printf("IOCTL_BTH_SDP_ATTRIBUTE_SEARCH --> OK\n");

			SDP::FUNCTIONS::printResponse(bssr_response);
			int position = SDP::FUNCTIONS::set_save_ATTRIBUTE_ELEMENT<SDP::PNPINFO::INFO*, BYTE[]>(ttt_handle, bssr_response, 5000);

			position = SDP::FUNCTIONS::set_save_VALUE_ELEMENT<SDP::PNPINFO::INFO*, BYTE[]>(ttt_handle, bssr_response, 5000, position);

			if (bb == PrimaryRecord)
			{
				ttt_handle->setIDdata<BOOL>(bb, ttt_handle->VALUE.value[0]);
			}
			else
			{
				SHORT temp = 0x00;
				temp |= ttt_handle->VALUE.value[0];
				temp <<= 8;
				temp |= ttt_handle->VALUE.value[1];
				ttt_handle->setIDdata<SHORT>(bb, temp);
			}
		}
	}

	ttt_handle->print<INFO_S::VV>(ttt_handle->VALUE);

	return 1;
}

