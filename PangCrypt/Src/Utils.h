#pragma once
#include <vector>
#include <string>
using namespace std;
class Utils
{
public:
	/// <summary>
	/// copy old vector string and put it in a new one
	/// </summary>
	/// <param name="sourceArray:"> object to be copied</param>
	/// <param name="sourceIndex:"> start where object will be copied</param>
	/// <param name="destinationArray:"> target object</param>
	/// <param name="destinationIndex:"> start of target object</param>
	/// <param name="length:"> new size</param>
	/// <returns></returns>
	static bool CopyTo(vector<unsigned char> sourceArray, int sourceIndex, vector<unsigned char>& destinationArray, int destinationIndex, int length);
	
	/// <summary>
	///	copy a vector string and convert to unsigned char
	/// </summary>
	/// <param name="source:">vector string</param>
	/// <returns>unsigned char</returns>
	static unsigned char* ConvertVectorToChar(vector<unsigned char> source);

	/// <summary>
	/// Create new String
	/// </summary>
	/// <param name="destinationArray:">returns data with new size</param>
	/// <param name="length:">new size</param>
	/// <returns>true = sucess</returns>
	static bool Resize(vector<unsigned char>& destinationArray, int length);

	static string ShowPacketInHex(unsigned char* packet_buffer, int size);

	static string ShowPacketInHex(vector<unsigned char> packet_buffer);
};
