#pragma once
#ifndef CRYPTOR_H
#define CRYPTOR_H


//----------------- UPDATE 09-01-2021 10:00:00 by LUISMK -----------------------------
//this library is a version created in C++ by LUISMK
//objective of this was to increase my learning as a programmer
//this is a remake of PangCrypt-Csharp: https://github.com/pangyatools/PangCrypt
//create by John Chadwick: https://github.com/jchv and Andreas Nedbal: https://github.com/pixeldesu
//group discord for pangYa: https://discord.gg/HwDTssf

#include <Windows.h>
#include <stdio.h>
#include "Pang.h"
#define DLLEXPORT EXTERN_C __declspec(dllexport)
typedef unsigned int uint;

#pragma region Simplication 
void pangya_client_decrypt(unsigned char* buffin, int size, unsigned int key, unsigned char*& dataout, int& newSize)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	Pang::_pangya_client_decrypt(packet, (int)key);
	dataout = new unsigned char[packet.size()];
	dataout = Utils::ConvertVectorToChar(packet);
	newSize = packet.size();
}

// Encrypt Pangya client packets
void pangya_client_encrypt(unsigned char* buffin, int size, unsigned int key, int salt, unsigned char*& dataout, int& newSize)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	Pang::_pangya_client_encrypt(packet, (int)key, salt);
	dataout = new unsigned char[packet.size()];
	dataout = Utils::ConvertVectorToChar(packet);
	newSize = packet.size();
}

// Decrypt Pangya server packets
void pangya_server_decrypt(unsigned char* buffin, int size, unsigned int key, unsigned char*& dataout, int& newSize)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	Pang::_pangya_server_decrypt(packet, (int)key);
	dataout = new unsigned char[packet.size()];
	dataout = Utils::ConvertVectorToChar(packet);
	newSize = packet.size();
}

// Encrypt Pangya server packets
void pangya_server_encrypt(unsigned char* buffin, int size, unsigned int key, int salt, unsigned char*& dataout, int& newSize)
{
	auto packet = vector<unsigned char>(buffin, buffin + size);
	Pang::_pangya_server_encrypt(packet, (int)key, salt);
	dataout = new unsigned char[packet.size()];
	dataout = Utils::ConvertVectorToChar(packet);
	newSize = packet.size();
}

void pangya_deserialize(uint& deserialize)
{
	Pang::_pangya_deserialize_decrypt(deserialize);
}
#pragma endregion

#endif