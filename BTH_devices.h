#pragma once

#define MAX_SEARCHED_SHOWED_DEVICE 30

namespace BTH_DEVICES
{
	typedef struct CACHED_DEVICE_S
	{
		CACHED_DEVICE_S(char n[BTH_MAX_NAME_SIZE], BYTE add[6], ULONG flags) : flags_{ flags }
		{
			strcpy_s(name_, BTH_MAX_NAME_SIZE, n);
			for (int a = 0; a < 6; a++)
				address_[a] = add[a];
		};

		void print()
		{
			printf("Name: %s\n", name_);
			printf("Flags: %lu\n", flags_);
			printf("Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				address_[5],
				address_[4],
				address_[3],
				address_[2],
				address_[1],
				address_[0]);
			printf("\n");

			// TODO: add flag printing
		};

		ULONG flags_;
		char name_[BTH_MAX_NAME_SIZE];
		BYTE address_[6];

	} CACHED_DEVICE, * PCACHED_DEVICE;

	typedef struct SEARCHED_CACHED_DEVICES_S
	{
		ULONG numOfDevices;
		std::vector<CACHED_DEVICE> devices;

		void print()
		{
			for (auto d : devices)
				d.print();
		}

	} SEARCHED_CACHED_DEVICES, * PSEARCHED_CACHED_DEVICES;


	typedef struct DEVICE_DATA_S
	{
		void init(BYTE add[6], ULONG f, char n[BTH_MAX_NAME_SIZE])
		{
			address[0] = add[0];
			address[1] = add[1];
			address[2] = add[2];
			address[3] = add[3];
			address[4] = add[4];
			address[5] = add[5];

			flags = f;

			strcpy_s(name, BTH_MAX_NAME_SIZE, n);
		};

		void print()
		{
			printf("\tDEVICE DATA:\n");
			printf("\t\tName: %s\n", name);
			printf("\t\tAddress: %02X:%02X:%02X:%02X:%02X:%02X\n",
				address[5],
				address[4],
				address[3],
				address[2],
				address[1],
				address[0]);
			printf("\t\tflags: %lu\n", flags);

			cod->print();
		}

		CHAR name[BTH_MAX_NAME_SIZE];
		BYTE address[6];
		ULONG flags;
		COD_PARSER::PDEVICE_PARSED_COD_DATA cod;

	} DEVICE_DATA, * PDEVICE_DATA;

	typedef struct RADIO_DATA_S
	{
		RADIO_DATA_S(ULONGLONG lsf, USHORT m, USHORT ls, UCHAR lv) :
			LMP_SupportedFeatures{ lsf },
			mfg{ m },
			LMP_minor_version{ ls },
			LMP_major_version{ lv }
		{

		};

		void print()
		{
			printf("\tRADIO DATA:\n");
			printf("\t\tLMP version: %d.%d\n", LMP_major_version, LMP_minor_version);
			printf("\t\tLMP Supported Features: %X\n", LMP_SupportedFeatures);
			printf("\t\tID of the manufacturer: %d\n", mfg);
		}


		ULONGLONG LMP_SupportedFeatures;
		USHORT mfg;
		USHORT LMP_minor_version;
		UCHAR LMP_major_version;

	} RADIO_DATA, * PRADIO_DATA;


	typedef struct CONNECTED_DEVICE_DATA_S
	{
		PRADIO_DATA radio;


		void print()
		{
			radio->print();
		};

	} CONNECTED_DEVICE_DATA, * PCONNECTED_DEVICE_DATA;

	typedef struct LOCAL_RADIO_DEVICE_DATA_S
	{
		LOCAL_RADIO_DEVICE_DATA_S(
			ULONG flags,
			USHORT hciRevision,
			UCHAR hciVersion)
			:
			flags_{ flags },
			HCI_minor_version_{ hciRevision },
			HCI_major_version_{ hciVersion }
		{

		};

		void print()
		{
			printf("LOCAL DEVICE and RADIO DATA:\n");
			printf("\tFlags: %X\n", flags_);
			printf("\tVersion: %lu.%lu (Major.Minor version HCI)\n",
				HCI_major_version_,
				HCI_minor_version_
			);
			device->print();
			radio->print();
		}

		ULONG flags_;
		USHORT HCI_minor_version_;
		UCHAR HCI_major_version_;

		PDEVICE_DATA device;
		PRADIO_DATA radio;

	} LOCAL_RADIO_DEVICE_DATA, * PLOCAL_RADIO_DEVICE_DATA;



}