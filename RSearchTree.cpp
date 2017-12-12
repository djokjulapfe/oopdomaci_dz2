#include "RSearchTree.h"
#include <queue>

RSearchTree::RSearchTree(std::vector<BigDecimal *> &values) {

	// stack to emulate recursion
	std::vector<StackElement> stack;

	// accomulator array
	std::vector<BigDecimal> acc;

	// put the 0 as the first element
	acc.push_back(BigDecimal("0"));

	// calculate the array
	for (auto &&v : values) {
		acc.push_back(*acc.rbegin() + *v);
	}

	// initialize the root
	root = new TreeNode(0, values.size() - 1, &acc[values.size()]);

	// initialize stack
	stack.push_back(StackElement(root, RIGHT, values.size() / 2, values.size() - 1));
	stack.push_back(StackElement(root, LEFT, 0, values.size() / 2 - 1));

	// main while loop
	while (!stack.empty()) {

		// current StackElement for processing
		StackElement currSE = stack.back();

		// pop the selected StackElement
		stack.pop_back();

		// temporary start and end for easier reading
		int s = currSE.start;
		int e = currSE.end;

		// calculate the sum using the accomulation array
		BigDecimal *sum = new BigDecimal(acc[e + 1] - acc[s]);

		// create the temporary element
		TreeNode *tNode = new TreeNode(s, e, sum);

		// set the parent's child to the temporary node
		if (currSE.side == RIGHT) {
			currSE.parent->setRight(tNode);
		} else {
			currSE.parent->setLeft(tNode);
		}

		// size of the segment of the current node
		int len = currSE.end - currSE.start;

		// push for creating the element's child
		if (len > 0) {
			stack.push_back(StackElement(tNode, RIGHT, currSE.start + len / 2 + 1, currSE.end));
			stack.push_back(StackElement(tNode, LEFT, currSE.start, currSE.start + len / 2));
		}

		// remove unused BigDecimal
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

	// no need for copy if the values are same
	if (this != &rSearchTree) {

		// free the past state
		free_tree();

		// a temporary stack for emulating recursion
		std::vector<RSearchTree::StackElement> stack;

		// create the root
		root = new TreeNode(*rSearchTree.root);

		// push the root's children if they exist
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

		// main loop
		while (!stack.empty()) {

			// get the current element
			RSearchTree::StackElement currSE = stack.back();
			stack.pop_back();

			// push the current element's children if they exist and copy them to this
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

std::vector<TreeNode *> RSearchTree::intervalNodes(int start, int end) const {

	// temporary return and stack emulator
	std::vector<TreeNode *> stack, ret;
	stack.push_back(root);

	// main loop
	while (!stack.empty()) {

		// get the current node
		TreeNode *tNode = stack.back();
		stack.pop_back();

		if (tNode->covers(start, end)) {

			// if the node is contained, add it to the return value
			ret.push_back(tNode);

		} else {

			// add children if they exist
			if (tNode->getRight() != nullptr) {
				stack.push_back(tNode->getRight());
			}
			if (tNode->getLeft() != nullptr) {
				stack.push_back(tNode->getLeft());
			}

		}

	}

	return ret;
}

BigDecimal RSearchTree::intervalSum(int start, int end) const {

	// array to store the intervalNodes
	auto arr = intervalNodes(start, end);

	// initialize the sum
	BigDecimal sum("0");

	// loop through the nodes and add the elements
	for (auto &item : arr) {
		sum += item->getVal();
	}

	// return the sum
	return sum;
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

RSearchTree::StackElement::StackElement(TreeNode *parent, bool side, int start, int end) : parent(parent),
																						   start(start),
																						   end(end), side(side) {
}
