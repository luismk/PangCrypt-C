#include <stdio.h>
#include <stdlib.h>
#include <Src\ClientCipher.cpp>
#include <Src\ServerCipher.cpp>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	//..luismk.......ñf.5C91472.824.00“…J%.....9D390AF
	vector<unsigned char> testencrypt = { 0x02, 0x00, 0x06, 0x00, 0x6C, 0x75, 0x69, 0x73, 0x6D, 0x6B, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x96, 0x66, 0x07, 0x00, 0x35, 0x43, 0x39, 0x31, 0x34, 0x37, 0x32, 0x06, 0x00, 0x38, 0x32, 0x34, 0x2E, 0x30, 0x30, 0xD2, 0xC9, 0x4A, 0x25, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x39, 0x44, 0x33, 0x39, 0x30, 0x41, 0x46 };

	auto client_encrypted = ClientCipher::Encrypt(testencrypt, 1, 0);

	auto client_decrypted = ClientCipher::Decrypt(client_encrypted, 1);

	auto server_encrypted = ServerCipher::Encrypt(testencrypt, 2, 0);

	auto server_decrypted = ServerCipher::Decrypt(server_encrypted, 2);

	auto result0 = Utils::ShowPacketInHex(client_encrypted.size() ? (unsigned char*)&client_encrypted[0] : 0, (int)client_encrypted.size());
	
	auto result1 = Utils::ShowPacketInHex(client_decrypted.size() ? (unsigned char*)&client_decrypted[0] : 0, (int)client_decrypted.size());

	auto result3 = Utils::ShowPacketInHex(server_encrypted.size() ? (unsigned char*)&server_encrypted[0] : 0, (int)server_encrypted.size());

	auto result4 = Utils::ShowPacketInHex(server_decrypted.size() ? (unsigned char*)&server_decrypted[0] : 0, (int)server_decrypted.size());

	cout << "ClientEncrypt::Encrypt_Test:" << result0 << endl;
	cout << "" << "\n" << endl;
	cout << "ClientEncrypt::Decrypt_Test:" << result1 << endl;
	cout << "" << "\n" << endl;
	cout << "" << "\n" << endl;
	cout << "ServerEncrypt::Encrypt_Test:" << result3 << endl;
	cout << "" << "\n" << endl;
	cout << "ServerEncrypt::Decrypt_Test:" << result4 << endl;
	cout << "" << "\n" << endl;
	//Test_Crypt_Server();*/
	system("pause");
	return 0;
}
