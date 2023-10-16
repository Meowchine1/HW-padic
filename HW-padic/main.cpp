
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <string> 
#include <iomanip>
#include <SFML/Graphics.hpp>
#include<cmath>

#include "BitOperation.h"
#include "Functions.h"


//===============================================================================================
// Variant = 24 mod 20 + 1 = 5
// 
// full in github: https://github.com/Meowchine1/HW-padic
//===============================================================================================

std::string LINE(70, '='), LINEDELIMITER = LINE.append("\n\n");
const int H = 600, W = 600;

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
	int coef = 3, nMax = 4, numerator = 9, denominator = 7;;
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


void print(int k, int (*f)(int)) {
	sf::RenderWindow window(sf::VideoMode(H, W), "15"); window.setFramerateLimit(60);
	sf::Event event; sf::CircleShape point(5); point.setFillColor(sf::Color::Red);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
		}
		window.clear();
		int module = pow(2, k);
		for (int j = 0; j < module; j++) {
			double num = j;
			double rationalNum = num / module;
			double f_value = f(j) % module;
			double rational_f_value = f_value / module;
			//std::cout << rationalNum * H << ";" << rational_f_value * W << "\n";
			point.setPosition(rationalNum * H, rational_f_value * W);
			window.draw(point);
		}
		window.display();
	}
}

void print_1_2(int k, int (*f)(int, int)) {
	sf::RenderWindow window(sf::VideoMode(H, W), "15"); window.setFramerateLimit(60);
	sf::Event event; sf::CircleShape point(5); point.setFillColor(sf::Color::Red);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
		}
		window.clear();
		int coef = 3, nMax = k, numerator = 9, denominator = 7;
		unsigned long long int negative_binary = 1, rank = 1, powValue;
		for (int i = 1; i < nMax; i++) { // -1/7
			int degree = coef * i;
			powValue = pow(10, degree - coef * (i - 1));;
			rank *= powValue;
			negative_binary += rank;
		}
		std::bitset<32> neg_binary(std::to_string(negative_binary));
		std::bitset<32> num(numerator);
		neg_binary = BitOperation::bitsetMultiplication(neg_binary, num);
		std::bitset<32> positive_binary = ~neg_binary;
		positive_binary[0] = 1;
		int module = pow(2, k);
		int binaryToDeciminal = BitOperation::binaryToDeciminal(positive_binary, k);
		for (int j = 0; j < module; j++) {
			double num = j;
			double rationalNum = num / module;
			double f_value = f(j, binaryToDeciminal) % module;
			double rational_f_value = f_value / module;
			point.setPosition(rationalNum * H, rational_f_value * W);
			window.draw(point);
		}
		window.display();
	}
}

double radix(int n) {
	return pow(2, 1 / n);
}

void print_beta(int k, int (*f)(int)) {
	double p = radix(k);
	int nodeCount = 20;
	sf::RenderWindow window(sf::VideoMode(H, W), "15"); window.setFramerateLimit(60);
	sf::Event event; sf::CircleShape point(5); point.setFillColor(sf::Color::Red);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
		}
		window.clear();
		for (int j = 0; j < nodeCount; j++) {
			std::bitset<32> prototype(j);
			std::bitset<32> image(f(j));
			double p_adic_prototype = BitOperation::binaryTo_P_adic(prototype, p, k);
			double p_adic_image = BitOperation::binaryTo_P_adic(image, p, k);
			int x = (int)p_adic_prototype / p, y = (int)p_adic_image / p;
			point.setPosition(x * H/4, y * W/4);
			//std::cout << x * H / 4 << ";" << y * W / 4 << "\n";
			window.draw(point);
		}
		window.display();
	}
}

void print_beta_1_2(int k, int (*f)(int, int)) {
	double p = radix(k);
	int nodeCount = 20;
	sf::RenderWindow window(sf::VideoMode(H, W), "15"); window.setFramerateLimit(60);
	sf::Event event; sf::CircleShape point(5); point.setFillColor(sf::Color::Red);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
		}
		window.clear();
		int coef = 3, nMax = k, numerator = 9, denominator = 7;
		unsigned long long int negative_binary = 1, rank = 1, powValue;
		for (int i = 1; i < nMax; i++) { // -1/7
			int degree = coef * i;
			powValue = pow(10, degree - coef * (i - 1));;
			rank *= powValue;
			negative_binary += rank;
		}
		std::bitset<32> neg_binary(std::to_string(negative_binary));
		std::bitset<32> num(numerator);
		neg_binary = BitOperation::bitsetMultiplication(neg_binary, num);
		std::bitset<32> positive_binary = ~neg_binary;
		positive_binary[0] = 1;
		int module = pow(2, k);
		int binaryToDeciminal = BitOperation::binaryToDeciminal(positive_binary, k);
		for (int j = 0; j < module; j++) {
			double num = j;
			//double rationalNum = num / module;
			double f_value = f(j, binaryToDeciminal) % module;
			//double rational_f_value = f_value / module;

			std::bitset<32> prototype(num);
			std::bitset<32> image(f_value);
			double p_adic_prototype = BitOperation::binaryTo_P_adic(prototype, p, k);
			double p_adic_image = BitOperation::binaryTo_P_adic(image, p, k);
			int x = (int)p_adic_prototype / p, y = (int)p_adic_image / p;
			point.setPosition(x * H / 4, y * W / 4);
			window.draw(point);
		}
		window.display();
	}
}

 

 
int main() {
	
	//print(8, Functions::f);
	/*print_1_2(6, Functions::g);*/
	//print(8, Functions::logicF);


	//print_beta(10, Functions::f);
	//print_beta(5, Functions::f);
	//print_beta(10, Functions::f);
	// 
	//print_beta_1_2(5, Functions::g);
	// 
	print_beta(10, Functions::logicF);
	 
	}


