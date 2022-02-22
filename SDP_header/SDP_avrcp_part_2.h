#pragma once



namespace SDP
{

	namespace AVRCP
	{
		class AVRCP_all_attributes : DEFAULT_class
		{
		public:
			
			PSUPPORTED_FEATURES supported_features_handle;

			DEVICE_DATA_SDP* dds;

			AVRCP_all_attributes();

			void call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp);
			void print_ALL_ATTR();


		private:
			SHORT avrcp_att_array[8]{
				ServiceRecordHandle,
				ServiceClassIDList,
				ProtocolDescriptorList,
				AdditionalProtocolDescriptorList,
				BluetoothProfileDescriptorList,
				SupportedFeatures,
				ProviderName,
				ServiceName
			};
		};

	};

};