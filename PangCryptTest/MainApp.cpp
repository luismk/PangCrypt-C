#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include "../PangCrypt/Src/Cryptor.h"
int main(int argc, char* argv[])
{
	try
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       time[50];
		localtime_s(&tstruct, &now);
		strftime(time, sizeof(time), "%d-%m-%Y %X", &tstruct);

		system("title PangCryptTest");

		cout << "Start PangCrypt Test: " << time << endl;
		cout << "" << "\n" << endl;
		
		for (int i = 1; i < 16; i++)
		{
			vector<unsigned char> test = { static_cast<unsigned char>(i), 0x00, 0x06, 0x00, 0x6C, 0x75, 0x69, 0x73, 0x6D, 0x6B, static_cast<unsigned char>(i), static_cast<unsigned char>(rand()) };
			
			auto buffin = Utils::ConvertVectorToChar(test);
			unsigned char* encrypt;
			unsigned char* decrypt;
			unsigned char* result;
			int CompressionSize;
			int DecompressionSize;
			pangya_server_encrypt(buffin, (int)test.size(), i, 0, encrypt, CompressionSize);
			Utils::PrintLog(4, (unsigned char*)encrypt, i, CompressionSize);
			decrypt = (unsigned char*)encrypt;
			pangya_server_decrypt(decrypt, CompressionSize, i, result, DecompressionSize);
			Utils::PrintLog(3, result, i, DecompressionSize);
		}
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	system("pause");
	return 0;
}
