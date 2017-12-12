#include <iostream>
#include "BigDecimal.h"
#include "RSearchTree.h"

int main() {
//	for (int i = 0; i < 1000; ++i) {
//		std::string s1, s2;
//		std::cin >> s1 >> s2;
//		BigDecimal x(s1.c_str());
//		BigDecimal y(s2.c_str());
//		std::cout << x.equals(&y) << std::endl;
//	}

//	BigDecimal x("300");
//	BigDecimal y("-10");
//	BigDecimal z;
//	x += y;
//	std::cout << x << std::endl;
//	x += y;
//	std::cout << x << std::endl;
//	int p;
//	x = x << 3;
//	std::cout << x << std::endl;
//	x >>= &p;
//	std::cout << x << std::endl;
//	x += y;
//	std::cout << x << std::endl;
//	x += y;
//	std::cout << x << std::endl;

//	TreeNode treeNode(0, 10, new BigDecimal("36"));
//	std::cout << treeNode.covers(3, 100) << std::endl;

//	std::vector<BigDecimal *> t;
//	t.push_back(new BigDecimal("1"));
//	t.push_back(new BigDecimal("3"));
//	t.push_back(new BigDecimal("5"));
//	t.push_back(new BigDecimal("7"));
//	t.push_back(new BigDecimal("9"));
//	t.push_back(new BigDecimal("11"));
//
//	RSearchTree *rSearchTree1 = new RSearchTree(t);
//
//	RSearchTree rSearchTree2(*rSearchTree1);
//
//	for (int i = 0; i < t.size(); ++i) {
//		delete t[i];
//	}
//
//	t.clear();
//	t.push_back(new BigDecimal("11"));
//	t.push_back(new BigDecimal("9"));
//	t.push_back(new BigDecimal("7"));
//	t.push_back(new BigDecimal("5"));
//	t.push_back(new BigDecimal("3"));
//	t.push_back(new BigDecimal("1"));
//
//	delete rSearchTree1;
//
//	rSearchTree1 = new RSearchTree(t);
//
//	std::cout << *rSearchTree1 << std::endl;
//	std::cout << rSearchTree2 << std::endl;
//
//	for (int i = 0; i < t.size(); ++i) {
//		delete t[i];
//	}

	for (int k = 0; k < 100 ; ++k) {
		std::vector<BigDecimal*> v;
		for (int i = 0; i < 100; ++i) {
			v.push_back(new BigDecimal("3.14"));
		}
		RSearchTree x(v);
		RSearchTree y(v);
		y = x;
		for (int i = 0; i < 100; ++i) {
			delete v[i];
		}
	}

	return 0;
}