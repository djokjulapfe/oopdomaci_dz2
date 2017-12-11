#include <iostream>
#include "BigDecimal.h"

int main() {
//	for (int i = 0; i < 1000; ++i) {
//		std::string s1, s2;
//		std::cin >> s1 >> s2;
//		BigDecimal x(s1.c_str());
//		BigDecimal y(s2.c_str());
//		std::cout << x.equals(&y) << std::endl;
//	}

	BigDecimal x("300");
	BigDecimal y("-10");
	BigDecimal z;
	x += y;
	x += y;
	int p;
	x = x << 3;
	x >>= &p;
	x += y;
	x += y;
	std::cout << x << std::endl;

	return 0;
}