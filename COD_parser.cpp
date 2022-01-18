#include "main.h"

void parseCODdata(COD_data* data)
{
	printf("\t\tMajor Service Class: %X\n", data->octet3);

	if (data->octet1_2.a0_1)
		printf("\t\tLimited Discoverable Mode\n");

	if (data->octet1_2.a0_2)
		printf("\t\tLE audio\n");

	if(data->octet3.a1)
		printf("\t\tPositioning (Location identification)\n");

	if (data->octet3.a2)
		printf("\t\tNetworking (LAN, Ad hoc, ...)\n");

	if (data->octet3.a3)
		printf("\t\tRendering (Printing, Speaker, ...)\n");

	if (data->octet3.a4)
		printf("\t\tCapturing (Scanner, Microphone, ...)\n");

	if (data->octet3.a5)
		printf("\t\tObject Transfer (v-Inbox, v-Folder, ...)\n");

	if (data->octet3.a6)
		printf("\t\tAudio (Speaker, Microphone, Headset service, ...)\n");

	if (data->octet3.a7)
		printf("\t\tTelephony (Cordless telephony, Modem, Headset service, ...)\n");

	if (data->octet3.a8)
		printf("\t\tInformation (WEB-server, WAP-server, ...)\n");


	printf("\t\tMajor Device Class: %X\n",data->octet1_2.major_device_class);

	if (data->octet1_2.major_device_class == 0x00)
	{
		printf("\t\tMiscellaneous\n");
	}

	if (data->octet1_2.major_device_class == 0x01)
	{
		printf("\t\tComputer (desktop,notebook, PDA, organizers, .... )\n");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x00:
				printf("\t\t\tUncategorized, code for device not assigned\n");
			break;

			case 0x01:
				printf("\t\t\tDesktop workstation\n");
			break;

			case 0x02:
				printf("\t\t\tServer-class computer\n");
			break;

			case 0x03:
				printf("\t\t\tLaptop\n");
			break;

			case 0x04:
				printf("\t\t\tHandheld PC/PDA (clamshell)\n");
			break;

			case 0x05:
				printf("\t\t\tPalm-size PC/PDA\n");
			break;

			case 0x06:
				printf("\t\t\tWearable computer (watch size)\n");
			break;

			case 0x07:
				printf("\t\t\tTablet\n");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x02)
	{
		printf("\t\tPhone (cellular, cordless, payphone, modem, ...)\n");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x00:
				printf("\t\t\tUncategorized, code for device not assigned\n");
			break;

			case 0x01:
				printf("\t\t\tCellular\n");
			break;

			case 0x02:
				printf("\t\t\tCordless\n");
			break;

			case 0x03:
				printf("\t\t\tSmart phone\n");
			break;

			case 0x04:
				printf("\t\t\tWired modem or voice gateway\n");
			break;

			case 0x05:
				printf("\t\t\tCommon ISDN Access\n");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x03)
	{
		printf("\t\tLAN/Network Access point\n");

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
				printf("\t\t\tFully available\n");
			break;

			case 0x01:
				printf("\t\t\t1 - 17%c utilized\n", 0x25);
			break;

			case 0x02:
				printf("\t\t\t17 - 33%c utilized\n", 0x25);
			break;

			case 0x03:
				printf("\t\t\t33 - 50%c utilized\n", 0x25);
			break;

			case 0x04:
				printf("\t\t\t50 - 67%c utilized\n", 0x25);
			break;

			case 0x05:
				printf("\t\t\t67 - 83%c utilized\n", 0x25);
			break;

			case 0x06:
				printf("\t\t\t83 - 99%c utilized\n", 0x25);
			break;

			case 0x07:
				printf("\t\t\tNo service available\n");
			break;
		}

		switch (aa->byte_1.minor_device_class_1)
		{
			case 0x00:
				printf("\t\t\tUncategorized (use this value if no other apply)\n");
			break;

			default:
				printf("\t\t\tAll other values reserved\n");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x04)
	{
		printf("\t\tAudio/Video (headset, speaker, stereo, video display, VCR, …\n");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x00:
				printf("\t\t\tUncategorized, code not assigned\n");
			break;

			case 0x01:
				printf("\t\t\tWearable Headset Device\n");
			break;

			case 0x02:
				printf("\t\t\tHands-free Device\n");
			break;

			case 0x03:
				
			break;

			case 0x04:
				printf("\t\t\tMicrophone\n");
			break;

			case 0x05:
				printf("\t\t\tLoudspeaker\n");
			break;

			case 0x06:
				printf("\t\t\tHeadphones\n");
			break;

			case 0x07:
				printf("\t\t\tPortable Audio\n");
			break;

			case 0x08:
				printf("\t\t\tCar audio\n");
			break;

			case 0x09:
				printf("\t\t\tSet-top box\n");
			break;

			case 0x0a:
				printf("\t\t\tHiFi Audio Device\n");
			break;

			case 0x0b:
				printf("\t\t\tVCR\n");
			break;

			case 0x0c:
				printf("\t\t\tVideo Camera\n");
			break;

			case 0x0d:
				printf("\t\t\tCamcorder\n");
			break;

			case 0x0e:
				printf("\t\t\tVideo Monitor\n");
			break;

			case 0x0f:
				printf("\t\t\tVideo Display and Loudspeaker\n");
			break;

			case 0x10:
				printf("\t\t\tVideo Conferencing\n");
			break;

			case 0x11:
				
			break;

			case 0x12:
				printf("\t\t\tGaming/Toy\n");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x05)
	{
		printf("\t\tPeripheral (mouse, joystick, keyboard, … )\n");

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
				printf("\t\t\tNot Keyboard / Not Pointing Device\n");
			break;

			case 0x01:
				printf("\t\t\tKeyboard\n");
			break;

			case 0x02:
				printf("\t\t\tPointing device\n");
			break;

			case 0x03:
				printf("\t\t\tCombo keyboard/pointing device\n");
			break;
		}

		switch (aa->byte_1.minor_device_class_1)
		{
			case 0x00:
				printf("\t\t\tUncategorized device\n");
			break;

			case 0x01:
				printf("\t\t\tJoystick\n");
			break;

			case 0x02:
				printf("\t\t\tGamepad\n");
			break;

			case 0x03:
				printf("\t\t\tRemote control\n");
			break;

			case 0x04:
				printf("\t\t\tSensing device\n");
			break;

			case 0x05:
				printf("\t\t\tDigitizer tablet\n");
			break;

			case 0x06:
				printf("\t\t\tCard Reader (e.g. SIM Card Reader)\n");
			break;

			case 0x07:
				printf("\t\t\tDigital Pen\n");
			break;

			case 0x08:
				printf("\t\t\tHandheld scanner for bar-codes, RFID, etc\n");
			break;

			case 0x09:
				printf("\t\t\tHandheld gestural input device (e.g., “wand” form factor)\n");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x06)
	{
		printf("\t\tImaging (printing, scanner, camera, display, ...)\n");

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

		if(aa->byte_1.minor_device_class_2_1)
			printf("\t\t\tDisplay\n");
		if (aa->byte_1.minor_device_class_2_2)
			printf("\t\t\tCamera\n");
		if (aa->byte_1.minor_device_class_2_3)
			printf("\t\t\tScanner\n");
		if (aa->byte_1.minor_device_class_2_4)
			printf("\t\t\tPrinter\n");
		if (aa->byte_1.minor_device_class_1 == 0x00)
			printf("\t\t\tUncategorized, default\n");
	}

	if (data->octet1_2.major_device_class == 0x07)
	{
		printf("\t\tWearable\n");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x01:
				printf("\t\t\tWrist Watch\n");
			break;

			case 0x02:
				printf("\t\t\tPager\n");
			break;

			case 0x03:
				printf("\t\t\tJacket\n");
			break;

			case 0x04:
				printf("\t\t\tHelmet\n");
			break;

			case 0x05:
				printf("\t\t\tGlasses\n");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x08)
	{
		printf("\t\tToy\n");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x01:
				printf("\t\t\tRobot\n");
			break;

			case 0x02:
				printf("\t\t\tVehicle\n");
			break;

			case 0x03:
				printf("\t\t\tDoll / Action Figure\n");
			break;

			case 0x04:
				printf("\t\t\tController\n");
			break;

			case 0x05:
				printf("\t\t\tGame\n");
			break;
		}
	}

	if (data->octet1_2.major_device_class == 0x09)
	{
		printf("\t\tHealth\n");

		switch (data->octet1_2.minor_device_class)
		{
			case 0x00:
				printf("\t\t\tUndefined\n");
			break;

			case 0x01:
				printf("\t\t\tBlood Pressure Monitor\n");
			break;

			case 0x02:
				printf("\t\t\tThermometer\n");
			break;

			case 0x03:
				printf("\t\t\tWeighing Scale\n");
			break;

			case 0x04:
				printf("\t\t\tGlucose Meter\n");
			break;

			case 0x05:
				printf("\t\t\tPulse Oximeter\n");
			break;

			case 0x06:
				printf("\t\t\tHeart/Pulse Rate Monitor\n");
			break;

			case 0x07:
				printf("\t\t\tHealth Data Display\n");
			break;

			case 0x08:
				printf("\t\t\tStep Counter\n");
			break;

			case 0x09:
				printf("\t\t\tBody Composition Analyzer\n");
			break;

			case 0x0a:
				printf("\t\t\tPeak Flow Monitor\n");
			break;

			case 0x0b:
				printf("\t\t\tMedication Monitor\n");
			break;

			case 0x0c:
				printf("\t\t\tKnee Prosthesis\n");
			break;

			case 0x0d:
				printf("\t\t\tAnkle Prosthesis\n");
			break;

			case 0x0e:
				printf("\t\t\tGeneric Health Manager\n");
			break;

			case 0x0f:
				printf("\t\t\tPersonal Mobility Device\n");
			break;
		}
	}
	
	if (data->octet1_2.major_device_class == 0x1f)
		printf("\t\tUncategorized: device code not specified\n");

}