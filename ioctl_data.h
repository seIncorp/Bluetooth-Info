#pragma once

#define DEFAULT_DEVICE L"\\\\?\\GLOBALROOT\\Device\\USBPDO-5"

#define BTH_ENUMERATORFL_INCOMING	0x00000001
#define BTH_ENUMERATORFL_OUTGOING	0x00000002
#define BTH_ENUMERATORFL_REENUM		0x00000004

#define BTHPORT_RESERVED_FIELD_SIZE     (2)
#define BTHPORT_CONTEXT_SIZE            (4)



#define OPCODE(ogf, ocf) (ocf | ogf << 10)




namespace IOCTL_S
{
	typedef struct
	{
		HANDLE hDevice;
		BOOL bResult;
		DWORD junk;

		SHORT service_class_id_in_use;

	} DEFAULT_DATA;
	


	int connectToDevice(const wchar_t* name = DEFAULT_DEVICE);
	void closeConnectionToDevice();
	

	int str2ba(const char* straddr, BTH_ADDR* btaddr);


	int SDPsearch();
	int getBthDeviceInfo(int print = 1);
	void getLocalBthInfo();


	void printErrorMessage(DWORD id);
};


extern IOCTL_S::DEFAULT_DATA dd;







int getDeviceInfo();













