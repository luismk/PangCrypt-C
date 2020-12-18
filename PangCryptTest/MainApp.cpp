#include <stdio.h>
#include <stdlib.h>
#include <ClientCipher.cpp>
#include <ServerCipher.cpp>
#include <DeserializeCipher.cpp>
#include <iostream>
#include <chrono>
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

		auto test = DeserializeCipher::Encrypt(2014020600);
		if (test != 626763146)
		{
			throw exception("Falied To Deserialize Encrypted Data");
		}
		 test = DeserializeCipher::Decrypt(test);
		if (test != 2014020600)
		{
			throw exception("Falied To Deserialize Encrypted Data");
		}
		for (int i = 1; i < 16; i++)
		{
			vector<unsigned char> test = { static_cast<unsigned char>(i), 0x00, 0x06, 0x00, 0x6C, 0x75, 0x69, 0x73, 0x6D, 0x6B, static_cast<unsigned char>(i), static_cast<unsigned char>(rand()) };
			
			auto client_encrypted = ClientCipher::Encrypt(test, i, 0);

			auto client_decrypted = ClientCipher::Decrypt(client_encrypted, i);
			if (client_decrypted != test)
			{
				throw exception("Falied To Client Decrypt Data");
			}
			auto server_encrypted = ServerCipher::Encrypt(test, i, i * 2);

			auto server_decrypted = ServerCipher::Decrypt(server_encrypted, i);
			if (server_decrypted != test)
			{
				throw exception("Falied To Client Server Data");
			}
			auto result0 = Utils::ShowPacketInHex(client_encrypted);

			auto result1 = Utils::ShowPacketInHex(client_decrypted);

			auto result2 = Utils::ShowPacketInHex(server_encrypted);

			auto result3 = Utils::ShowPacketInHex(server_decrypted);

			cout << "--------------------------LOG--------------------------" << endl;
			cout << "NEW_KEY=> " << i << endl;
			cout << "ClientEncrypt: " << " Encrypt_Test=> " << result0 << endl;
			cout << "" << "\n" << endl;
			cout << "ClientDecrypt: " << " Decrypt_Test=> " << result1 << endl;
			cout << "" << "\n" << endl;
			cout << "" << "\n" << endl;
			cout << "ServerEncrypt: " << " Encrypt_Test=> " << result2 << endl;
			cout << "" << "\n" << endl;
			cout << "ServerDecrypt: " << " Decrypt_Test=> " << result3 << endl;		
			cout << "--------------------------END--------------------------" << endl;
			cout << "" << "\n" << endl;
		}
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	system("pause");
	return 0;
}
