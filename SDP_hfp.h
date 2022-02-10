#pragma once


namespace SDP
{

	namespace HFP
	{
		typedef enum
		{
			Network = 0x0301,
			SupportedFeatures = 0x0311

		} ATTRIBUTE_ID_HFP;

		struct SUPPORTED_FEATURES_DATA_S
		{
			struct SR_S
			{
				BYTE a0 : 1;
				BYTE a1 : 1;
				BYTE a2 : 1;
				BYTE a3 : 1;
				BYTE a4 : 1;
				BYTE a5 : 1;
				BYTE a6 : 1;
				BYTE a7 : 1;
				BYTE : 8;

			};

			SR_S* repo;

			SUPPORTED_FEATURES_DATA_S(SHORT* a) : repo((SR_S*)a)
			{
				printf("FROM STRUCT --> %X\n", *a);
			};

			std::string getSupportedFeatures_AG_String()
			{
				std::string temp = "";

				if (repo->a0)
				{
					temp += "Three-way calling\n";
				}

				if (repo->a1)
				{
					temp += "EC and/or NR function\n";
				}

				if (repo->a2)
				{
					temp += "Voice recognition function\n";
				}

				if (repo->a3)
				{
					temp += "In-band ring tone capability\n";
				}

				if (repo->a4)
				{
					temp += "Attach a phone number to a voice tag\n";
				}

				if (repo->a5)
				{
					temp += "Wide band speech\n";
				}

				if (repo->a6)
				{
					temp += "Enhanced Voice Recognition Status \n";
				}

				if (repo->a7)
				{
					temp += "Voice Recognition Text\n";
				}

				return temp;
			}

			std::string getSupportedFeaturesString()
			{
				std::string temp = "";

				if (repo->a0)
				{
					temp += "EC and/or NR function\n";
				}

				if (repo->a1)
				{
					temp += "Call waiting or three-way calling\n";
				}

				if (repo->a2)
				{
					temp += "CLI presentation capability\n";
				}

				if (repo->a3)
				{
					temp += "Voice recognition activation\n";
				}

				if (repo->a4)
				{
					temp += "Remote volume control\n";
				}

				if (repo->a5)
				{
					temp += "Wide band speech\n";
				}

				if (repo->a6)
				{
					temp += "Enhanced Voice Recognition Status\n";
				}

				if (repo->a7)
				{
					temp += "Voice Recognition Text\n";
				}

				return temp;
			}
		};

		typedef struct NETWORK_S : DEFAULT_OBJECT
		{
			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Network: %s\n", v.value[0] == 0x01 ? "Ability to reject a call" : "No ability to reject a call");
			}

		} NETWORK, * PNETWORK;

		typedef struct SUPPORTED_FEATURES_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				SHORT supported_features_value;

				SUPPORTED_FEATURES_DATA_S* sfds;

			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				// TODO: naredi da bo tudi za brez AG (trenutno narejeno samo za AG)
				printf("Supported features: 0x%04X\n", v.supported_features_value);
				printf("%s\n", v.sfds->getSupportedFeatures_AG_String().c_str());

			}

		} SUPPORTED_FEATURES, * PSUPPORTED_FEATURES;

		int getAndParse_NETWORK_HFP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SUPPORTED_FEATURES_HFP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
	}



};