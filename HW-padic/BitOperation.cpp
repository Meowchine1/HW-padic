#include "BitOperation.h"

int BitOperation::binaryToDeciminal(std::bitset<32> binaryNum, int bitAmount) {
	int decimal_number = 0;
	for (int l = 0; l < bitAmount; l++) {
		if (binaryNum[l] == 1) {
			decimal_number +=  pow(2, l);
		}
		
	}
	return decimal_number;
}

bool BitOperation::fullAdder(bool b1, bool b2, bool& carry)
{
	bool sum = (b1 ^ b2) ^ carry;
	carry = (b1 && b2) || (b1 && carry) || (b2 && carry); // 
	return sum;
}

std::bitset<32> BitOperation::bitsetAdd(std::bitset<32>& x, std::bitset<32>& y)
{
	bool carry = false;
	std::bitset<32> ans;
	for (int i = 0; i < 32; i++) {
		ans[i] = fullAdder(x[i], y[i], carry);
	}
	return ans;
}

std::bitset<32> BitOperation::bitsetMultiplication(std::bitset<32>& x, std::bitset<32>& y)
{
	std::bitset<32> ans(0);
	int rang = 0;
	for (int i = 0; i < 32; i++) {
		if (y[i]) {
			x = x << rang;
			rang = 1;
			ans = bitsetAdd(ans, x);
		}
		else {
			rang++;
		}
	}
	return ans;
}