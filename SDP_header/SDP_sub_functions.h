#pragma once

namespace SDP
{
	namespace SUB_FUNCTIONS
	{
		std::string getElementTypeString(BYTE type);
		int getElementSize(BYTE size, int* add_bits);
		std::string getProtocolTypeString(SHORT type);
		std::string getNetworkPacketTypeString(SHORT type);

	};

}