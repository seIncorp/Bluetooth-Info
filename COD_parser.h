#pragma once

namespace COD_PARSER
{
	typedef struct
	{
		struct			// 2 byte
		{
			BYTE format_type : 2;			// 0 - 1 bits
			BYTE minor_device_class : 6;	// 2 - 7 bits
			BYTE major_device_class : 5;	// 8 - 12 bits

			// Major Service Classes
			BYTE a0_1 : 1;	// 13 bit
			BYTE a0_2 : 1;	// 14 bit
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

	typedef struct DEVICE_PARSED_COD_DATA_S
	{
		std::vector<char*> major_service_class;
		std::vector<char*> major_device_class;
		std::vector<char*> minor_device_class;

		void print()
		{
			printf("\tDEVICE COD data: \n");

			printf("\t\tMajor service class:\n");
			for (int a = 0; a < major_service_class.size(); a++)
				printf("\t\t\t%s\n", major_service_class.at(a));

			printf("\t\tMajor device class:\n");
			for (int a = 0; a < major_device_class.size(); a++)
				printf("\t\t\t%s\n", major_device_class.at(a));

			printf("\t\tMinor device class:\n");
			for (int a = 0; a < minor_device_class.size(); a++)
				printf("\t\t\t%s\n", minor_device_class.at(a));
			printf("\n");
		}


	} DEVICE_PARSED_COD_DATA, * PDEVICE_PARSED_COD_DATA;



	void parseCODdata(COD_data* data, PDEVICE_PARSED_COD_DATA cod);
}




