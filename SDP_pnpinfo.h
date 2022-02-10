#pragma once

namespace SDP
{
	namespace PNPINFO	// PnPInformation
	{
		typedef enum
		{
			SpecificationID = 0x0200,
			VendorID = 0x0201,
			ProductID = 0x0202,
			Version = 0x0203,
			PrimaryRecord = 0x0204,
			VendorIDSource = 0x0205,
			ClientExecutableURL = 0x000B,
			DocumentationURL = 0x000A

		} ATTRIBUTE_ID_DEVICE_SDP;

		typedef struct INFO_S : DEFAULT_OBJECT
		{
			SHORT SpecificationID;
			SHORT VendorID;
			SHORT ProductID;
			SHORT Version;
			BOOL PrimaryRecord;
			SHORT VendorIDSource;

			template<class A>
			void setIDdata(SHORT id, A data)
			{
				switch (id)
				{
				case ATTRIBUTE_ID_DEVICE_SDP::SpecificationID:
					this->SpecificationID = data;
					break;

				case ATTRIBUTE_ID_DEVICE_SDP::VendorID:
					this->VendorID = data;
					break;

				case ATTRIBUTE_ID_DEVICE_SDP::ProductID:
					this->ProductID = data;
					break;

				case ATTRIBUTE_ID_DEVICE_SDP::Version:
					this->Version = data;
					break;

				case ATTRIBUTE_ID_DEVICE_SDP::PrimaryRecord:
					this->PrimaryRecord = data;
					break;

				case ATTRIBUTE_ID_DEVICE_SDP::VendorIDSource:
					this->VendorIDSource = data;
					break;
				}
			}


			template<class T>
			void print(T v)
			{
				printATTR_ELEMENT();

				printVALUE_ELEMENT(v);

				printf("Specification ID: 0x%04X\n", this->SpecificationID);
				printf("Vendor ID: 0x%04X\n", this->VendorID);
				printf("Product ID: 0x%04X\n", this->ProductID);
				printf("Version: 0x%04X\n", this->Version);
				printf("Primary Record: 0x%02X\n", this->PrimaryRecord);
				printf("Vendor ID Source: 0x%04X\n", this->VendorIDSource);
			}

		} INFO, * PINFO;


		int getAndParse_SPECIFICATION_ID_PNPINFO(ULONG recordHandle, HANDLE_SDP_TYPE aa);

	};
};