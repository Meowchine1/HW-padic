 #pragma once
#include <bitset>

class BitOperation
{
public:
	static int binaryToDeciminal(std::bitset<64> binaryNum, int bitAmount);

	static std::bitset<64> bitsetAdd(std::bitset<64>& x, std::bitset<64>& y);

	static std::bitset<64> bitsetMultiplication(std::bitset<64>& x, std::bitset<64>& y);

	static double binaryTo_P_adic(std::bitset<64> binaryNum, double radix, int bitAmount);

private:
	static bool fullAdder(bool b1, bool b2, bool& carry);
};

