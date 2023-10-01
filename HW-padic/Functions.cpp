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
