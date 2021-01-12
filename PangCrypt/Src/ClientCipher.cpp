#include "ClientCipher.h"
vector<unsigned char> ClientCipher::Decrypt(std::vector<unsigned char> source, int key)
{	
	if (key >= 32) throw "Key too large ({%s} >= 0x20)", key;

	if (source.size() < 5)
	{
		throw exception("Source", ("Packet too small ({0} < 5)", source.size()));
	}

	auto buffer = static_cast<std::vector<unsigned char>>(source);

	buffer[4] = CryptoOracle::CryptTable2[(key << 8) + source[0]];

	for (int i = 8; i < buffer.size(); i++)
	{
		buffer[i] ^= buffer[i - 4];
	}

	auto output = std::vector<unsigned char>(buffer.size() - 5);

	Utils::CopyTo(buffer, 5, output, 0, buffer.size() - 5);
	return output;
}

vector<unsigned char> ClientCipher::Encrypt(vector<unsigned char> source, int key, int salt)
{
	if (key >= 32) throw "Key too large ({%s} >= 0x20)", key;


	auto oracleIndex = (key << 8) + salt;
	
	int size = source.size();
	auto buffer = vector<unsigned char>(size + 5);

	auto pLen = buffer.size() - 4;
	buffer[0] = salt;
	buffer[1] = static_cast<unsigned char>((pLen >> 0) & 0xFF);
	buffer[2] = static_cast<unsigned char>((pLen >> 8) & 0xFF);
	buffer[4] = static_cast<unsigned char>(CryptoOracle::CryptTable1[oracleIndex]);

	Utils::CopyTo(source, 0, buffer, 5, size);
	size = buffer.size() - 1;
	for (int i = size; i >= 8; i--) buffer[i] ^= buffer[i - 4];

	buffer[4] ^= CryptoOracle::CryptTable1[oracleIndex];
	return buffer;
}


