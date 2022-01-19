#include "main.h"

MAIN_FLAGS main_flags{ 0 };
DEFAULT_DATA dd{ 0 };
PSEARCHED_CACHED_DEVICES devices;
PLOCAL_RADIO_DEVICE_DATA local_device_radio;

int main(int argc, char *argv[])
{
	parseCommand(argc, argv);
	executeCommand();


	if (connectToDevice())
	{

		dd.bResult = FALSE;
		dd.junk = 0;

		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/
		/* LIST OF CACHED BTH SEARCHED DEVICES */

		if (main_flags.cached_devices_flag)
			if (getBthDeviceInfo())
			{
				for (int a = 0; a < devices->numOfDevices; a++)
				{
					devices->devices.at(a).print();
				}
			}
			else 
			{
				// TODO: print correct error
				printf("ERROR!!!\n");
			}


		
		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/
		/* INFORMATION LOCAL BTH SYSTEM AND RADIO */

		if (main_flags.local_flag)
			if (getLocalBthInfo())
			{
				
			}
			else
			{
				// TODO: print correct error
				printf("ERROR!!!\n");
			}





		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/
		/*  */

		



		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/




		if (closeConnectionToDevice() == 0)
		{
			// TODO: print correct error
			printf("ERROR!!!\n");
		}


	}
	else
	{
		// TODO: error correct print
		printf("ERROR!!!\n");
	}




	return 0;
}

void printHelp()
{
	printf("Commands:\n");
	printf("-h or -H\tto print help\n");
	printf("-sd\t\tprint all cached of previously discovered remote radios that are Bluetooth-enabled\n");
	printf("-local\t\tto get information about the local Bluetooth system and radio\n");
	//printf("-dev\n");
	printf("\n");
}

void parseCommand(int argc, char* argv[])
{
	for (int aa = 0; aa < argc; aa++)
	{
		if (std::string(argv[aa]) == "-H" || std::string(argv[aa]) == "-h")
		{
			main_flags.help_flag = 1;
		}

		if (std::string(argv[aa]) == "-sd")
		{
			main_flags.cached_devices_flag = 1;
		}

		if (std::string(argv[aa]) == "-local")
		{
			main_flags.local_flag = 1;
		}

		/*if (std::string(argv[aa]) == "-dev")
		{
			main_flags.devInfo_flag = 1;
		}*/
	}
}

void executeCommand()
{
	if (main_flags.help_flag)
	{
		printHelp();

		main_flags.help_flag = 0;
	}
}