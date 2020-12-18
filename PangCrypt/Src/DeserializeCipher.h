#pragma once
#include <windows.h>
#include "CryptoOracle.h"
/// <summary>
/// cipher used for decrypt and int32 encrypt
/// </summary>
class DeserializeCipher
{
public:
	static UINT32 Decrypt(UINT32 pangya_build_date);

	static UINT32 Encrypt(UINT32 pangya_build_date);
};

