#pragma once
#include <windows.h>
#include "CryptoOracle.h"
typedef unsigned int uint;
/// <summary>
/// cipher used for decrypt and int32 encrypt
/// </summary>
class DeserializeCipher
{
public:
	static uint Decrypt(uint pangya_build_date);

	static uint Encrypt(uint pangya_build_date);
};

