#include<cmath>
#include <bitset>
#include<string>

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


double Functions::kakutani_neumann(int num) {
    double decimal_fraction = 0.0;  double denominator = 10.0, remainder = num;
    while (num > 0){
       remainder = num % 10;
       num /= 10;
       decimal_fraction += remainder / (denominator);
       denominator *= 10;
    } 
     
    return decimal_fraction;
}

double Functions::monna_map(int n) {
    double result = 0, factor = 1.0, monna_base = 3;
    while (n > 0) {
        int remainder = n % 2;
        n /= 2;
        result += remainder * factor;
        factor *= monna_base;
    }
    return result;
}
 
     


