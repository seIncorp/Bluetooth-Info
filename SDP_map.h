#pragma once

namespace SDP
{

	namespace MAP
	{
		typedef enum
		{
			GoepL2capPsm = 0x0200,
			MASInstanceID = 0x0315,
			SupportedMessageTypes = 0x0316,
			MapSupportedFeatures = 0x0317

		} ATTRIBUTE_ID_MAP;

		struct SUPPORTED_FEATURES_MESSAGES_S
		{
			struct SMT_S
			{
				BYTE a0 : 1;
				BYTE a1 : 1;
				BYTE a2 : 1;
				BYTE a3 : 1;
				BYTE a4 : 1;
				BYTE : 3;
			};

			SMT_S* ttt;


			struct SF_S
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
				BYTE a9 : 1;
				BYTE a10 : 1;
				BYTE a11 : 1;
				BYTE a12 : 1;
				BYTE a13 : 1;
				BYTE a14 : 1;
				BYTE a15 : 1;
				BYTE a16 : 1;
				BYTE a17 : 1;
				BYTE a18 : 1;
				BYTE a19 : 1;
				BYTE a20 : 1;
				BYTE a21 : 1;
				BYTE a22 : 1;
				BYTE : 6;
				BYTE : 3;
			};

			SF_S* aaa;

			SUPPORTED_FEATURES_MESSAGES_S(BYTE* a) : ttt((SMT_S*)a)
			{
				//printf("FROM STRUCT --> %X\n", *a);
			};

			SUPPORTED_FEATURES_MESSAGES_S(DWORD* a) : aaa((SF_S*)a)
			{
				//printf("FROM STRUCT --> %X\n", *a);
			};


		};

		std::string getMessageTypesString(SUPPORTED_FEATURES_MESSAGES_S* sfm);
		std::string getSupportedFeaturesString(SUPPORTED_FEATURES_MESSAGES_S* sfm);


		typedef struct GOEPL2CAPPSM_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				SHORT GoepL2CapPsm_value;

			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("GoepL2CapPsm value: 0x%04X\n", v.GoepL2CapPsm_value);
			}


		} GOEPL2CAPPSM, * PGOEPL2CAPPSM;

		typedef struct SUPPORTED_MESSAGE_TYPES_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				SUPPORTED_FEATURES_MESSAGES_S* sfm;

			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Message types: \n%s\n", getMessageTypesString(VALUE.sfm).c_str());
			}


		} SUPPORTED_MESSAGE_TYPES, * PSUPPORTED_MESSAGE_TYPES;

		typedef struct MAS_INSTANCE_ID_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				BYTE instance_ID;

			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("MAS instance ID: 0x%02X\n", v.instance_ID);
			}

		} MAS_INSTANCE_ID, * PMAS_INSTANCE_ID;

		typedef struct MAP_SUPPORTED_FEATURES_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				SUPPORTED_FEATURES_MESSAGES_S* sfm;

			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Features: \n%s\n", getSupportedFeaturesString(v.sfm).c_str());
			}

		} MAP_SUPPORTED_FEATURES, * PMAP_SUPPORTED_FEATURES;


		int getAndParse_GOEPL2CAPPSM_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_SUPPORTED_MESSAGE_TYPES_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_MAS_INSTANCE_ID_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
		int getAndParse_MAP_SUPPORTED_FEATURES_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);

		int getAllFeatures_data_MAP(ULONG recordHandle, HANDLE_SDP_TYPE aa);
	};

};