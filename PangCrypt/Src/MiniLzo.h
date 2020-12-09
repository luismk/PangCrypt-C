#pragma once
//#region License

/* Based on the MiniLZO library by Markus Oberhumer and some code
   from a port to C# by Frank Razenberg.

   Copyright (C) 1996-2019 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   The LZO library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The LZO library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the LZO library; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
   http://www.oberhumer.com/opensource/lzo/
 */

 //#endregion
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

class MiniLzo final
{

	//		#region Helpers

private:
	static unsigned int ReadU32(vector<unsigned char>& arr, unsigned int i);

	static unsigned int ReadU16(vector<unsigned char>& arr, unsigned int i);

	static unsigned int LzoBitOpsCtz32(signed int v);

	static unsigned int NearestPowerOfTwo(unsigned int n);

	static void AllocSpace(vector<unsigned char>& array, unsigned int minLength);

	static void EnsureSpace(unsigned int need, vector<unsigned char>& array, unsigned int pos);

	//		#endregion

	//		#region Compression

	static unsigned int Lzo1X1CompressCore(vector<unsigned char>& in, unsigned int inIndex, unsigned int inLen, vector<unsigned char>& out, unsigned int outIndex, unsigned int& outLen, unsigned int ti, vector<unsigned short>& dict);

	static void Lzo1X1Compress(vector<unsigned char>& in, unsigned int inLen, vector<unsigned char>& out, unsigned int& outLen, vector<unsigned short>& dict);

	//		#endregion

	//		#region Decompression

	static vector<unsigned char> Lzo1XDecompress(vector<unsigned char> in);

	//		#endregion Decompression

	//		#region API

public:
	static vector<unsigned char> Decompress(vector<unsigned char> input);

	static vector<unsigned char> Compress(vector<unsigned char> input);

	//		#endregion
};

