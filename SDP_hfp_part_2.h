#pragma once


namespace SDP
{

	namespace HFP
	{
		class HFP_all_attributes : DEFAULT_all_attributes
		{
		public:

			/* specific */
			PNETWORK network_handle;
			PSUPPORTED_FEATURES supported_features_handle;

			HFP_all_attributes();

			void call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp);
			void print_ALL_ATTR();


		private:
			SHORT att_AG_array[7]{
				ServiceRecordHandle,
				ServiceClassIDList,
				ProtocolDescriptorList,
				BluetoothProfileDescriptorList,
				ServiceName,
				Network,
				SupportedFeatures
			};

		};
	}
};