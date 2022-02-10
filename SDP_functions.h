#pragma once

namespace SDP
{

	namespace FUNCTIONS
	{
		std::string getElementTypeString(BYTE type);
		int getElementSize(BYTE size, int* add_bits);
		std::string getProtocolTypeString(SHORT type);
		std::string getNetworkPacketTypeString(SHORT type);


		/* SET, CONNECT, DISCONNECT FROM SDP DEVICE */
		void init_for_IOCTL_BTH_SDP_CONNECT(char add[], DEVICE_DATA_SDP* device_data_sdp);
		void call_IOCTL_BTH_SDP_CONNECT(DEVICE_DATA_SDP* device_data_sdp);
		void call_IOCTL_BTH_SDP_SERVICE_SEARCH();



		BOOL call_IOCTL_BTH_SDP_ATTRIBUTE_SEARCH(BTH_SDP_ATTRIBUTE_SEARCH_REQUEST* bsasr, BYTE bssr_response[], int res_length);
		BOOL set_and_call_BTH_SDP_ATTRIBUTE_SEARCH(ULONG recordHandle, HANDLE_SDP_TYPE aa, USHORT minAttr, USHORT maxAttr, BYTE res[], int res_length);

		void printResponse(BYTE bssr_response[]);

		int getAndParse_SERVICE_RECORD_HANDLE(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_CLASS_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_PROTOCOL_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_NAME(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_PROVIDER_NAME(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_BLUETOOTH_PROFILE_DESCRIPTOR_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_LANGUAGE_BASE_ATTRIBUTE_ID_LIST(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_AVAILABILITY(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SERVICE_DESCRIPTION(ULONG recordHandle, HANDLE_SDP_TYPE aa);
	
		template<class A, class B>
		int set_save_ATTRIBUTE_ELEMENT(A id_handle, B res, int res_length) 
		{
			int position = sizeof(BTH_SDP_STREAM_RESPONSE) + 1 + 0;

			SDP::PATTRIBUTE_ID_ELEMENT record_handle_element = new SDP::ATTRIBUTE_ID_ELEMENT();
			record_handle_element = (SDP::PATTRIBUTE_ID_ELEMENT)(res + position);

			id_handle->attr_id = new ATTR_ID();
			id_handle->attr_id->element = record_handle_element;



			int temp_size = SDP::FUNCTIONS::getElementSize(id_handle->attr_id->element->element.size, &(id_handle->attr_id->additional_bits_flag));

			if (id_handle->attr_id->additional_bits_flag)
			{
				id_handle->attr_id->additional_bits_for_size = temp_size;

				// TODO: nadaljuj z branjem dodatnih byte-ov
			}
			else
			{
				id_handle->attr_id->size_bytes = temp_size;
				position++;

				id_handle->attr_id->value = (BYTE*)malloc(id_handle->attr_id->size_bytes * sizeof(BYTE));
				memset(id_handle->attr_id->value, 0x00, id_handle->attr_id->size_bytes);
				for (int a = 0; a < id_handle->attr_id->size_bytes; a++)
				{
					position += a;
					//printf("%X ", *(res + position));
					id_handle->attr_id->value[a] = *(res + position);
				}
				printf("\n");
			}

			position++;

			return position;
		}

		template<class A, class B>
		int set_save_VALUE_ELEMENT(A id_handle, B res, int res_length, int position) 
		{
			SDP::PATTRIBUTE_ID_ELEMENT record_handle_element_2 = new SDP::ATTRIBUTE_ID_ELEMENT();
			record_handle_element_2 = (SDP::PATTRIBUTE_ID_ELEMENT)(res + position);

			id_handle->VALUE.element = record_handle_element_2;

			int temp_size_VALUE = SDP::FUNCTIONS::getElementSize(id_handle->VALUE.element->element.size, &(id_handle->VALUE.additional_bits_flag));

			if (id_handle->VALUE.additional_bits_flag)
			{
				id_handle->VALUE.additional_bits_for_size = temp_size_VALUE;

				if (id_handle->VALUE.additional_bits_for_size = 1)
				{
					position++;
					id_handle->VALUE.size_bytes = *(res + position);

					id_handle->VALUE.value = (BYTE*)malloc(id_handle->VALUE.size_bytes * sizeof(BYTE));
					memset(id_handle->VALUE.value, 0x00, id_handle->VALUE.size_bytes);

					position++;
					for (int b = 0; b < id_handle->VALUE.size_bytes; b++)
						id_handle->VALUE.value[b] = *(res + position + b);

				}

				// TODO: naredi se za ostale velikosti 2 in 4
			}
			else
			{
				id_handle->VALUE.size_bytes = temp_size_VALUE;
				position++;

				id_handle->VALUE.value = (BYTE*)malloc(id_handle->VALUE.size_bytes * sizeof(BYTE));
				memset(id_handle->VALUE.value, 0x00, id_handle->VALUE.size_bytes);
				for (int b = 0; b < id_handle->VALUE.size_bytes; b++)
				{

					id_handle->VALUE.value[b] = *(res + position + b);
				}
			}

			position += id_handle->VALUE.size_bytes;

			return position;
		}
	};

}