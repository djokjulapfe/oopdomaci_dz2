#include "RSearchTree.h"
#include <queue>

RSearchTree::RSearchTree(std::vector<BigDecimal *> &values) {
	std::vector<StackElement> stack;
	std::vector<BigDecimal> acc;
	acc.push_back(BigDecimal("0"));
	for (auto &&v : values) {
		acc.push_back(*acc.rbegin() + *v);
	}
	root = new TreeNode(0, values.size() - 1, &acc[values.size()]);
	stack.push_back(StackElement(root, RIGHT, values.size() / 2, values.size() - 1));
	stack.push_back(StackElement(root, LEFT, 0, values.size() / 2 - 1));
	while (!stack.empty()) {
		StackElement currSE = stack.back();
		stack.pop_back();
		int s = currSE.start;
		int e = currSE.end;
		BigDecimal *sum = new BigDecimal(acc[e+1] - acc[s]);
		TreeNode *tNode = new TreeNode(s, e, sum);
		if (currSE.side == RIGHT) {
			currSE.parent->setRight(tNode);
		} else {
			currSE.parent->setLeft(tNode);
		}
		int len = currSE.end - currSE.start;
		if (len > 0) {
			stack.push_back(StackElement(tNode, RIGHT, currSE.start + len / 2 + 1, currSE.end));
			stack.push_back(StackElement(tNode, LEFT, currSE.start, currSE.start + len / 2));
		}
	}
}

RSearchTree::RSearchTree(const RSearchTree &rSearchTree) {
	std::queue<RSearchTree::StackElement> queue;
	root = rSearchTree.root;
	queue.push(RSearchTree::StackElement(rSearchTree.root, LEFT, 0, 0));
	while (!queue.empty()) {
		RSearchTree::StackElement currSE = queue.front();
		queue.pop();
		if (currSE.parent->getLeft() != nullptr || currSE.parent->getRight() != nullptr) {
			queue.push(RSearchTree::StackElement(currSE.parent->getLeft(), LEFT, 0, 0));
			queue.push(RSearchTree::StackElement(currSE.parent->getRight(), RIGHT, 0, 0));
		}
	}
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

std::ostream &operator<<(std::ostream &out, const RSearchTree &rSearchTree) {
	std::queue<RSearchTree::StackElement> queue;
	queue.push(RSearchTree::StackElement(rSearchTree.root, LEFT, 0, 0));
	while (!queue.empty()) {
		RSearchTree::StackElement currSE = queue.front();
		queue.pop();
		if (currSE.parent->getLeft() != nullptr || currSE.parent->getRight() != nullptr) {
			queue.push(RSearchTree::StackElement(currSE.parent->getLeft(), LEFT, 0, 0));
			queue.push(RSearchTree::StackElement(currSE.parent->getRight(), RIGHT, 0, 0));
		}
		out << *currSE.parent << ',';
	}
	return out;
}

RSearchTree::StackElement::StackElement(TreeNode *parent, bool side, int start, int end) : parent(parent),
																						   start(start),
																						   end(end), side(side) {}
