#include "main.h"

int connectToDevice(const wchar_t* name)
{
	dd.hDevice = CreateFileW(
		DEFAULT_DEVICE,							// drive to open
		GENERIC_READ | GENERIC_WRITE,			// no access to the drive
		FILE_SHARE_READ | FILE_SHARE_WRITE,		// share mode
		NULL,									// default security attributes
		OPEN_EXISTING,							// disposition
		0,										// file attributes
		NULL);									// do not copy file attributes

	if (dd.hDevice == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	return 1;
}

int closeConnectionToDevice()
{
	if (CloseHandle(dd.hDevice) == 0)
		return 0;
	return 1;
}

// LIST OF CACHED BTH SEARCHED DEVICES
int getBthDeviceInfo()
{
	BYTE data_2[sizeof(BTH_DEVICE_INFO_LIST) + (MAX_SEARCHED_SHOWED_DEVICE - 1) * sizeof(BTH_DEVICE_INFO)]{ 0 };

	dd.bResult = DeviceIoControl(
		dd.hDevice, // device to be queried
		IOCTL_BTH_GET_DEVICE_INFO, // operation to perform
		NULL, 0,                       // no input buffer
		data_2, sizeof(data_2),             // output buffer
		&dd.junk,                         // # bytes returned
		(LPOVERLAPPED)NULL);          // synchronous I/O

	if (dd.bResult)
	{
		BTH_DEVICE_INFO_LIST* bdil = (BTH_DEVICE_INFO_LIST*)data_2;
		BTH_DEVICE_INFO* bdi = bdil->deviceList;

		devices = new SEARCHED_CACHED_DEVICES();
		devices->numOfDevices = bdil->numOfDevices;

		for (int a = 0; a < bdil->numOfDevices; a++)
		{
			BLUETOOTH_ADDRESS_STRUCT* bas = (BLUETOOTH_ADDRESS_STRUCT*)&((bdi + a)->address);

			CACHED_DEVICE_S temp{ (bdi + a)->name, bas->rgBytes, (bdi + a)->flags };

			devices->devices.push_back(temp);
		}

		return 1;
	}
	else
		return 0;
}

// information about the local Bluetooth system and radio
int getLocalBthInfo()
{
	BTH_LOCAL_RADIO_INFO blri{ 0 };

	dd.bResult = DeviceIoControl(
		dd.hDevice, // device to be queried
		IOCTL_BTH_GET_LOCAL_INFO, // operation to perform
		NULL, 0,                       // no input buffer
		&blri, sizeof(blri),             // output buffer
		&dd.junk,                         // # bytes returned
		(LPOVERLAPPED)NULL);          // synchronous I/O

	if (dd.bResult)
	{
		BTH_DEVICE_INFO bdi = blri.localInfo;
		BTH_RADIO_INFO* bri = &blri.radioInfo;
		
		local_device_radio = new LOCAL_RADIO_DEVICE_DATA_S{ 
																blri.flags,
																blri.hciRevision,
																blri.hciVersion
															};
		
		DEVICE_DATA_S temp_d;
		
		temp_d.init(
			((BLUETOOTH_ADDRESS_STRUCT*)(&bdi.address))->rgBytes,
			bdi.flags,
			bdi.name
		);
		local_device_radio->device = &temp_d;

		PDEVICE_PARSED_COD_DATA cod_temp = new DEVICE_PARSED_COD_DATA();
		parseCODdata((COD_data*)&bdi.classOfDevice, cod_temp);
		local_device_radio->device->cod = cod_temp;

		RADIO_DATA_S temp_s{ bri->lmpSupportedFeatures ,bri->mfg,bri->lmpSubversion, bri->lmpVersion };
		local_device_radio->radio = &temp_s;

		// TODO: preveri tezavo s prikazom zunaj
		local_device_radio->print();

		return 1;
	}

	return 0;
}









