
#include <cmath>
#include <list>
#include <iostream>

int f(int x) {
	return 33 + 3 * x * x;
}

double g(int x) {
	return 13 * x + 0.8;
}

bool isCircle(std::list<int> list) {

	return true;
}

std::list<int>::iterator circularNext(std::list<int>& l, std::list<int>::iterator& it)
{
	return std::next(it) == l.end() ? l.begin() : std::next(it);
}

int main() {



	int n = 1, nMax = 10;
	bool isTransitive = true;
	// f(x)
	while (n < nMax) {
		int module = pow(2, n);
		std::list<int> set;
		set.push_back(0);
		for (int i = 0; i < module; i++) {
			int result = f(i) % module;
			std::list<int>::iterator iter = std::find_if(set.begin(), set.end(), [=](int n) {
				return n == result;
				});
			if (iter != set.end()) {
				set.push_back(set.front());   // make a cycle
				break;
			}
			else {
				set.push_back(result);
			}
		}
		// check cycle
		if (set.back() != set.front()) { isTransitive = false; }
		else {
			std::cout << "[MODULE = " << module << "]" << std::endl;
			auto begin = set.begin();
			std::cout << *begin << " -> ";
			auto iter = circularNext(set, begin);
			while (iter != set.begin()) {
				std::cout << *iter << " -> ";
				auto newIter = circularNext(set, iter);
				iter = newIter;
			}
			std::cout << *iter << "\n";


			 
			
			std::cout << std::endl;
			std::cout << std::endl;
		}

		n++;
	}



}