#pragma once
namespace SDP
{
	class DEFAULT_all_attributes
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

		/* default functions */
		void setDefaultObjects();
		void callDefaultAttributes(DEVICE_DATA_SDP* device_data_sdp);
		void printDefaultData();
	};
}
