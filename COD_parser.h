#pragma once

typedef struct
{
	struct			// 2 byte
	{
		BYTE format_type : 2;			// 0 - 1 bits
		BYTE minor_device_class : 6;	// 2 - 7 bits
		BYTE major_device_class : 5;	// 8 - 12 bits
		
		// Major Service Classes
		BYTE a0_1: 1;	// 13 bit
		BYTE a0_2: 1;	// 14 bit
		BYTE : 1;		// 15 bit

	} octet1_2;
	
	struct 
	{
		BYTE a1 : 1;	// 16 bit
		BYTE a2 : 1;
		BYTE a3 : 1;
		BYTE a4 : 1;
		BYTE a5 : 1;
		BYTE a6 : 1;
		BYTE a7 : 1;
		BYTE a8 : 1;	// 23 bit
	}octet3;

} COD_data;

void parseCODdata(COD_data* data);
