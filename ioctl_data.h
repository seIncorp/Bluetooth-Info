#pragma once

#define DEFAULT_DEVICE L"\\\\?\\GLOBALROOT\\Device\\USBPDO-4"

#define BTH_ENUMERATORFL_INCOMING	0x00000001
#define BTH_ENUMERATORFL_OUTGOING	0x00000002
#define BTH_ENUMERATORFL_REENUM		0x00000004

#define BTHPORT_RESERVED_FIELD_SIZE     (2)
#define BTHPORT_CONTEXT_SIZE            (4)












typedef enum _ENUMERATOR_ACTION {
	ENUMERATOR_ACTION_CREATE = 0,
	ENUMERATOR_ACTION_REMOVE,
	ENUMERATOR_ACTION_DESTROY,
	ENUMERATOR_ACTION_MAX,
} ENUMERATOR_ACTION, * PENUMERATOR_ACTION;


typedef enum _ENUMERATOR_TYPE {
	ENUMERATOR_TYPE_PROTOCOL = 0,
	ENUMERATOR_TYPE_SERVICE,
	ENUMERATOR_TYPE_DEVICE,
	ENUMERATOR_TYPE_MAX,
} ENUMERATOR_TYPE, * PENUMERATOR_TYPE;

typedef struct _BTH_ENUMERATOR_INFO {
	//
	// Type of connection being requested
	//
	ENUMERATOR_TYPE EnumeratorType;

	//
	// Action to take
	//
	ENUMERATOR_ACTION Action;

	//
	// Psm being connected to if this is an L2CAP connect request, RFCOMM
	// DLCI if this is an RFCOMM connection request.
	//
	ULONG Port;

	//
	// Flags
	//

	ULONG Flags;

	//
	// Protocol / Service UUID for the enumeration action
	//
	GUID Guid;

	//
	// Instance ID of the Protocol / Service for BTH_ENUMERATORFL_INCOMING
	//
	ULONG InstanceId;

	//
	// Instance ID str of the Protocol / Service for BTH_ENUMERATORFL_OUTGOING
	//

	WCHAR InstanceIdStr[BTH_MAX_SERVICE_NAME_SIZE];

	//
	// Vendor ID, retrieved from DI SDP record
	//
	USHORT Vid;

	//
	// Product ID, retrieved from DI SDP record
	//
	USHORT Pid;

	//
	// Manufacturer, retrieved from DI SDP record
	//
	USHORT Mfg;

	//
	// Local radio manufacturer, retreived via HCI Command
	//
	USHORT LocalMfg;


	//
	// Vendor ID type, retrieved from DI SDP record
	//
	USHORT VidType;

	//
	// Service Name (Used for local services)
	//
	WCHAR ServiceName[BTH_MAX_SERVICE_NAME_SIZE];

	//
	// Identifier used for remote services.
	//
	CHAR SdpPriLangServiceName[BTH_MAX_SERVICE_NAME_SIZE];

	//
	// Device string passed down on BTH_UPDATE ADD
	//
	WCHAR DeviceString[BTH_MAX_SERVICE_NAME_SIZE];

} BTH_ENUMERATOR_INFO, * PBTH_ENUMERATOR_INFO;

//
// BRB HEADER
//
typedef struct _BRB_HEADER {
	//
	// [IN] Used to enqueue BRBs.  This field is to be used by the current owner
	//      of the BRB.  For instance, once the BRB has been sent to BTHPORT,
	//      the client driver may not use this field since BTHPORT may use it
	//      to enqueue the BRB.
	//
	LIST_ENTRY ListEntry;

	//
	// [IN] Size of the BRB including this header
	//
	ULONG Length;

	//
	// [PRIVATE] BRB Version
	// 0  ==> Bluetooth 1.x version
	// >0 ==> Bluetooth 2.x version or later, filled in by 
	// BthCreateBrb
	//
	USHORT Version; // BRB_VERSION

	//
	// [IN] BRB request type.
	//
	USHORT Type;    // BRB_TYPE


	//
	// [PRIVATE] Internal flags for use by BTHPORT
	//
	ULONG BthportFlags;

	//
	// [OUT] BRB completion status
	//
	NTSTATUS Status;

	//
	// [OUT] BRB completion BtStatus
	//
	BTHSTATUS BtStatus;

	//
	// [PRIVATE] for internal use by BTHPORT only.
	//
	PVOID Context[BTHPORT_CONTEXT_SIZE];

	//
	// for use by client drivers, BTHPORT will never touch these fields.
	//
	PVOID ClientContext[BTHPORT_CONTEXT_SIZE];

	//
	// opaque reserved fields
	//
	ULONG Reserved[BTHPORT_RESERVED_FIELD_SIZE];

} BRB_HEADER;

struct _BRB_GET_LOCAL_BD_ADDR {
	BRB_HEADER Hdr;
	BTH_ADDR   BtAddress;
};





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




	void testCALLS();
	void testCALLS_1();

};


extern IOCTL_S::DEFAULT_DATA dd;







int getDeviceInfo();













