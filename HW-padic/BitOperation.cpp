#include "BitOperation.h"

int BitOperation::binaryToDeciminal(std::bitset<64> binaryNum, int bitAmount) {
	int decimal_number = 0;
	for (int l = 0; l < bitAmount; l++) {
		if (binaryNum[l] == 1) {
			decimal_number +=  pow(2, l);
		}
	}
	return decimal_number;
}

double BitOperation::binaryTo_P_adic(std::bitset<64> binaryNum, double radix, int bitAmount)
{
	double p_adic_number = 0;
	for (int l = 0; l < bitAmount; l++) {
		if (binaryNum[l] == 1) {
			p_adic_number += pow(radix, l);
		}
	}
	return p_adic_number;
}

bool BitOperation::fullAdder(bool b1, bool b2, bool& carry)
{
	bool sum = (b1 ^ b2) ^ carry;
	carry = (b1 && b2) || (b1 && carry) || (b2 && carry); // 
	return sum;
}

std::bitset<64> BitOperation::bitsetAdd(std::bitset<64>& x, std::bitset<64>& y)
{
	bool carry = false;
	std::bitset<64> ans;
	for (int i = 0; i < 64; i++) {
		ans[i] = fullAdder(x[i], y[i], carry);
	}
	return ans;
}

std::bitset<64> BitOperation::bitsetMultiplication(std::bitset<64>& x, std::bitset<64>& y)
{
	std::bitset<64> ans(0);
	int rang = 0;
	for (int i = 0; i < 64; i++) {
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

 
