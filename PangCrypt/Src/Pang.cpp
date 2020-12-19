#include <Windows.h>
#include <stdlib.h>
#include "ClientCipher.h"
#include "ServerCipher.h"
#include "DeserializeCipher.h"
#define DLLEXPORT EXTERN_C __declspec(dllexport)
typedef unsigned int UInt32;

//----------------- FINISH WORK 18-12-2020 16:00:00 by LUISMK -----------------------------
//this library is a version created in C++ by LUISMK
//objective of this was to increase my learning as a programmer
//this is a remake of PangCrypt-Csharp: https://github.com/pangyatools/PangCrypt
//create by John Chadwick: https://github.com/jchv and Andreas Nedbal: https://github.com/pixeldesu
//group discord for pangYa: https://discord.gg/HwDTssf
//to work with the reina server, you need to change part of the reina src code
//crypt will only go up to a maximum of 15 keys

// Decrypt pangya client packets
DLLEXPORT int pangya_client_decrypt(unsigned char *buffin, int size, unsigned char **buffout, int *buffoutSize, unsigned char key)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto decrypt = ClientCipher::Decrypt(packet, (int)key);
	*buffout = new unsigned char[decrypt.size()];
	*buffout = Utils::ConvertVectorToChar(decrypt);
	*buffoutSize = decrypt.size();
	return 1;
}

// Encrypt Pangya client packets, not used: packetid
DLLEXPORT int pangya_client_encrypt(unsigned char *buffin, int size, unsigned char **buffout, int *buffoutSize, unsigned char key, char packetid)
{
	auto len = size;
	auto packet = vector<unsigned char>(buffin, buffin + len);
	auto encrypt = ClientCipher::Encrypt(packet, (int)key, 0);
	*buffout = new unsigned char[encrypt.size()];
	*buffout = Utils::ConvertVectorToChar(encrypt);
	*buffoutSize = encrypt.size();
	return 1;
}

// Decrypt Pangya server packets
DLLEXPORT int pangya_server_decrypt(unsigned char *buffin, int size, unsigned char **buffout, int *buffoutSize, unsigned char key)
{
	unsigned char* packet_decrypt;
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto decrypt = ServerCipher::Decrypt(packet, (int)key);
	*buffout = new unsigned char[decrypt.size()];
	*buffout = Utils::ConvertVectorToChar(decrypt);
	*buffoutSize = decrypt.size();
	return 1;
}

// Encrypt Pangya server packets
DLLEXPORT int pangya_server_encrypt(unsigned char *buffin, int size, unsigned char **buffout, int *buffoutSize, unsigned char key)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	auto encrypt = ServerCipher::Encrypt(packet, (int)key, 0);
	*buffout = new unsigned char[encrypt.size()];
	*buffout = Utils::ConvertVectorToChar(encrypt);
	*buffoutSize = encrypt.size();
	return 1;
}

DLLEXPORT void pangya_free(char** buffout)
{
	free(*buffout);
}


DLLEXPORT UInt32 pangya_deserialize(UInt32 deserialize)
{
	return DeserializeCipher::Decrypt(deserialize);
}


DLLEXPORT UInt32 pangya_encrypt_deserialize(UInt32 deserialize)
{
	return DeserializeCipher::Encrypt(deserialize);
}
