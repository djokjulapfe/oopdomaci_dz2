#include "RSearchTree.h"


RSearchTree::RSearchTree(std::vector<BigDecimal *> &values) {

}

RSearchTree::RSearchTree(const RSearchTree &rSearchTree) {

}

RSearchTree &RSearchTree::operator=(const RSearchTree &rSearchTree) {
	return const_cast<RSearchTree &>(rSearchTree);
}

std::vector<TreeNode *> RSearchTree::intervalNodes(int start, int end) {
	return std::vector<TreeNode *>();
}

BigDecimal RSearchTree::intervalSum(int start, int end) {
	return BigDecimal(nullptr);
}

std::ostream &operator<<(std::ostream &out, const RSearchTree &) {
	return out;
}
