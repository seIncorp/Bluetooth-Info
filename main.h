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
#include "BTH_devices.h"


#include "ioctl_data.h"


/*****************************************/
/* SDP */
#include "SDP.h"
#include "SDP_sub_functions.h"
#include "SDP_services_objects.h"
#include "SDP_enums.h"
#include "SDP_classes.h"
#include "SDP_nap_part_1.h"
#include "SDP_map_part_1.h"
#include "SDP_pbap_part_1.h"
#include "SDP_obex_part_1.h"
#include "SDP_hfp_part_1.h"
#include "SDP_pnpinfo_part_1.h"
#include "SDP_a2dp_part_1.h"
#include "SDP_avrcp_part_1.h"
#include "SDP_hsp_part_1.h"
#include "SDP_functions.h"
#include "SDP_nap_part_2.h"
#include "SDP_map_part_2.h"
#include "SDP_pbap_part_2.h"
#include "SDP_obex_part_2.h"
#include "SDP_hfp_part_2.h"
#include "SDP_pnpinfo_part_2.h"
#include "SDP_a2dp_part_2.h"
#include "SDP_avrcp_part_2.h"
#include "SDP_hsp_part_2.h"
/*****************************************/






#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Bthprops.lib")
#pragma comment(lib, "Ole32.lib")



namespace MAIN
{
	typedef struct
	{
		int help_flag;
		int cached_devices_flag;
		int local_flag;
		int devInfo_flag;
		int SDP_flag;


	} MAIN_FLAGS;

	void parseCommand(int argc, char* argv[]);
	void executeCommand();
	void printHelp();


	
}





extern MAIN::MAIN_FLAGS main_flags;

