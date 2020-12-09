#pragma once
#include <vector>
#include <string>
using namespace std;
class Utils
{
public:
	static bool CopyString(unsigned char* sourceArray, int sourceIndex, unsigned char*& destinationArray, int destinationIndex, int length);

	static bool CopyTo(vector<unsigned char> sourceArray, int sourceIndex, vector<unsigned char>& destinationArray, int destinationIndex, int length);
	/// <summary>
	/// Create new String
	/// </summary>
	/// <param name="destinationArray"></param>
	/// <param name="length"></param>
	/// <returns></returns>
	static bool Resize(vector<unsigned char>& destinationArray, int length);

	static string ShowPacketInHex(unsigned char* packet_buffer, int size);
};
