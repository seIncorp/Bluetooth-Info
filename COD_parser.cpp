#include "main.h"

void parseCODdata(COD_data* data, PDEVICE_PARSED_COD_DATA cod)
{
	if (data->octet1_2.a0_1)
	{
		cod->major_service_class.push_back((char*)"Limited Discoverable Mode");
	}

	if (data->octet1_2.a0_2)
	{
		cod->major_service_class.push_back((char*)"LE audio");
	}

	if (data->octet3.a1)
	{
		cod->major_service_class.push_back((char*)"Positioning (Location identification)");
	}

	if (data->octet3.a2)
	{
		cod->major_service_class.push_back((char*)"Networking (LAN, Ad hoc, ...)");
	}

	if (data->octet3.a3)
	{
		cod->major_service_class.push_back((char*)"Rendering (Printing, Speaker, ...)");
	}

	if (data->octet3.a4)
	{
		cod->major_service_class.push_back((char *)"Capturing (Scanner, Microphone, ...)");
	}

	if (data->octet3.a5)
	{
		cod->major_service_class.push_back((char*)"Object Transfer (v-Inbox, v-Folder, ...)");
	}

	if (data->octet3.a6)
	{
		cod->major_service_class.push_back((char*)"Audio (Speaker, Microphone, Headset service, ...)");
	}

	if (data->octet3.a7)
	{
		cod->major_service_class.push_back((char*)"Telephony (Cordless telephony, Modem, Headset service, ...)");
	}

	if (data->octet3.a8)
	{
		cod->major_service_class.push_back((char*)"Information (WEB-server, WAP-server, ...)");
	}


	if (data->octet1_2.major_device_class == 0x00)
	{
		cod->major_device_class.push_back((char*)"Miscellaneous");
	}

	if (data->octet1_2.major_device_class == 0x01)
	{
		cod->major_device_class.push_back((char*)"Computer (desktop,notebook, PDA, organizers, .... )");


		switch (data->octet1_2.minor_device_class)
		{
			case 0x00:
				cod->minor_device_class.push_back((char*)"Uncategorized, code for device not assigned");
			break;

			case 0x01:
				cod->minor_device_class.push_back((char*)"Desktop workstation");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"Server-class computer");
			break;

			case 0x03:
				cod->minor_device_class.push_back((char*)"Laptop");
			break;

			case 0x04:
				cod->minor_device_class.push_back((char*)"Handheld PC/PDA (clamshell)");
			break;

			case 0x05:
				cod->minor_device_class.push_back((char*)"Palm-size PC/PDA");
			break;

			case 0x06:
				cod->minor_device_class.push_back((char*)"Wearable computer (watch size)");
			break;

			case 0x07:
				cod->minor_device_class.push_back((char*)"Tablet");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x02)
	{
		cod->major_device_class.push_back((char*)"Phone (cellular, cordless, payphone, modem, ...)");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x00:
				cod->minor_device_class.push_back((char*)"Uncategorized, code for device not assigned");
			break;

			case 0x01:
				cod->minor_device_class.push_back((char*)"Cellular");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"Cordless");
			break;

			case 0x03:
				cod->minor_device_class.push_back((char*)"Smart phone");
			break;

			case 0x04:
				cod->minor_device_class.push_back((char*)"Wired modem or voice gateway");
			break;

			case 0x05:
				cod->minor_device_class.push_back((char*)"Common ISDN Access");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x03)
	{
		cod->major_device_class.push_back((char*)"LAN/Network Access point");

		WORD* test = (WORD*)&data->octet1_2;
		typedef struct
		{
			struct			// 1 BYTE
			{
				// 2 bita
				BYTE format_type : 2;			// 0 1

				// 6 bitov
				BYTE minor_device_class_1 : 3;	// 2 3 4
				BYTE minor_device_class_2 : 3;	// 5 6 7


			} byte_1;

			BYTE byte_2;		// 1 BYTE
		} AA;

		AA* aa = new AA();
		aa = (AA*)test;

		switch (aa->byte_1.minor_device_class_2)
		{
			case 0x00:
				cod->minor_device_class.push_back((char*)"Fully available");
			break;

			case 0x01:
				cod->minor_device_class.push_back((char*)"1 - 17%c utilized");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"17 - 33%c utilized");
			break;

			case 0x03:
				cod->minor_device_class.push_back((char*)"33 - 50%c utilized");
			break;

			case 0x04:
				cod->minor_device_class.push_back((char*)"50 - 67%c utilized");
			break;

			case 0x05:
				cod->minor_device_class.push_back((char*)"67 - 83%c utilized");
			break;

			case 0x06:
				cod->minor_device_class.push_back((char*)"83 - 99%c utilized");
			break;

			case 0x07:
				cod->minor_device_class.push_back((char*)"No service available");
			break;
		}

		switch (aa->byte_1.minor_device_class_1)
		{
			case 0x00:
				//printf("\t\t\tUncategorized (use this value if no other apply)\n");
			break;

			default:
				//printf("\t\t\tAll other values reserved\n");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x04)
	{
		cod->major_device_class.push_back((char*)"Audio/Video (headset, speaker, stereo, video display, VCR, …");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x00:
				cod->minor_device_class.push_back((char*)"Uncategorized, code not assigned");
			break;

			case 0x01:
				cod->minor_device_class.push_back((char*)"Wearable Headset Device");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"Hands-free Device");
			break;

			case 0x03:
				
			break;

			case 0x04:
				cod->minor_device_class.push_back((char*)"Microphone");
			break;

			case 0x05:
				cod->minor_device_class.push_back((char*)"Loudspeaker");
			break;

			case 0x06:
				cod->minor_device_class.push_back((char*)"Headphones");
			break;

			case 0x07:
				cod->minor_device_class.push_back((char*)"Portable Audio");
			break;

			case 0x08:
				cod->minor_device_class.push_back((char*)"Car audio");
			break;

			case 0x09:
				cod->minor_device_class.push_back((char*)"Set-top box");
			break;

			case 0x0a:
				cod->minor_device_class.push_back((char*)"HiFi Audio Device");
			break;

			case 0x0b:
				cod->minor_device_class.push_back((char*)"VCR");
			break;

			case 0x0c:
				cod->minor_device_class.push_back((char*)"Video Camera");
			break;

			case 0x0d:
				cod->minor_device_class.push_back((char*)"Camcorder");
			break;

			case 0x0e:
				cod->minor_device_class.push_back((char*)"Video Monitor");
			break;

			case 0x0f:
				cod->minor_device_class.push_back((char*)"Video Display and Loudspeaker");
			break;

			case 0x10:
				cod->minor_device_class.push_back((char*)"Video Conferencing");
			break;

			case 0x11:
				
			break;

			case 0x12:
				cod->minor_device_class.push_back((char*)"Gaming/Toy");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x05)
	{
		cod->major_device_class.push_back((char*)"Peripheral (mouse, joystick, keyboard, … )");

		WORD* test = (WORD*)&data->octet1_2;
		typedef struct
		{
			struct			// 1 BYTE
			{
				// 2 bita
				BYTE format_type : 2;			// 0 1

				// 6 bitov
				BYTE minor_device_class_1 : 4;	// 2 3 4 5
				BYTE minor_device_class_2 : 2;	// 6 7


			} byte_1;

			BYTE byte_2;		// 1 BYTE
		} AA;

		AA* aa = new AA();
		aa = (AA*)test;

		switch (aa->byte_1.minor_device_class_2)
		{
			case 0x00:
				cod->minor_device_class.push_back((char*)"Not Keyboard / Not Pointing Device");
			break;

			case 0x01:
				cod->minor_device_class.push_back((char*)"Keyboard");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"Pointing device");
			break;

			case 0x03:
				cod->minor_device_class.push_back((char*)"Combo keyboard/pointing device");
			break;
		}

		switch (aa->byte_1.minor_device_class_1)
		{
			case 0x00:
				cod->minor_device_class.push_back((char*)"Uncategorized device");
			break;

			case 0x01:
				cod->minor_device_class.push_back((char*)"Joystick");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"Gamepad");
			break;

			case 0x03:
				cod->minor_device_class.push_back((char*)"Remote control");
			break;

			case 0x04:
				cod->minor_device_class.push_back((char*)"Sensing device");
			break;

			case 0x05:
				cod->minor_device_class.push_back((char*)"Digitizer tablet");
			break;

			case 0x06:
				cod->minor_device_class.push_back((char*)"Card Reader (e.g. SIM Card Reader)");
			break;

			case 0x07:
				cod->minor_device_class.push_back((char*)"Digital Pen");
			break;

			case 0x08:
				cod->minor_device_class.push_back((char*)"Handheld scanner for bar-codes, RFID, etc");
			break;

			case 0x09:
				cod->minor_device_class.push_back((char*)"Handheld gestural input device (e.g., “wand” form factor)");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x06)
	{
		cod->major_device_class.push_back((char*)"Imaging (printing, scanner, camera, display, ...)");

		WORD* test = (WORD*)&data->octet1_2;

		typedef struct
		{
			struct			// 1 BYTE
			{
				// 2 bita
				BYTE format_type : 2;			// 0 1

				// 6 bitov
				BYTE minor_device_class_1 : 2;	// 2 3

				BYTE minor_device_class_2_1 : 1;	// 4
				BYTE minor_device_class_2_2 : 1;	// 5
				BYTE minor_device_class_2_3 : 1;	// 6
				BYTE minor_device_class_2_4 : 1;	// 7


			} byte_1;

			BYTE byte_2;		// 1 BYTE
		} AA;

		AA* aa = new AA();
		aa = (AA*)test;

		if (aa->byte_1.minor_device_class_2_1)
		{
			cod->minor_device_class.push_back((char*)"Display");
		}

		if (aa->byte_1.minor_device_class_2_2)
		{
			cod->minor_device_class.push_back((char*)"Camera");
		}

		if (aa->byte_1.minor_device_class_2_3)
		{
			cod->minor_device_class.push_back((char*)"Scanner");
		}

		if (aa->byte_1.minor_device_class_2_4)
		{
			cod->minor_device_class.push_back((char*)"Printer");
		}

		if (aa->byte_1.minor_device_class_1 == 0x00)
		{
			cod->minor_device_class.push_back((char*)"Uncategorized, default");
		}
	}

	if (data->octet1_2.major_device_class == 0x07)
	{
		cod->major_device_class.push_back((char*)"Wearable");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x01:
				cod->minor_device_class.push_back((char*)"Wrist Watch");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"Pager");
			break;

			case 0x03:
				cod->minor_device_class.push_back((char*)"Jacket");
			break;

			case 0x04:
				cod->minor_device_class.push_back((char*)"Helmet");
			break;

			case 0x05:
				cod->minor_device_class.push_back((char*)"Glasses");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x08)
	{
		cod->major_device_class.push_back((char*)"Toy");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x01:
				cod->minor_device_class.push_back((char*)"Robot");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"Vehicle");
			break;

			case 0x03:
				cod->minor_device_class.push_back((char*)"Doll / Action Figure");
			break;

			case 0x04:
				cod->minor_device_class.push_back((char*)"Controller");
			break;

			case 0x05:
				cod->minor_device_class.push_back((char*)"Game");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x09)
	{
		cod->major_device_class.push_back((char*)"Health");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x00:
				cod->minor_device_class.push_back((char*)"Undefined");
			break;

			case 0x01:
				cod->minor_device_class.push_back((char*)"Blood Pressure Monitor");
			break;

			case 0x02:
				cod->minor_device_class.push_back((char*)"Thermometer");
			break;

			case 0x03:
				cod->minor_device_class.push_back((char*)"Weighing Scale");
			break;

			case 0x04:
				cod->minor_device_class.push_back((char*)"Glucose Meter");
			break;

			case 0x05:
				cod->minor_device_class.push_back((char*)"Pulse Oximeter");
			break;

			case 0x06:
				cod->minor_device_class.push_back((char*)"Heart/Pulse Rate Monitor");
			break;

			case 0x07:
				cod->minor_device_class.push_back((char*)"Health Data Display");
			break;

			case 0x08:
				cod->minor_device_class.push_back((char*)"Step Counter");
			break;

			case 0x09:
				cod->minor_device_class.push_back((char*)"Body Composition Analyzer");
			break;

			case 0x0a:
				cod->minor_device_class.push_back((char*)"Peak Flow Monitor");
			break;

			case 0x0b:
				cod->minor_device_class.push_back((char*)"Medication Monitor");
			break;

			case 0x0c:
				cod->minor_device_class.push_back((char*)"Knee Prosthesis");
			break;

			case 0x0d:
				cod->minor_device_class.push_back((char*)"Ankle Prosthesis");
			break;

			case 0x0e:
				cod->minor_device_class.push_back((char*)"Generic Health Manager");
			break;

			case 0x0f:
				cod->minor_device_class.push_back((char*)"Personal Mobility Device");
			break;
		}
	}
	
	if (data->octet1_2.major_device_class == 0x1f)
	{
		cod->major_device_class.push_back((char*)"Uncategorized: device code not specified");
	}
}