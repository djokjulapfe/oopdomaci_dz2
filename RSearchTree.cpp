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
		BigDecimal *sum = new BigDecimal(acc[e + 1] - acc[s]);
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
		delete sum;
	}
}

RSearchTree::~RSearchTree() {
	free_tree();
}

RSearchTree::RSearchTree(const RSearchTree &rSearchTree) {
	*this = rSearchTree;
}

RSearchTree &RSearchTree::operator=(const RSearchTree &rSearchTree) {
	if (this != &rSearchTree) {
		free_tree();
		std::vector<RSearchTree::StackElement> stack;
		root = new TreeNode(*rSearchTree.root);
		if (root->getRight() != nullptr) {
			root->setRight(new TreeNode(*root->getRight()));
			stack.push_back(RSearchTree::StackElement(root->getRight(), RIGHT, root->getRight()->getStart(),
													  root->getRight()->getEnd()));
		}
		if (root->getLeft() != nullptr) {
			root->setLeft(new TreeNode(*root->getLeft()));
			stack.push_back(RSearchTree::StackElement(root->getLeft(), LEFT, root->getLeft()->getStart(),
													  root->getLeft()->getEnd()));
		}
		while (!stack.empty()) {
			RSearchTree::StackElement currSE = stack.back();
			stack.pop_back();
			if (currSE.parent->getRight() != nullptr) {
				currSE.parent->setRight(new TreeNode(*currSE.parent->getRight()));
				stack.push_back(RSearchTree::StackElement(currSE.parent->getRight(), RIGHT,
														  currSE.parent->getRight()->getStart(),
														  currSE.parent->getRight()->getEnd()));
			}
			if (currSE.parent->getLeft() != nullptr) {
				currSE.parent->setLeft(new TreeNode(*currSE.parent->getLeft()));
				stack.push_back(RSearchTree::StackElement(currSE.parent->getLeft(), LEFT,
														  currSE.parent->getLeft()->getStart(),
														  currSE.parent->getLeft()->getEnd()));
			}
		}
	}
	return *this;
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

void RSearchTree::free_tree() {
	std::vector<TreeNode *> stack;
	stack.push_back(root);
	while (!stack.empty()) {
		TreeNode *tNode = stack.back();
		stack.pop_back();
		if (tNode != nullptr) {
			stack.push_back(tNode->getRight());
			stack.push_back(tNode->getLeft());
		}
		delete tNode;
	}
}

RSearchTree &RSearchTree::operator=(RSearchTree &&rSearchTree) {
	return *this;
}

RSearchTree::StackElement::StackElement(TreeNode *parent, bool side, int start, int end) : parent(parent),
																						   start(start),
																						   end(end), side(side) {
}
