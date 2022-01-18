#pragma once

#define MAX_SEARCHED_SHOWED_DEVICE 30

typedef struct CACHED_DEVICE_S
{
	CACHED_DEVICE_S(char n[BTH_MAX_NAME_SIZE], BYTE add[6], ULONG flags) : flags_{ flags}
	{
		strcpy_s(name_, BTH_MAX_NAME_SIZE,n);
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

} CACHED_DEVICE, *PCACHED_DEVICE;


typedef struct SEARCHED_CACHED_DEVICES_S
{
	ULONG numOfDevices;
	std::vector<CACHED_DEVICE> devices;

} SEARCHED_CACHED_DEVICES, *PSEARCHED_CACHED_DEVICES;



extern PSEARCHED_CACHED_DEVICES devices;