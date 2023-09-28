
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <bitset>
#include <string> 

// Valiant = 24 mod 20 + 1 = 5
//
int f(int x) { 
	return 12 + 3 * x  - 14 * x * x;
}

int f2(int x) {  // transitive function
	return 2 * x * x + 3 * x + 7;
}

int g(int x, int floatNumValue) {
	return 11 + floatNumValue * x;
}

void startIteration(int module, std::map<int, int> permitations, bool& transitive, bool& cycle) {
	std::cout << "MODULE [" << module << "]\n";
	std::cout << "Set size = " << permitations.size() << "\n";
	int tmp = 0;
	std::vector<int> circle;
	for (int i = 0; i <= module; i++) {
		auto from = permitations.find(tmp);
		if (from != permitations.end()) {
			std::cout << tmp << "->";
			int to = from->second;
			if (std::find(circle.begin(), circle.end(), to) != circle.end()) {  // cycle exist
				cycle = true;
				if (i < module) // if cycle closed up before we reached the last element
					// that means input function is non-bijective mapping 
				{
					transitive = false;
					std::cout << "{!}";
				}
			}
			tmp = to;
			circle.push_back(to);
		}
		else {
			std::cout << "\nERROR!!! Wrong input set\n"; // That means permutation collection has not key for transition
			transitive = false;
			break;
		}
	}
	if (!cycle) { transitive = false; std::cout << "\nERROR!!!No cycle\n"; }
	std::cout << "\n \n";
}

int binaryToDeciminal(std::bitset<32> binaryNum, int bitAmount) {
	int decimal_number = 0, r = 1;
	for (int l = 0; l < bitAmount; l++) {
		if (binaryNum[l] == 1) {

			decimal_number += r * pow(2, l);
		}
		r *= 10;
	}
	return decimal_number;
}

void Task_1_1(int (*f)(int)) {
	int  nMax = 10;
	bool isTransitive = true, isCyclesExist = false;
	for (int i = 1; i < nMax; i++) {
		int module = pow(2, i);
		std::map<int, int> permitations;
		for (int j = 0; j < module; j++) {
			permitations.insert(std::make_pair(j, f(j) % module));
		}
		startIteration(module, permitations, isTransitive, isCyclesExist);
	}
	std::cout << "\n \n";
	std::string result = isTransitive ? "Function f() is transitive" : "Function f() is not transitive";
	std::cout << "Result :" << result;
	std::cout << "\n \n";
}

void Task_1_2() {
	int coef = 3, nMax = 5;
	bool isTransitive = true, isCyclesExist = false;
	unsigned long long int negative_binary = 1, rank = 1, powValue;
	for (int i = 1; i < nMax; i++) { // -1/7
		int degree = coef * i;
		powValue = pow(10, degree - coef * (i - 1));;
		rank *= powValue;
		negative_binary += rank;
	}
	std::bitset<32> positive_binary(std::to_string(negative_binary));
	positive_binary = ~positive_binary;
	positive_binary[0] = 1;
	std::cout << "positive_binary: " << positive_binary << '\n'; // 1/7
	 
	for (int i = 1; i < nMax; i++) {
		int module = pow(2, i);
		std::map<int, int> permitations;
		for (int j = 0; j < module; j++) {
			permitations.insert(std::make_pair(j, g(j, binaryToDeciminal(positive_binary, j)) % module));
		}
		startIteration(module, permitations, isTransitive, isCyclesExist);
	}
	std::cout << "\n \n";
	std::string result = isTransitive ? "Function g() is transitive" : "Function g() is not transitive";
	std::cout << "Result :" << result;
	std::cout << "\n \n";
}
 

 

int main() {
	Task_1_1(&f);
	Task_1_1(&f2);
	Task_1_2();
}
