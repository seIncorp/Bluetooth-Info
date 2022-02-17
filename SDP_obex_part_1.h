#pragma once
namespace SDP
{

	namespace OBEX
	{

		std::string getSupportedFormatsString(BYTE data[], int size);

		typedef struct SERVICE_VERSION_S : DEFAULT_OBJECT
		{

		} SERVICE_VERSION, * PSERVICE_VERSION;

		typedef struct SUPPORTED_FORMATS_S : DEFAULT_OBJECT
		{
			struct VV : VALUE
			{
				int num_of_formats;
				BYTE* formats;

			} VALUE;

			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Number of supported formats: %d\n", v.num_of_formats);

				printf("Supported formats: \n");
				for (int aa = 0; aa < v.num_of_formats; aa++)
					printf("0x%02X ", v.formats[aa]);
				printf("\n");

				printf("Formats: \n%s\n", getSupportedFormatsString(v.formats, v.num_of_formats).c_str());
			}

		} SUPPORTED_FORMATS, * PSUPPORTED_FORMATS;

		// GoepL2CapPsm use from MAP

		void parse_SERVICE_VERSION_OBEX(PSERVICE_VERSION handle);
		void parse_SUPPORTED_FORMATS_LIST_OBEX(PSUPPORTED_FORMATS handle);


		template<class C>
		void parse_by_type_sub_function(const std::type_info& type, C handle, SHORT current_used_service)
		{
			const std::type_info& a10 = typeid(SERVICE_VERSION_S*);
			const std::type_info& a11 = typeid(SUPPORTED_FORMATS_S*);
			const std::type_info& a12 = typeid(SDP::MAP::GOEPL2CAPPSM_S*);
			

			// ServiceVersion
			if (type == a10)
			{
				parse_SERVICE_VERSION_OBEX((PSERVICE_VERSION) handle);
			}

			// SupportedFormatsList
			if (type == a11)
			{
				parse_SUPPORTED_FORMATS_LIST_OBEX((PSUPPORTED_FORMATS) handle);
			}

			// GoepL2capPsm
			if (type == a12)
			{
				SDP::MAP::parse_GOEPL2CAPPSM_MAP((SDP::MAP::PGOEPL2CAPPSM) handle);
			}
		}
	};
};