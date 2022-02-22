#pragma once


namespace SDP
{

	namespace NAP
	{
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

		} SECURITY_DESCRIPTION, * PSECURITY_DESCRIPTION;

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

		} NET_ACCESS_TYPE, * PNET_ACCESS_TYPE;

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

		} MAX_NET_ACCESS_RATE, * PMAX_NET_ACCESS_RATE;


		void parse_SECURITY_DESCRIPTION_PAN(PSECURITY_DESCRIPTION handle);
		void parse_NET_ACCESS_TYPE_PAN(PNET_ACCESS_TYPE handle);
		void parse_MAX_NET_ACCESS_RATE_PAN(PMAX_NET_ACCESS_RATE handle);


		template<class C>
		void parse_by_type_sub_function(const std::type_info& type, C handle, SHORT current_used_service)
		{
			const std::type_info& a10 = typeid(SECURITY_DESCRIPTION_S*);
			const std::type_info& a11 = typeid(NET_ACCESS_TYPE_S*);
			const std::type_info& a12 = typeid(MAX_NET_ACCESS_RATE_S*);

			// SecurityDescription
			if (type == a10)
			{
				parse_SECURITY_DESCRIPTION_PAN((PSECURITY_DESCRIPTION)handle);
			}

			// NetAccessType
			if (type == a11)
			{
				parse_NET_ACCESS_TYPE_PAN((PNET_ACCESS_TYPE)handle);
			}

			// MaxNetAccessrate
			if (type == a12)
			{
				parse_MAX_NET_ACCESS_RATE_PAN((PMAX_NET_ACCESS_RATE)handle);
			}
		}
	}
}