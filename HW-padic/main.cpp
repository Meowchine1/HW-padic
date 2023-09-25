
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <bitset>

int f(int x) { 
	return 33 + 3 * x * x;
}

int f2(int x) {  // transitive
	return 2 * x * x + 3 * x + 7;

}

int g(int x, int floatNumValue) {
	return 13 * x + floatNumValue;
}

int main() {
	// f(x) transitive test start
	bool isTransitive = true, isCyclesExist = false;
	int  nMax = 10;
	for (int i = 1; i < nMax; i++) {
		int module = pow(2, i);
		std::map<int, int> permitations;
		for (int j = 0; j < module; j++) {

			permitations.insert(std::make_pair(j, f(j) % module));

		}
		std::cout <<"MODULE [" << module << "]\n";
		std::cout << "Set size = " << permitations.size() << "\n";
		int tmp = 0;
		std::vector<int> circle;
		for (int i = 0; i <= module; i++) {
			auto from = permitations.find(tmp);
			if (from != permitations.end()) {
				std::cout << tmp << "->";
				int to = from->second;
				if(std::find(circle.begin(), circle.end(), to) != circle.end()){  // cycle exist
					isCyclesExist = true;
					if (i < module) // if cycle closed up before we reached the last element
						// that means input function is non-bijective mapping 
					{
						isTransitive = false;
						std::cout << "{!}";
					}
				}
				tmp = to;
				circle.push_back(to);
			}
			else {
				std:: cout << "\nERROR!!! Wrong input set\n";
				break;
			}
		}
		if (!isCyclesExist) { isTransitive = false; std::cout << "\nERROR!!!No cycle\n"; }
		std::cout << "\n \n";
	}

	std::cout << "\n \n";
	std::string result = isTransitive? "Function is transitive" : "Function is not transitive";
	std::cout << "Result :" << result;
	std::cout << "\n \n";
	// f(x) transitive test end


	// g(x)

	union
	{
		float input; // assumes sizeof(float) == sizeof(int)
		int   output;
	} data;

	data.input = 0.8;

	std::bitset<sizeof(float)* CHAR_BIT> bits(data.output);
	std::cout << bits << std::endl;

	unsigned long range = bits.to_ulong() >> 2 & ((1 << (5 - 2 + 1)) - 1);

	// Output the range of bits
	std::cout << std::bitset<4>(range) << std::endl;

	isTransitive = true, isCyclesExist = false;
	nMax = 10;

	for (int i = 1; i < nMax; i++) {
		int module = pow(2, i);
		std::map<int, int> permitations;


	}


	// or
	std::cout << "BIT 4: " << bits[4] << std::endl;
	std::cout << "BIT 7: " << bits[7] << std::endl;




}