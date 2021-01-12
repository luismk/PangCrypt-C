#include "MiniLzo.h"

unsigned int MiniLzo::ReadU32(vector<unsigned char>& arr, unsigned int i)
{
	auto result = arr[i] | (arr[i + 1] << 8) | (arr[i + 2] << 16) | (arr[i + 3] << 24);
	return static_cast<unsigned int>(result);
}

unsigned int MiniLzo::ReadU16(vector<unsigned char>& arr, unsigned int i)
{
	auto result = arr[i] | (arr[i + 1] << 8);
	return static_cast<unsigned int>(result);
}

vector<int> MultiplyDeBruijnBitPosition = { 0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9 };

unsigned int MiniLzo::LzoBitOpsCtz32(signed int v)
{
	auto result = ((v & -v) * 0x077CB531U);
	return MultiplyDeBruijnBitPosition[static_cast<unsigned int>(result >> 27)];
}

unsigned int MiniLzo::NearestPowerOfTwo(unsigned int n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	return n + 1;
}

void MiniLzo::AllocSpace(vector<unsigned char>& decompress, unsigned int minLength)
{
	Utils::Resize(decompress, NearestPowerOfTwo(minLength));
}

void MiniLzo::EnsureSpace(unsigned int need, vector<unsigned char>& array, unsigned int pos)
{
	auto needLen = pos + need;
	if (needLen > array.size())
	{
		AllocSpace(array, needLen);
	}
}

unsigned int MiniLzo::Lzo1X1CompressCore(vector<unsigned char>& in, unsigned int inIndex, unsigned int inLen, vector<unsigned char>& out, unsigned int outIndex, unsigned int& outLen, unsigned int ti, vector<unsigned short>& dict)
{
	auto inEnd = inIndex + inLen;
	auto ipEnd = inIndex + inLen - 20;
	auto op = outIndex;
	auto ip = inIndex;
	auto ii = ip;
	ip += ti < 4 ? 4 - ti : 0;

	for (;;)
	{
		literal:
		ip += 1 + ((ip - ii) >> 5);
	next:
		if (ip >= ipEnd)
		{
			break;
		}
		auto dv = ReadU32(in, ip);
		auto dIndex = (((0x1824429d * dv) >> (32 - 14)) & (((1u << 14) - 1) >> 0)) << 0;
		auto mPos = inIndex + dict[dIndex];
		dict[dIndex] = static_cast<unsigned short>(ip - inIndex);
		if (dv != ReadU32(in, mPos))
		{
			goto literal;
		}

		ii -= ti;
		ti = 0;
		{
			auto t = ip - ii;
			if (t != 0)
			{
				if (t <= 3)
				{
					out[op - 2] |= static_cast<unsigned char>(t);
					copy_n(in.begin() + ii, t, out.begin() + op);
					op += t;
				}
				else if (t <= 16)
				{
					out[op++] = static_cast<unsigned char>(t - 3);
					copy_n(in.begin() + ii, t, out.begin() + op);
					op += t;
				}
				else
				{
					if (t <= 18)
					{
						out[op++] = static_cast<unsigned char>(t - 3);
					}
					else
					{
						auto tt = t - 18;
						out[op++] = 0;
						while (tt > 255)
						{
							tt -= 255;
							out[op++] = 0;
						}

						out[op++] = static_cast<unsigned char>(tt);
					}

					copy_n(in.begin() + ii, t, out.begin() + op);
					op += t;
				}
			}
		}
		unsigned int mLen = 4;
		{
			auto v = ReadU32(in, ip + mLen) ^ ReadU32(in, mPos + mLen);
			while (v == 0)
			{
				mLen += 4;
				v = ReadU32(in, ip + mLen) ^ ReadU32(in, mPos + mLen);
				if (ip + mLen >= ipEnd)
				{
					goto m_len_done;
				}
			}

			mLen += static_cast<unsigned int>(LzoBitOpsCtz32(v)) / 8;
		}
	m_len_done:
		auto mOff = ip - mPos;
		ip += mLen;
		ii = ip;
		if (mLen <= 8 && mOff <= 0x0800)
		{
			mOff -= 1;
			out[op++] = static_cast<unsigned char>(((mLen - 1) << 5) | ((mOff & 7) << 2));
			out[op++] = static_cast<unsigned char>(mOff >> 3);
		}
		else if (mOff <= 0x4000)
		{
			mOff -= 1;
			if (mLen <= 33)
			{
				out[op++] = static_cast<unsigned char>(32 | (mLen - 2));
			}
			else
			{
				mLen -= 33;
				out[op++] = 32 | 0;
				while (mLen > 255)
				{
					mLen -= 255;
					out[op++] = 0;
				}

				out[op++] = static_cast<unsigned char>(mLen);
			}

			out[op++] = static_cast<unsigned char>(mOff << 2);
			out[op++] = static_cast<unsigned char>(mOff >> 6);
		}
		else
		{
			mOff -= 0x4000;
			if (mLen <= 9)
			{
				out[op++] = static_cast<unsigned char>(16 | ((mOff >> 11) & 8) | (mLen - 2));
			}
			else
			{
				mLen -= 9;
				out[op++] = (uint8_t)(16 | ((mOff >> 11) & 8));
				while (mLen > 255)
				{
					mLen -= 255;
					out[op++] = 0;
				}
				out[op++] = (uint8_t)mLen;
			}
			out[op++] = (uint8_t)(mOff << 2);
			out[op++] = (uint8_t)(mOff >> 6);
		}
		goto next;
	}
	outLen = op - outIndex;
	return inEnd - (ii - ti);
}

