#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
using namespace std;
class Utils
{
public:
	static bool CopyString(unsigned char* sourceArray, int sourceIndex, unsigned char*& destinationArray, int destinationIndex, int length);

	static bool CopyTo(vector<unsigned char> sourceArray, int sourceIndex, vector<unsigned char>& destinationArray, int destinationIndex, int length);
	
	static unsigned char* ConvertVectorToChar(vector<unsigned char>& source);
	/// <summary>
	/// Create new String
	/// </summary>
	/// <param name="destinationArray"></param>
	/// <param name="length"></param>
	/// <returns></returns>
	static bool Resize(vector<unsigned char>& destinationArray, int length);

	static string ShowPacketInHex(unsigned char* packet_buffer, int size);

	static string ShowPacketInHex(vector<unsigned char> packet_buffer);

	template<typename T>
	static T IfCompare(bool expression, T trueValue, T falseValue)
	{
		if (expression)
		{
			return trueValue;
		}
		else
		{
			return falseValue;
		}
	}
};
