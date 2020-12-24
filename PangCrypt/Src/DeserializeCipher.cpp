#include "DeserializeCipher.h"
#include <exception>

//code sent by: Hsreina
uint DeserializeCipher::Decrypt(uint pangya_build_date)
{
	uint result = pangya_build_date;
	UINT8* pval = (UINT8*)&result;

	for (unsigned char i = 0; i < 38; i++)
	{
		pval[i % 4] ^= CryptoOracle::CryptTableDeserialize[i];
	}
	if (result != pangya_build_date)
	{
		return result;
	}
	else
	{
		throw exception("Falied To Deserialize Data !");
	}
}

//code sent by: Acrisio SuperSS Dev
uint DeserializeCipher::Encrypt(uint pangya_build_date)
{

	uint result = pangya_build_date;
	UINT8* pval = (UINT8*)&result;
	size_t i, index;
	for (i = 0, index = 0; i < 38; i++)
	{
		pval[index] ^= CryptoOracle::CryptTableDeserialize[i];
		index = (index == 3) ? 0 : ++index;
	}

	return result;
}
