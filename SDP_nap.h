#pragma once

namespace SDP
{

	/* USED ONLY IN NAP and PANU */
	namespace NAP
	{
		typedef enum
		{
			IpSubnet = 0x0200,
			SecurityDescription = 0x030A,
			NetAccessType = 0x030B,
			MaxNetAccessrate = 0x030C,
			IPv4Subnet = 0x030D,		// TODO:
			IPv6Subnet = 0x030E		// TODO:

		} ATTRIBUTE_ID_PAN;

		std::string getSecurityDescriptionString(SHORT type);
		std::string getNetAccessTypeString(SHORT type);

		typedef struct SECURITY_DESCRIPTION_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				SHORT security_value;
			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Security Description [0x%04X][%s]\n", VALUE.security_value, getSecurityDescriptionString(VALUE.security_value).c_str());
				printf("\n");

			}

		} SECURITY_DESCRIPTION, *PSECURITY_DESCRIPTION;

		typedef struct NET_ACCESS_TYPE_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				SHORT NetAccessType;
			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Type of Network Access Available[0x%04X][%s]\n", VALUE.NetAccessType, getNetAccessTypeString(VALUE.NetAccessType).c_str());
				printf("\n");
			}

		} NET_ACCESS_TYPE, *PNET_ACCESS_TYPE;

		typedef struct MAX_NET_ACCESS_RATE_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				DWORD Maximum_possible_Network_Access_Data_Rate;
			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Maximum possible Network Access Data Rate: 0x%08X\n", VALUE.Maximum_possible_Network_Access_Data_Rate);
				printf("\n");
			}

		} MAX_NET_ACCESS_RATE, *PMAX_NET_ACCESS_RATE;


		int getAndParse_SECURITY_DESCRIPTION_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa, PSECURITY_DESCRIPTION security_description_handle = new SECURITY_DESCRIPTION(), int print = 1);
		int getAndParse_NET_ACCESS_TYPE_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa, PNET_ACCESS_TYPE net_access_type_handle = new NET_ACCESS_TYPE(), int print = 1);
		int getAndParse_MAX_NET_ACCESS_RATE_PAN(ULONG recordHandle, HANDLE_SDP_TYPE aa, PMAX_NET_ACCESS_RATE max_net_access_rate_handle = new MAX_NET_ACCESS_RATE(), int print = 1);


		class NAP_PANU_all_attributes
		{
		public:

			/* default */
			PDEFAULT_OBJECT record_handle;
			PSERVICE_CLASS_ID_LIST class_id_handle;
			PPROTOCOL_DESCRIPTOR_LIST protocol_descriptor_list_handle;
			PLANGUAGE_BASE_ATTRIBUTE_ID_LIST language_base_attribute_id_list_handle;
			PBLUETOOTH_PROFILE_DESCRIPTOR_LIST bluetooth_profile_descriptor_list_handle;
			PSERVICE_NAME service_name_handle;
			PSERVICE_DESCRIPTION service_description_handle;


			/* specific */
			PSECURITY_DESCRIPTION security_description_handle;
			PNET_ACCESS_TYPE net_access_type_handle;
			PMAX_NET_ACCESS_RATE max_net_access_rate_handle;
			

			int nap_flag;

			NAP_PANU_all_attributes(int nap = 1);

			void call_ALL_ATTR(DEVICE_DATA_SDP* device_data_sdp);
			void print_ALL_ATTR();


		private:
			SHORT nap_att_array[11]{
				ServiceRecordHandle,
				ServiceClassIDList,
				ProtocolDescriptorList,
				LanguageBaseAttributeIDList,
				ServiceAvailability,
				BluetoothProfileDescriptorList,
				ServiceName,
				ServiceDescription,
				SecurityDescription,
				NetAccessType,
				MaxNetAccessrate
				// TODO: naredi se za IPv4Subnet in IPv6Subnet
			};

			SHORT panu_att_array[9]{
				ServiceRecordHandle,
				ServiceClassIDList,
				ProtocolDescriptorList,
				LanguageBaseAttributeIDList,
				ServiceAvailability,
				BluetoothProfileDescriptorList,
				ServiceName,
				ServiceDescription,
				SecurityDescription
			};

		};









	};

};