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

string Utils::PacketInHex(unsigned char* packet_buffer, int size)
{
	char const hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	string returndata = "";
	for (int i = 0; i < size; ++i)
	{
		const char ch = packet_buffer[i];
		returndata.append(&hex[(ch & 0xF0) >> 4], 1);
		returndata.append(&hex[ch & 0xF], 1);
	}
	return returndata;
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


string Utils::ShowPacketInHex(vector<unsigned char> packet_buffer, int size)
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

string Utils::GetDateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       time[50];
	localtime_s(&tstruct, &now);
	strftime(time, sizeof(time), "%d-%m-%Y %X", &tstruct);
	return time;
}

string Utils::GetTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       time[20];
	localtime_s(&tstruct, &now);
	strftime(time, sizeof(time), "%X", &tstruct);
	return time;
}

void Utils::ConsolePrint(const char* _Format)
{
	string Format = _Format;
	puts(_Format);
}

void Utils::PrintLog(int typelog, unsigned char* packet, unsigned char key, int size)
{
	string InputLog = "";
	switch (typelog)
	{
	case 1:
	{
		InputLog = "************ pangya_client_decrypt ************\n";
	}
		break;
	case 2:
	{
		InputLog = "************ pangya_client_encrypt ************\n";		
	}
	break;
	case 3:
	{
		InputLog = "************ pangya_server_decrypt ************\n";		
	}
	break;
	case 4:
	{
		InputLog = "************ pangya_server_encrypt ************\n";		
	}
	break;
	default:
			break;
	}
	InputLog += "New Incoming Call at :" + GetDateTime() + "\n";
	InputLog += "******************* Input *********************\n";
	auto size2 = to_string(size);
	InputLog += "Size : " + size2 + "\n";
	InputLog += "Key (HEX) : " + ShowPacketInHex(&key, 1) + "\n";
	InputLog += hex2ascii(PacketInHex(packet, size)) + "\n";
	InputLog += "Data (HEX) :" + ShowPacketInHex(packet, size) + "\n";
	InputLog += "PacketID (HEX) :" + ShowPacketInHex(packet, 2) + "\n";
	InputLog += "***********************************************\n";
	ConsolePrint(InputLog.c_str());
}


unsigned char Utils::hexval(unsigned char c)
{
	if ('0' <= c && c <= '9')
		return c - '0';
	else if ('a' <= c && c <= 'f')
		return c - 'a' + 10;
	else if ('A' <= c && c <= 'F')
		return c - 'A' + 10;

	return '0';
}

string Utils::hex2ascii(const string& in)
{
	string out;
	out = "Data (STRING) :";
	for (string::const_iterator p = in.begin(); p != in.end(); p++)
	{
		unsigned char c = hexval(*p);
		p++;
		if (p == in.end()) break;
		c = (c << 4) + hexval(*p);

		if (c == NULL)
			c = ' ';

		out += std::string(1, c);
	}

	return out;
}
