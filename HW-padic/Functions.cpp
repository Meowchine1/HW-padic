#include "Functions.h"

int Functions::f(int x) {
	return 12 + 3 * x - 14 * x * x;
}

int Functions::transitiveFunction(int x) {
	return 2 * x * x + 3 * x + 7;
}

int Functions::g(int x, int floatNumValue) {
	return 11 + floatNumValue * x;
}

int Functions::logicF(int x)
{
	return ((x + 1) ^ 4) ^ (4 * (x & (1 + 2 * x) & (3 + 4 * x)
		& (7 + 8 * x) & (15 + 16 * x) & (31 + 32 * x) &
		(63 + 64 * x))) + 8 * (x * x + 24);
}


