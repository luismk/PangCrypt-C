#pragma once
#include "MiniLzo.h"
class Pang
{
private:
	static const vector<unsigned char> PublicKeyTable;
	static const vector<unsigned char> PrivateKeyTable;
	static const vector<unsigned char> PublicTableDeserialize;

	static void Encrypt_Packet(vector<unsigned char>& source, unsigned char Salt, int ParseKey, bool Compress =false);

	static void Decrypt_Packet(vector<unsigned char>& source, int ParseKey, bool Decompress = false);
public:
	static void _pangya_client_decrypt(vector<unsigned char>& buffin, unsigned int key);

	static void _pangya_client_encrypt(vector<unsigned char>& buffin, unsigned int key, unsigned int salt);

	static void _pangya_server_decrypt(vector<unsigned char>& buffin, unsigned int key);

	static void _pangya_server_encrypt(vector<unsigned char>& buffin, unsigned int key, unsigned int salt);

	static void _pangya_deserialize_encrypt(unsigned int& source);

	static void _pangya_deserialize_decrypt(unsigned int& source);
};