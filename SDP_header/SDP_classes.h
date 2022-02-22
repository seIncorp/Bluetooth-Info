#pragma once
namespace SDP
{
	class DEFAULT_class
	{
	public:
		/* default */
		PDEFAULT_OBJECT record_handle;
		PSERVICE_CLASS_ID_LIST class_id_handle;
		PPROTOCOL_DESCRIPTOR_LIST protocol_descriptor_list_handle;
		PSERVICE_NAME service_name_handle;
		PPROVIDER_NAME provider_name_handle;
		PBLUETOOTH_PROFILE_DESCRIPTOR_LIST bluetooth_profile_descriptor_list_handle;
		PLANGUAGE_BASE_ATTRIBUTE_ID_LIST language_base_attribute_id_list_handle;
		PSERVICE_DESCRIPTION service_description_handle;

		/* default functions (all att) */
		void setDefaultObjects();
		void callDefaultAttributes(DEVICE_DATA_SDP* device_data_sdp);
		void printDefaultData();

		/* default functions (one att at time) */
		void call_ServiceRecordHandle(DEVICE_DATA_SDP* device_data_sdp);
		void call_ServiceClassIDList(DEVICE_DATA_SDP* device_data_sdp);
		void call_ProtocolDescriptorList(DEVICE_DATA_SDP* device_data_sdp);
		void call_ServiceName(DEVICE_DATA_SDP* device_data_sdp);
		void call_BluetoothProfileDescriptorList(DEVICE_DATA_SDP* device_data_sdp);



	private:

		SHORT list_att[5]{
			ServiceRecordHandle,
			ServiceClassIDList,
			ProtocolDescriptorList,
			ServiceName,
			BluetoothProfileDescriptorList
		};

	};
}
