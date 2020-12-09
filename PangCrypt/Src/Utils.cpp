#include "Utils.h"

bool Utils::CopyTo(vector<unsigned char> sourceArray, int sourceIndex, vector<unsigned char>& destinationArray, int destinationIndex, int length)
{
	for (int i = 0; i < length; i++)
	{
		destinationArray[destinationIndex] = sourceArray[sourceIndex];
		sourceIndex++;
		destinationIndex++;
	}
	return 1;
}

bool Utils::Resize(vector<unsigned char>& destinationArray, int length)
{
	auto source = vector<unsigned char>(length);
	try
	{
		int i;
		int realsize = destinationArray.size() - 1;
		for (i = 0; i <= realsize; i++)
		{
			if ((length - 1) == i)
			{
				source[i] = destinationArray[i];
				break;
			}
			source[i] = destinationArray[i];
		}
		destinationArray = source;
		return 1;
	}
	catch (const std::exception&)
	{
			
	}
}

string Utils::ShowPacketInHex(unsigned char* packet_buffer, int size)
{
	char const hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	string returndata = "";
	for (int i = 0; i < size; ++i)
	{
		const char ch = packet_buffer[i];
		returndata += " 0x";
		returndata.append(&hex[(ch & 0xF0) >> 4], 1);
		returndata.append(&hex[ch & 0xF], 1);
	}
	return returndata;
}

bool Utils::CopyString(unsigned char* sourceArray, int sourceIndex, unsigned char*& destinationArray, int destinationIndex, int length)
{
	for (int i = 0; i < length; i++)
	{
		destinationArray[sourceIndex] = sourceArray[sourceIndex];
		sourceIndex++;
		destinationIndex++;
	}
	return 1;
}
