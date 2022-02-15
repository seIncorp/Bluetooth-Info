#pragma once

namespace SDP
{

	/* USED ONLY IN NAP and PANU */
	namespace NAP
	{

		class NAP_PANU_all_attributes : DEFAULT_all_attributes
		{
		public:

			/* specific */
			PSECURITY_DESCRIPTION security_description_handle;
			PNET_ACCESS_TYPE net_access_type_handle;
			PMAX_NET_ACCESS_RATE max_net_access_rate_handle;
			
			int nap_flag;

			NAP_PANU_all_attributes(int nap = 1);

			void call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp);
			void print_ALL_ATTR();


		private:
			SHORT nap_att_array[11]{
				ServiceRecordHandle,
				ServiceClassIDList,
				ProtocolDescriptorList,
				LanguageBaseAttributeIDList,
				ServiceAvailability,
				BluetoothProfileDescriptorList,
				ServiceName,
				ServiceDescription,
				SecurityDescription,
				NetAccessType,
				MaxNetAccessrate
				// TODO: naredi se za IPv4Subnet in IPv6Subnet
			};

			SHORT panu_att_array[9]{
				ServiceRecordHandle,
				ServiceClassIDList,
				ProtocolDescriptorList,
				LanguageBaseAttributeIDList,
				ServiceAvailability,
				BluetoothProfileDescriptorList,
				ServiceName,
				ServiceDescription,
				SecurityDescription
			};

		};
	};
};