#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <initguid.h>
#include <winsock2.h>
#include <ws2bth.h>
#include <strsafe.h>
#include <intsafe.h>
#include <bluetoothapis.h>
#include <bthdef.h>
#include <bthsdpdef.h>
#include <combaseapi.h>
#include <bthdef.h>
#include <bthioctl.h>


#include "COD_parser.h"
#include "ioctl_data.h"
#include "devices.h"


#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Bthprops.lib")
#pragma comment(lib, "Ole32.lib")


typedef struct
{
	int help_flag;
	int cached_devices_flag;
	int local_flag;
} MAIN_FLAGS;

extern MAIN_FLAGS main_flags;

void parseCommand(int argc, char* argv[]);
void executeCommand();
void printHelp();