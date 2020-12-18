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

unsigned char* Utils::ConvertVectorToChar(vector<unsigned char> source)
{
	auto buffer = new unsigned char[source.size()];
	copy(source.begin(), source.end(), buffer);
	return buffer;
}

bool Utils::Resize(vector<unsigned char>& destinationArray, int length)
{
	auto source = vector<unsigned char>(length);
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


string Utils::ShowPacketInHex(vector<unsigned char> packet_buffer)
{
	char const hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	string returndata = "";
	for (int i = 0; i < packet_buffer.size(); ++i)
	{
		const char ch = packet_buffer[i];
		returndata += " 0x";
		returndata.append(&hex[(ch & 0xF0) >> 4], 1);
		returndata.append(&hex[ch & 0xF], 1);
	}
	return returndata;
}

