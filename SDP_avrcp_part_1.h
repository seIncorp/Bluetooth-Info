#pragma once
namespace SDP
{

	namespace AVRCP
	{
		
		// TODO: naredi se za A_V_RemoteControlController (drugo strukturo ker je vec bit-ov in druga razlaga)(AVRCP_v1.6.2.pdf)

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
				BYTE a8 : 1;
				BYTE : 7;
				// TODO: naredi se za RFA
			};

			SR_S* repo;

			SUPPORTED_FEATURES_DATA_S(SHORT* a) : repo((SR_S*)a)
			{
				printf("FROM STRUCT --> %X\n", *a);
			};

			std::string getSupportedFeaturesString()
			{
				std::string temp = "";

				if (repo->a0)
				{
					temp += "Category 1\n";
				}

				if (repo->a1)
				{
					temp += "Category 2\n";
				}

				if (repo->a2)
				{
					temp += "Category 3\n";
				}

				if (repo->a3)
				{
					temp += "Category 4\n";
				}

				if (repo->a4)
				{
					temp += "Player Application Settings\n";
				}

				if (repo->a5)
				{
					temp += "Group Navigation\n";
				}

				if (repo->a6)
				{
					temp += "Supports browsing\n";
				}

				if (repo->a7)
				{
					temp += "Supports multiple media player applications\n";
				}

				if (repo->a8)
				{
					temp += "Supports Cover Art\n";
				}

				return temp;
			}

		};

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


				printf("Supported features: 0x%04X\n", v.supported_features_value);
				printf("%s\n", v.sfds->getSupportedFeaturesString().c_str());

			}

		} SUPPORTED_FEATURES, * PSUPPORTED_FEATURES;





		int getAndParse_SUPPORTED_FEATURES_AVRCP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
	};

};