void MiniLzo::Lzo1X1Compress(vector<unsigned char>& in, unsigned int inLen, vector<unsigned char>& out, unsigned int& outLen, vector<unsigned short> dict)
{
	unsigned int ip = 0;
	unsigned int op = 0;
	auto l = inLen;
	unsigned int t = 0;
	while (l > 20)
	{
		auto ll = l;
		ll = ll <= 49152 ? ll : 49152;
		auto llEnd = ip + ll;
		if (llEnd + ((t + ll) >> 5) <= llEnd || llEnd + ((t + ll) >> 5) <= ip + ll)
		{
			break;
		}

		for (auto i = 0; i < (1 << 14) * sizeof(unsigned short); i++)
		{
			dict[i] = 0;
		}
		t = Lzo1X1CompressCore(in, ip, ll, out, op, outLen, t, dict);
		ip += ll;
		op += outLen;
		l -= ll;
	}

	t += l;
	if (t > 0)
	{
		unsigned long long ii = inLen - t;
		if (op == 0 && t <= 238)
		{
			out[op++] = static_cast<unsigned char>(17 + t);
		}
		else if (t <= 3)
		{
			out[op - 2] |= static_cast<unsigned char>(t);
		}
		else if (t <= 18)
		{
			out[op++] = static_cast<unsigned char>(t - 3);
		}
		else
		{
			auto tt = t - 18;
			out[op++] = 0;
			while (tt > 255)
			{
				tt -= 255;
				out[op++] = 0;
			}

			out[op++] = static_cast<unsigned char>(tt);
		}

		do
		{
			out[op++] = in[ii++];
		} while (--t > 0);
	}

	out[op++] = 16 | 1;
	out[op++] = 0;
	out[op++] = 0;
	outLen = op;
}


