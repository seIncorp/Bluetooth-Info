#pragma once
namespace SDP
{
	namespace A2DP
	{
		struct SUPPORTED_FEATURES_DATA_S
		{
			struct SR_S
			{
				BYTE a0 : 1;
				BYTE a1 : 1;
				BYTE a2 : 1;
				BYTE a3 : 1;
				BYTE : 4;
				BYTE : 8;
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
					temp += "Player\n";
				}

				if (repo->a1)
				{
					temp += "Microphone\n";
				}

				if (repo->a2)
				{
					temp += "Tuner\n";
				}

				if (repo->a3)
				{
					temp += "Mixer\n";
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

		// TODO: naredi se za Audio Sink 

		void parse_SUPPORTED_FEATURES_A2DP(PSUPPORTED_FEATURES handle);

		template<class C>
		void parse_by_type_sub_function(const std::type_info& type, C handle, SHORT current_used_service)
		{
			const std::type_info& a10 = typeid(SUPPORTED_FEATURES_S*);


			// SupportedFeatures
			if (type == a10)
			{
				parse_SUPPORTED_FEATURES_A2DP((PSUPPORTED_FEATURES)handle);
			}
		}
	};
};