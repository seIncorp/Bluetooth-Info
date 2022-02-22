#include "main.h"

/* only those attributes are used on all services */
void SDP::DEFAULT_class::setDefaultObjects()
{
	record_handle = new DEFAULT_OBJECT();
	class_id_handle = new SERVICE_CLASS_ID_LIST();
	protocol_descriptor_list_handle = new PROTOCOL_DESCRIPTOR_LIST();
	service_name_handle = new SERVICE_NAME();
	bluetooth_profile_descriptor_list_handle = new BLUETOOTH_PROFILE_DESCRIPTOR_LIST();
}


void SDP::DEFAULT_class::call_ServiceRecordHandle(DEVICE_DATA_SDP* device_data_sdp)
{
	FUNCTIONS::getAndParse_DEAFULT<PDEFAULT_OBJECT, DEFAULT_OBJECT_S::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		record_handle,
		SDP::ServiceRecordHandle,
		SDP::ServiceRecordHandle,
		device_data_sdp,
		0
		);
}

void SDP::DEFAULT_class::call_ServiceClassIDList(DEVICE_DATA_SDP* device_data_sdp)
{
	FUNCTIONS::getAndParse_DEAFULT<PSERVICE_CLASS_ID_LIST, SERVICE_CLASS_ID_LIST_S::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		class_id_handle,
		SDP::ServiceClassIDList,
		SDP::ServiceClassIDList,
		device_data_sdp,
		0
	);
}

void SDP::DEFAULT_class::call_ProtocolDescriptorList(DEVICE_DATA_SDP* device_data_sdp)
{
	FUNCTIONS::getAndParse_DEAFULT<PPROTOCOL_DESCRIPTOR_LIST, PROTOCOL_DESCRIPTOR_LIST_S::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		protocol_descriptor_list_handle,
		SDP::ProtocolDescriptorList,
		SDP::ProtocolDescriptorList,
		device_data_sdp,
		0
	);
}

void SDP::DEFAULT_class::call_ServiceName(DEVICE_DATA_SDP* device_data_sdp)
{
	FUNCTIONS::getAndParse_DEAFULT<PSERVICE_NAME, SERVICE_NAME::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		service_name_handle,
		SDP::ServiceName,
		SDP::ServiceName,
		device_data_sdp,
		0
	);
}

void SDP::DEFAULT_class::call_BluetoothProfileDescriptorList(DEVICE_DATA_SDP* device_data_sdp)
{
	FUNCTIONS::getAndParse_DEAFULT<PBLUETOOTH_PROFILE_DESCRIPTOR_LIST, BLUETOOTH_PROFILE_DESCRIPTOR_LIST::VV>(
		device_data_sdp->buffer_res[0],
		device_data_sdp->bsc->HANDLE_SDP_FIELD_NAME,
		bluetooth_profile_descriptor_list_handle,
		SDP::BluetoothProfileDescriptorList,
		SDP::BluetoothProfileDescriptorList,
		device_data_sdp,
		0
	);
}



void SDP::DEFAULT_class::callDefaultAttributes(DEVICE_DATA_SDP* device_data_sdp)
{
	call_ServiceRecordHandle(device_data_sdp);
	call_ServiceClassIDList(device_data_sdp);
	call_ProtocolDescriptorList(device_data_sdp);
	call_ServiceName(device_data_sdp);
	call_BluetoothProfileDescriptorList(device_data_sdp);
}

void SDP::DEFAULT_class::printDefaultData()
{
	if(record_handle != NULL)
		record_handle->print(record_handle->VALUE);

	if (class_id_handle != NULL)
		class_id_handle->print<SERVICE_CLASS_ID_LIST_S::VV>(class_id_handle->VALUE);

	if (protocol_descriptor_list_handle != NULL)
		protocol_descriptor_list_handle->print<PROTOCOL_DESCRIPTOR_LIST_S::VV>(protocol_descriptor_list_handle->VALUE);

	if (service_name_handle != NULL)
		service_name_handle->print<SERVICE_NAME_S::VV>(service_name_handle->VALUE);

	if (provider_name_handle != NULL)
		provider_name_handle->print<PROVIDER_NAME_S::VV>(provider_name_handle->VALUE);

	if (bluetooth_profile_descriptor_list_handle != NULL)
		bluetooth_profile_descriptor_list_handle->print<BLUETOOTH_PROFILE_DESCRIPTOR_LIST_S::VV>(bluetooth_profile_descriptor_list_handle->VALUE);

	if (language_base_attribute_id_list_handle != NULL)
		language_base_attribute_id_list_handle->print<LANGUAGE_BASE_ATTRIBUTE_ID_LIST_S::VV>(language_base_attribute_id_list_handle->VALUE);

	if (service_description_handle != NULL)
		service_description_handle->print<SERVICE_DESCRIPTION_S::VV>(service_description_handle->VALUE);

}