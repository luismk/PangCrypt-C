#include "DeserializeCipher.h"
#include <exception>

UINT32 DeserializeCipher::Decrypt(UINT32 pangya_build_date)
{
	UINT32 result = pangya_build_date;
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

UINT32 DeserializeCipher::Encrypt(UINT32 pangya_build_date)
{

	UINT32 result = pangya_build_date;
	UINT8* pval = (UINT8*)&result;
	size_t i, index;
	for (i = 0, index = 0; i < 38; i++)
	{
		pval[index] ^= CryptoOracle::CryptTableDeserialize[i];
		index = (index == 3) ? 0 : ++index;
	}

	return result;
}
