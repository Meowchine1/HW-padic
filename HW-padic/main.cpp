
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <string> 
#include <iomanip>

#include "BitOperation.h"
#include "Functions.h"


//===============================================================================================
// Variant = 24 mod 20 + 1 = 5
// 
// full in github: https://github.com/Meowchine1/HW-padic
//===============================================================================================

std::string LINE(70, '=');
std::string LINEDELIMITER = LINE.append("\n\n");

bool сycleExist(std::map<int, int> mapping) {
	std::vector<int> passed;

	auto nextPair = mapping.begin();
	int i = 0;
	while (i < mapping.size() + 1) {

		int prototype = nextPair->first;
		int image = nextPair->second;
		if (std::find(passed.begin(), passed.end(), image) != passed.end() ) {
			return true;
		}
		passed.push_back(image);
		nextPair = mapping.find(image);

		if (nextPair == mapping.end()) {
			for (auto elem : mapping) {
				if (std::find(passed.begin(), passed.end(), elem.second) == passed.end()) {
					nextPair = mapping.find(elem.first);
					passed.clear();
				}
			}
		}
		if (nextPair == mapping.end()) { return false; }
		i++;
	}
	return false;
}

void transitionBijectionCheck(int module, std::map<int, int> inputMapping, bool& transitive, bool& bijective) {
	std::cout << "\nMODULE [" << module << "]\n"<< LINEDELIMITER << "Set size = " << inputMapping.size() << "\n";
	std::map<int, int> passedMapping;
	auto display = inputMapping.begin();
	int i = 0;
	for (auto display : inputMapping) {
		int prototype = display.first;
		int image = display.second;

		for (auto& elem : passedMapping) {
			if (elem.second == image) {
				std::cout << "Attention: several keys refer same image function is not bijective and transitive.\n";
				transitive = false;
				bijective = false;
				break;
			}
		}
		// map keys are unique according to the task
		passedMapping.insert(std::make_pair(prototype, image));
		std::cout << "f" << "(" << prototype << ") =" << image << "\n";

		if (inputMapping.find(image) == inputMapping.end()) {

			std::cout << "Attention: image falue from another set\n";
			transitive = false;
			bijective = false;
			break;
		}

		if (i < (module - 1)) {
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
		i++;
	}
}

void Task_1_1(int (*f)(int)) {
	int  nMax = 4;
	bool isTransitive = true, isBijective = true;
	for (int i = 1; i < nMax; i++) {
		int module = pow(2, i);
		std::map<int, int> permitations;
		for (int j = 0; j < module; j++) {
			permitations.insert(std::make_pair(j, f(j) % module));
		}
		if (!(isTransitive || isBijective)) { 
			std::cout << "\nSTOP CHECKING! No need to continue\n";
			break; 
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

	std::bitset<32> neg_binary(std::to_string(negative_binary));
	std::bitset<32> num(numerator);

	std::cout << "Check binary numbers: \n";
	std::cout << std::right << std::setw(10) << "-1/7 = " << neg_binary << "\n";
	std::cout << std::right << std::setw(10) << "9 = " << num << "\n\n";

	neg_binary = BitOperation::bitsetMultiplication(neg_binary, num);
	std::cout << std::right << std::setw(10) << "-9/7 = " << neg_binary << "\n";
	std::bitset<32> positive_binary = ~neg_binary;
	positive_binary[0] = 1;
	std::cout << std::right << std::setw(10) << "9/7 = " << positive_binary << '\n';
	 
	for (int i = 1; i < nMax; i++) {
		int module = pow(2, i);
		int binaryToDeciminal = BitOperation::binaryToDeciminal(positive_binary, i);
		std::cout << "\n\nbit count = " << i << "  deciminal -> " << binaryToDeciminal << "\n";
		std::map<int, int> permitations;
		for (int j = 0; j < module; j++) {

			permitations.insert(std::make_pair(j, f(j, binaryToDeciminal) % module));
		}
		transitionBijectionCheck(module, permitations, isTransitive, isBijective);
	}
	std::cout << "\n\n";
	std::string result;
	result += "[Transition]: "; result += isTransitive ? "Yes\n" : "No\n";
	result += "[Bijection]: ";  result += isBijective ? "Yes\n" : "No\n";
	std::cout << "Result:" << result;
}

void Task2(int (*f)(int)) {
	bool isTransitive = true, isBijective = true;
	int module = 256;
	std::map<int, int> permitations;
	for (int j = 0; j < module; j++) {
		permitations.insert(std::make_pair(j, f(j) % module));
	}
	transitionBijectionCheck(module, permitations, isTransitive, isBijective);
	std::string result;
	result += "[Transition]: "; result += isTransitive ? "Yes\n" : "No\n";
	result += "[Bijection]: ";  result += isBijective ? "Yes\n" : "No\n";
	std::cout << "Result:" << result;
}

	
 
int main() {
	/*std::cout << "\tFUNCTION f(x)\n";
	Task_1_1(Functions::f);
	std::cout << LINEDELIMITER;
	std::cout << "\tFUNCTION transitive(x)\n";
	Task_1_1(Functions::transitiveFunction);
	std::cout << LINEDELIMITER;
	Task_1_2(Functions::g);*/

	Task2(Functions::logicF);

}
