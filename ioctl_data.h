#pragma once

#define DEFAULT_DEVICE L"\\\\?\\GLOBALROOT\\Device\\USBPDO-4"

typedef struct
{
	HANDLE hDevice;
	BOOL bResult;
	DWORD junk;

} DEFAULT_DATA;


extern DEFAULT_DATA dd;



int connectToDevice(const wchar_t* name = DEFAULT_DEVICE);
int closeConnectionToDevice();

int getBthDeviceInfo();
int getLocalBthInfo();











