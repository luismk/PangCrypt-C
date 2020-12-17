#pragma once
#include "CryptoOracle.h"
#include "Utils.h"
#include "MiniLzo.h"
/// <summary>
///     Cipher used for packets sent by the server. PangYa clients would
///     decrypt incoming packets using this cipher and PangYa servers would
///     encrypt outgoing packets using this cipher.
/// </summary>
class ServerCipher
{
	/// <summary>
	///     Decrypts data from server-side packets (sent from servers to clients.)
	/// </summary>
	/// <param name="source">The encrypted packet data.</param>
	/// <param name="key">Key to decrypt with.</param>
	/// <returns>The decrypted packet data.</returns>
	/// <exception cref="ArgumentOutOfRangeException">
	///     Thrown if the key is invalid or the packet data is too short.
	/// </exception>
public:
	static vector<unsigned char> Decrypt(vector<unsigned char> source, int key);

	/// <summary>
	///     Encrypts data for server-side packets (sent from servers to clients.)
	/// </summary>
	/// <param name="source">The decrypted packet data.</param>
	/// <param name="key">Key to encrypt with.</param>
	/// <param name="salt">Random salt value to encrypt with.</param>
	/// <returns>The encrypted packet data.</returns>
	/// <exception cref="ArgumentOutOfRangeException">
	///     Thrown if an invalid key is specified.
	/// </exception>
	static vector<unsigned char> Encrypt(vector<unsigned char> source, int key, int salt = 0);
};