vector<unsigned char> MiniLzo::Lzo1XDecompress(vector<unsigned char> in)
{
	unsigned int t;
	auto out = vector<unsigned char>(0);
	unsigned int op = 0;
	unsigned int ip = 0;
	auto gtFirstLiteralRun = false;
	auto gtMatchDone = false;

	try
	{
		if (in[ip] > 17)
		{
			t = static_cast<unsigned int>(in[ip++] - 17);
			EnsureSpace(t, out, op);
			if (t > 0)
			{
				do
				{
					out[op++] = in[ip++];
				} while (--t > 0);
			}

			if (t >= 4)
			{
				gtFirstLiteralRun = true;
			}
		}

		while (true)
		{
			unsigned int mPos;
			if (gtFirstLiteralRun)
			{
				gtFirstLiteralRun = false;
				goto FirstLiteralRun;
			}

			t = in[ip++];
			if (t >= 16)
			{
				goto match;
			}
			if (t == 0)
			{
				while (in[ip] == 0)
				{
					t += 255;
					ip++;
				}

				t += static_cast<unsigned int>(15 + in[ip++]);
			}

			t += 3;
			EnsureSpace(t, out, op);
			if (t > 0)
			{
				do
				{
					out[op++] = in[ip++];
				} while (--t > 0);
			}

		FirstLiteralRun:
			t = in[ip++];
			if (t >= 16)
			{
				goto match;
			}
			mPos = op - (1 + 0x0800);
			mPos -= t >> 2;
			mPos -= static_cast<unsigned int>(in[ip++]) << 2;

			EnsureSpace(3, out, op);
			out[op++] = out[mPos++];
			out[op++] = out[mPos++];
			out[op++] = out[mPos];
			gtMatchDone = true;

		match:
			do
			{
				if (gtMatchDone)
				{
					gtMatchDone = false;
					goto MatchDone;
				}

				if (t >= 64)
				{
					mPos = op - 1;
					mPos -= (t >> 2) & 7;
					mPos -= static_cast<unsigned int>(in[ip++]) << 3;
					t = (t >> 5) - 1;

					t += 2;
					EnsureSpace(t, out, op);
					do
					{
						out[op++] = out[mPos++];
					} while (--t > 0);

					goto MatchDone;
				}

				if (t >= 32)
				{
					t &= 31;
					if (t == 0)
					{
						while (in[ip] == 0)
						{
							t += 255;
							ip++;
						}

						t += static_cast<unsigned int>(31 + in[ip++]);
					}

					mPos = op - 1;
					mPos -= ReadU16(in, ip) >> 2;
					ip += 2;
				}
				else if (t >= 16)
				{
					mPos = op;
					mPos -= (t & 8) << 11;
					t &= 7;
					if (t == 0)
					{
						while (in[ip] == 0)
						{
							t += 255;
							ip++;
						}

						t += static_cast<unsigned int>(7 + in[ip++]);
					}

					mPos -= ReadU16(in, ip) >> 2;
					ip += 2;
					if (mPos == op)
					{
						goto EofFound;
					}
					mPos -= 0x4000;
				}
				else
				{
					mPos = op - 1;
					mPos -= t >> 2;
					mPos -= static_cast<unsigned int>(in[ip++]) << 2;
					EnsureSpace(2, out, op);
					out[op++] = out[mPos++];
					out[op++] = out[mPos];
					goto MatchDone;
				}

				t += 2;
				EnsureSpace(t, out, op);
				do
				{
					out[op++] = out[mPos++];
				} while (--t > 0);

			MatchDone:
				t = (int)(in[ip - 2] & 3);
				if (t == 0) break;

				EnsureSpace(t, out, op);
				if (t > 0)
					do
					{
						out[op++] = in[ip++];
					} while (--t > 0);

					t = in[ip++];
			} while (true);
		}
	EofFound:
		Utils::Resize(out, (int)op);
		return out;
	}
	catch (const exception& ex)
	{

	}
}

vector<unsigned char> MiniLzo::Decompress(vector<unsigned char> input)
{
	return Lzo1XDecompress(input);
}

vector<unsigned char> MiniLzo::Compress(vector<unsigned char> input)
{
	auto out = vector<unsigned char>(input.size() + input.size() / 16 + 64 + 3);
	unsigned int outLen = 0;
	Lzo1X1Compress(input, (int)input.size(), out, outLen, vector<unsigned short>(32768));
	Utils::Resize(out, outLen);
	return out;
}
