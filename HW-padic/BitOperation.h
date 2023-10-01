#include <bitset>
#pragma once

class BitOperation
{
public:
	static int binaryToDeciminal(std::bitset<32> binaryNum, int bitAmount);

	static std::bitset<32> bitsetAdd(std::bitset<32>& x, std::bitset<32>& y);

	static std::bitset<32> bitsetMultiplication(std::bitset<32>& x, std::bitset<32>& y);

private:
	static bool fullAdder(bool b1, bool b2, bool& carry);
};

