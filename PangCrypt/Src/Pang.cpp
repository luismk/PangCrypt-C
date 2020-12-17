
//----------------- try import the methods now :D -----------------------------
// I already performed tests with hsreina and it worked, but due to a bad programming of mine, I couldn't solve the error
//but how about you solve this error ?
#include "Pang.h"
// Decrypt pangya client packets
DLL_EXPORT int pangya_client_decrypt(unsigned char* buffin, int size, unsigned char** buffout, int* buffoutSize, int key)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto decrypt = ClientCipher::Decrypt(packet, (int)key);

	auto packet_decrypt = new unsigned char[decrypt.size()];

	packet_decrypt = Utils::ConvertVectorToChar(decrypt);

	*buffout = (unsigned char*)malloc(decrypt.size());
	memmove(*buffout, packet_decrypt, decrypt.size());
	delete[](packet_decrypt);
	return 1;
}

// Encrypt Pangya client packets
DLL_EXPORT int pangya_client_encrypt(unsigned char* buffin, int size, unsigned char** buffout, int* buffoutSize, int key)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto encrypt = ClientCipher::Encrypt(packet, (int)key, 0);
	auto packet_encrypt = new unsigned char[encrypt.size()];

	packet_encrypt = Utils::ConvertVectorToChar(encrypt);
	*buffout = (unsigned char*)malloc(encrypt.size());
	memmove(*buffout, packet_encrypt, encrypt.size());
	return 1;
}

// Decrypt Pangya server packets
DLL_EXPORT int pangya_server_decrypt(unsigned char* buffin, int size, unsigned char** buffout, int* buffoutSize, int key)
{
	unsigned char* packet_decrypt;
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto decrypt = ServerCipher::Decrypt(packet, (int)key);
	packet_decrypt = new unsigned char[decrypt.size()];
	packet_decrypt = Utils::ConvertVectorToChar(decrypt);
	*buffoutSize = decrypt.size();
	*buffout = new unsigned char[*buffoutSize];
	memcpy(*buffout, &packet_decrypt[0], *buffoutSize);
	delete[](packet_decrypt);
	return 1;
}

// Encrypt Pangya server packets
DLL_EXPORT int pangya_server_encrypt(unsigned char* buffin, int size, unsigned char** buffout, int* buffoutSize, int key)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto encrypt = ServerCipher::Encrypt(packet, (int)key, 0);
	auto packet_encrypt = new unsigned char[encrypt.size()];
	packet_encrypt = Utils::ConvertVectorToChar(encrypt);
	*buffoutSize = encrypt.size();
	*buffout = (unsigned char*)malloc(encrypt.size());
	memmove(*buffout, packet_encrypt, encrypt.size());
	return 1;
}

DLL_EXPORT void pangya_free(char** buffout)
{
	delete[](*buffout);
	free(buffout);
}

// Not used for now but maybe one day
DLL_EXPORT UInt32 pangya_deserialize(UInt32 deserialize)
{
	return ClientCipher::Deserialize(deserialize);
}
