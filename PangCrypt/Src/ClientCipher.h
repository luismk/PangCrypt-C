#pragma once
#include "Utils.h"
#include "CryptoOracle.h"
/// <summary>
///     Cipher used for packets sent by the client. PangYa clients would
///     encrypt outgoing packets using this cipher and PangYa servers would
///     decrypt incoming packets using this cipher.
/// </summary>
class ClientCipher
{
	
public:	
	/// <summary>
	///     Decrypts data from client-side packets (sent from clients to servers.)
	/// </summary>
	/// <param name="source">The encrypted packet data.</param>
	/// <param name="key">Key to decrypt with.</param>
	/// <returns>The decrypted packet data.</returns>
	/// <exception cref="ArgumentOutOfRangeException">
	///     Thrown if the key is invalid or the packet data is too short.
	/// </exception>
	static vector<unsigned char> Decrypt(vector<unsigned char> source, int key);
	/// <summary>
	///     Encrypts data for client-side packets (sent from clients to servers.)
	/// </summary>
	/// <param name="source">The decrypted packet data.</param>
	/// <param name="key">Key to encrypt with.</param>
	/// <param name="salt">Random salt value to encrypt with.</param>
	/// <returns>The encrypted packet data.</returns>
	/// <exception cref="ArgumentOutOfRangeException">
	///     Thrown if an invalid key is specified.
	/// </exception>

	static vector<unsigned char> Encrypt(vector<unsigned char> source, int key, int salt =0);
};