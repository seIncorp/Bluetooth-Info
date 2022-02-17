#pragma once
namespace SDP
{

	namespace AVRCP
	{
		
		// TODO: naredi se za A_V_RemoteControlController (drugo strukturo ker je vec bit-ov in druga razlaga)(AVRCP_v1.6.2.pdf)

		struct SUPPORTED_FEATURES_DATA_S
		{
			struct AVRCT_S
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

			struct AVRC_AVRCC_S
			{
				BYTE a0 : 1;
				BYTE a1 : 1;
				BYTE a2 : 1;
				BYTE a3 : 1;
				BYTE : 2;
				BYTE a6 : 1;
				BYTE a7 : 1;
				BYTE a8 : 1;
				BYTE a9 : 1;
				BYTE : 6;
			};

			AVRCT_S* avrct;
			AVRC_AVRCC_S* avrc_avrcc;

			SUPPORTED_FEATURES_DATA_S(SHORT* a, int type) //: avrct((AVRCT_S*)a)
			{
				avrct = NULL;
				avrc_avrcc = NULL;

				if (type == 1)
					avrct = (AVRCT_S*)a;
				else
					avrc_avrcc = (AVRC_AVRCC_S*)a;

				//printf("FROM STRUCT --> %X\n", *a);
			};

			std::string getSupportedFeaturesString_AVRC_AVRCC()
			{
				std::string temp = "";

				if (avrc_avrcc->a0)
				{
					temp += "Category 1\n";
				}

				if (avrc_avrcc->a1)
				{
					temp += "Category 2\n";
				}

				if (avrc_avrcc->a2)
				{
					temp += "Category 3\n";
				}

				if (avrc_avrcc->a3)
				{
					temp += "Category 4\n";
				}

				if (avrc_avrcc->a6)
				{
					temp += "Supports browsing\n";
				}

				if (avrc_avrcc->a7)
				{
					temp += "Supports Cover Art GetImageProperties feature\n";
				}

				if (avrc_avrcc->a8)
				{
					temp += " Supports Cover Art GetImage feature\n";
				}

				if (avrc_avrcc->a9)
				{
					temp += "Supports Cover Art GetLinkedThumbnail feature\n";
				}

				return temp;
			}

			std::string getSupportedFeaturesString_AVRCT()
			{
				std::string temp = "";

				if (avrct->a0)
				{
					temp += "Category 1\n";
				}

				if (avrct->a1)
				{
					temp += "Category 2\n";
				}

				if (avrct->a2)
				{
					temp += "Category 3\n";
				}

				if (avrct->a3)
				{
					temp += "Category 4\n";
				}

				if (avrct->a4)
				{
					temp += "Player Application Settings\n";
				}

				if (avrct->a5)
				{
					temp += "Group Navigation\n";
				}

				if (avrct->a6)
				{
					temp += "Supports browsing\n";
				}

				if (avrct->a7)
				{
					temp += "Supports multiple media player applications\n";
				}

				if (avrct->a8)
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

				// TODO: premisli kako bi to naredil da se data pravilno izpise
				if(v.sfds->avrct != NULL)
					printf("%s\n", v.sfds->getSupportedFeaturesString_AVRCT().c_str());

				if (v.sfds->avrc_avrcc != NULL)
					printf("%s\n", v.sfds->getSupportedFeaturesString_AVRC_AVRCC().c_str());
			}

		} SUPPORTED_FEATURES, * PSUPPORTED_FEATURES;


		void parse_SUPPORTED_FEATURES_AVRCP(PSUPPORTED_FEATURES handle, SHORT current_used_service);

		template<class C>
		void parse_by_type_sub_function(const std::type_info& type, C handle, SHORT current_used_service)
		{
			const std::type_info& a10 = typeid(SUPPORTED_FEATURES_S*);
			
			// SupportedFeatures
			if (type == a10)
			{
				parse_SUPPORTED_FEATURES_AVRCP((PSUPPORTED_FEATURES) handle, current_used_service);
			}
		}
	};

};