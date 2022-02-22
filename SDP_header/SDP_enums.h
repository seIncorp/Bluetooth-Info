#pragma once

namespace SDP
{
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
	}

	namespace MAP
	{
		typedef enum
		{
			GoepL2capPsm = 0x0200,
			MASInstanceID = 0x0315,
			SupportedMessageTypes = 0x0316,
			MapSupportedFeatures = 0x0317

		} ATTRIBUTE_ID_MAP;
	}

	namespace PBAP
	{
		typedef enum
		{
			GoepL2capPsm = 0x0200,
			SupportedRepositories = 0x0314,
			PbapSupportedFeatures = 0x0317

		} ATTRIBUTE_ID_PBAP;
	}

	namespace OBEX
	{
		typedef enum
		{
			GoepL2capPsm = 0x0200,
			ServiceVersion = 0x0300,
			SupportedFormatsList = 0x0303

		} ATTRIBUTE_ID_OBEX;
	}

	namespace HFP
	{
		typedef enum
		{
			Network = 0x0301,
			SupportedFeatures = 0x0311

		} ATTRIBUTE_ID_HFP;
	}

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
	}

	namespace A2DP
	{
		typedef enum
		{
			SupportedFeatures = 0x0311

		} ATTRIBUTE_ID_DEVICE_A2DP;
	}

	namespace AVRCP
	{
		typedef enum
		{
			SupportedFeatures = 0x0311

		} ATTRIBUTE_ID_DEVICE_AVRCP;
	}

	namespace HSP
	{
		typedef enum
		{
			RemoteAudioVolumeControl = 0x0302

		} ATTRIBUTE_ID_DEVICE_HSP;
	}
}