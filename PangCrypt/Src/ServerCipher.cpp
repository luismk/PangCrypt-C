#include "ServerCipher.h"
vector<unsigned char> ServerCipher::Encrypt(vector<unsigned char> source, int key, unsigned char salt)
{
	if (key >= 0x10)
	{
		throw exception("key", ("Key too large ({0} >= 0x10)", key));
	}

	auto oracleIndex = (key << 8) + salt;
	auto compressedData = MiniLzo::Compress(source);
	auto buffer = vector<unsigned char>(compressedData.size() + 8);
	auto pLen = buffer.size() - 3;

	auto u = source.size();
	auto x = (u + u / 255) & 0xff;
	auto v = (u - x) / 255;
	auto y = (v + v / 255) & 0xff;
	auto w = (v - y) / 255;
	auto z = (w + w / 255) & 0xff;

	buffer[0] = salt;
	buffer[1] = static_cast<unsigned char>((pLen >> 0) & 0xFF);
	buffer[2] = static_cast<unsigned char>((pLen >> 8) & 0xFF);
	buffer[3] = static_cast<unsigned char>(CryptoOracle::CryptTable1[oracleIndex] ^ CryptoOracle::CryptTable2[oracleIndex]);
	buffer[5] = static_cast<unsigned char>(z);
	buffer[6] = static_cast<unsigned char>(y);
	buffer[7] = static_cast<unsigned char>(x);

	Utils::CopyTo(compressedData, 0, buffer, 8, compressedData.size());
	for (auto i = buffer.size() - 1; i >= 10; i--)
	{
		buffer[i] ^= buffer[i - 4];
	}

	buffer[7] ^= CryptoOracle::CryptTable2[oracleIndex];

	return buffer;
}

vector<unsigned char> ServerCipher::Decrypt(vector<unsigned char> source, int key)
{
	if (key >= 0x10)
	{
		throw exception("key", ("Key too large ({0} >= 0x10)", key));
	}

	if (source.size() < 5)
	{
		throw exception("Source", ("Packet too small ({0} < 5)", source.size()));
	}


	auto oracleByte = CryptoOracle::CryptTable2[(key << 8) + source[0]];
	auto buffer = source;

	buffer[7] ^= oracleByte;

	for (int i = 10; i < source.size(); i++)
	{
		buffer[i] ^= buffer[i - 4];
	}

	auto compressedData = vector<unsigned char>(source.size() - 8);
	Utils::CopyTo(buffer, 8, compressedData, 0, compressedData.size());
	return MiniLzo::Decompress(compressedData);
}