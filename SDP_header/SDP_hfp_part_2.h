#pragma once


namespace SDP
{

	namespace HFP
	{
		class HFP_class : DEFAULT_class
		{
		public:

			/* specific */
			PNETWORK network_handle;
			PSUPPORTED_FEATURES supported_features_handle;

			HFP_class();

			void call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp);
			void print_ALL_ATTR();

			void call_Network(DEVICE_DATA_SDP* device_data_sdp);
			void call_SupportedFeatures(DEVICE_DATA_SDP* device_data_sdp);


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