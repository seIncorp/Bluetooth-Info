#include "main.h"

MAIN::MAIN_FLAGS main_flags{ 0 };
IOCTL_S::DEFAULT_DATA dd{ 0 };



//PLOCAL_RADIO_DEVICE_DATA local_device_radio;
//PCONNECTED_DEVICE_DATA connected_device;

int main(int argc, char *argv[])
{
	MAIN::parseCommand(argc, argv);
	MAIN::executeCommand();

	/***********************************************************/
	/***********************************************************/
	/***********************************************************/
	/* ONLY FOR GCI COMMANDS */
	HANDLE procToken;
	LUID luid;
	TOKEN_PRIVILEGES tp;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &procToken) == 0)
		IOCTL_S::printErrorMessage(GetLastError());

	if (LookupPrivilegeValueW(NULL, SE_LOAD_DRIVER_NAME, &luid) == 0)
		IOCTL_S::printErrorMessage(GetLastError());

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(
		procToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL);
	IOCTL_S::printErrorMessage(GetLastError());

	/***********************************************************/
	/***********************************************************/
	/***********************************************************/



	if (IOCTL_S::connectToDevice())
	{

		dd.bResult = FALSE;
		dd.junk = 0;

		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/
		/* LIST OF CACHED BTH SEARCHED DEVICES */

		if (main_flags.cached_devices_flag)
			IOCTL_S::getBthDeviceInfo();

		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/
		/* INFORMATION LOCAL BTH SYSTEM AND RADIO */

		if (main_flags.local_flag)
			IOCTL_S::getLocalBthInfo();

		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/
		/* SDP search */

		if (main_flags.SDP_flag)
			IOCTL_S::SDPsearch();


		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/
		/*  */

		if (main_flags.devInfo_flag)
			IOCTL_S::testCALLS_1();




		/*if (getDeviceInfo())
			{

			}
			else
				printf("ERROR!!!\n");*/
			//if (getLocalBthInfo())
			//{
			//	
			//}
			//else
			//{
			//	// TODO: print correct error
			//	printf("ERROR!!!\n");
			//}





		



		/*********************************************************************************************/
		/*********************************************************************************************/
		/*********************************************************************************************/


		//TODO: dodaj se vse za getDeviceInfo()







		IOCTL_S::closeConnectionToDevice();
	}
	




	return 0;
}

void MAIN::printHelp()
{
	printf("Commands:\n");
	printf("-h or -H\tto print help\n");
	printf("-SD\t\tprint all cached of previously discovered remote radios that are Bluetooth-enabled\n");
	printf("-local\t\tto get information about the local Bluetooth system and radio\n");
	printf("-SDP\t\tget all data of remote device services\n");

	//printf("-dev\n");
	printf("\n");
}

void MAIN::parseCommand(int argc, char* argv[])
{
	for (int aa = 0; aa < argc; aa++)
	{
		if (std::string(argv[aa]) == "-H" || std::string(argv[aa]) == "-h")
		{
			main_flags.help_flag = 1;
		}

		if (std::string(argv[aa]) == "-SD")
		{
			main_flags.cached_devices_flag = 1;
		}

		if (std::string(argv[aa]) == "-SDP")
		{
			main_flags.SDP_flag = 1;
		}

		if (std::string(argv[aa]) == "-local")
		{
			main_flags.local_flag = 1;
		}

		

		if (std::string(argv[aa]) == "-dev")
		{
			main_flags.devInfo_flag = 1;
		}
	}
}

void MAIN::executeCommand()
{
	if (main_flags.help_flag)
	{
		printHelp();

		main_flags.help_flag = 0;
	}
}