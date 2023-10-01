
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <string> 

#include "BitOperation.h"
#include "Functions.h"

//===============================================================================================
// Variant = 24 mod 20 + 1 = 5
// 
// github: https://github.com/Meowchine1/HW-padic
//===============================================================================================


bool сycleExist(std::map<int, int> mapping) {
	std::vector<int> passed;
	passed.push_back(mapping.begin()->first);

	for (auto &elem : mapping) {
		if (std::find(passed.begin(), passed.end(), elem.second) != passed.end()) {

			return false;
		}
		passed.push_back(elem.second);
	}
	return true;
}

void transitionBijectionCheck(int module, std::map<int, int> inputMapping, bool& transitive, bool& bijective) {
	std::cout << "MODULE [" << module << "]\n" << "Set size = " << inputMapping.size() << "\n";

	std::map<int, int> passedMapping;
	auto display = inputMapping.begin();
	for (int i = 0; i <= module; i++) {
		auto prototype = display->first;
		auto image = display->second;
		
		// when several keys refer same image function is not bijective
		for (auto &elem : passedMapping) {
		
			if (elem.second == image) {
				std::cout << "Attention: several keys refer same image function is not bijective.\n";
				transitive = false;
				bijective = false;
				break;
			}
		}
		
		// map keys are unique according to the task
		passedMapping.insert(prototype, image);

		std::cout << "f" << "(" << prototype << ") =" << image << "\n";

		if (i < module) {
			// that means cycle closed before checking all nodes. And we can say that this function isn't one-cycle permitation.
			if (сycleExist(passedMapping)) { 
				std::cout << "Attention: cycle closed up before checking all nodes.\n";
				transitive = false;
			}
		}
		else { // если циклов вообще нет то это не биективное отображение и как следствие не транзитивное
			if (!сycleExist(passedMapping)) {
				std::cout << "Attention: no cycles.\n";
				transitive = false;
				bijective = false;
				break;
			}
		}
		display = inputMapping.find(image);
		if (display == inputMapping.end()) {
			// deadlock  тупиковое отображение
			std::cout << "Attention: deadlock.\n";
			transitive = false;
			bijective = false;
			break;
		}
	}
}

void Task_1_1(int (*f)(int)) {
	int  nMax = 10;
	bool isTransitive = true, isBijective = true;
	for (int i = 1; i < nMax; i++) {
		int module = pow(2, i);
		std::map<int, int> permitations;
		for (int j = 0; j < module; j++) {
			permitations.insert(std::make_pair(j, f(j) % module));
		}
		transitionBijectionCheck(module, permitations, isTransitive, isBijective);
	}
	std::cout << "\n\n";
	std::string result;
	result += "[Transition]: "; result += isTransitive ? "Yes\n" : "No\n";
	result += "[Bijection]: ";  result += isBijective ? "Yes\n" : "No\n";
	std::cout << "Result:" << result;
}

void Task_1_2(int (*f)(int, int)) {
	int coef = 3, nMax = 5, numerator = 9, denominator = 7;;
	bool isTransitive = true, isBijective = true;
	unsigned long long int negative_binary = 1, rank = 1, powValue;
	for (int i = 1; i < nMax; i++) { // -1/7
		int degree = coef * i;
		powValue = pow(10, degree - coef * (i - 1));;
		rank *= powValue;
		negative_binary += rank;
	}
	std::bitset<32> positive_binary(std::to_string(negative_binary));
	std::bitset<32> num(numerator);
	positive_binary = BitOperation::bitsetMultiplication(positive_binary, num);// -9/7
	positive_binary = ~positive_binary;
	positive_binary[0] = 1;
	std::cout << "positive_binary: " << positive_binary << '\n'; // 9/7
	 
	for (int i = 1; i < nMax; i++) {
		int module = pow(2, i);
		std::map<int, int> permitations;
		for (int j = 0; j < module; j++) {
			permitations.insert(std::make_pair(j, f(j, BitOperation::binaryToDeciminal(positive_binary, j)) % module));
		}
		transitionBijectionCheck(module, permitations, isTransitive, isBijective);
	}
	std::cout << "\n\n";
	std::string result;
	result += "[Transition]: "; result += isTransitive ? "Yes\n" : "No\n";
	result += "[Bijection]: ";  result += isBijective ? "Yes\n" : "No\n";
	std::cout << "Result:" << result;
}
 
int main() {
	Task_1_1(Functions::f);
	Task_1_1(Functions::transitiveFunction);
	Task_1_2(Functions::g);
}
