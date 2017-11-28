#include "TreeNode.h"

void TreeNode::setLeft(TreeNode *left) {
	TreeNode::left = left;
}

void TreeNode::setRight(TreeNode *right) {
	TreeNode::right = right;
}

int TreeNode::getStart() const {
	return start;
}

int TreeNode::getEnd() const {
	return end;
}

TreeNode::~TreeNode() {
	delete val;
}
