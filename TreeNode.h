#ifndef DZ2_TREENODE_H
#define DZ2_TREENODE_H


#include "BigDecimal.h"

class TreeNode {
public:
	TreeNode(int start, int end, BigDecimal *val);

	TreeNode(const TreeNode &treeNode);

	virtual ~TreeNode();

	void setLeft(TreeNode *left);

	void setRight(TreeNode *right);

	TreeNode *getLeft() const;

	TreeNode *getRight() const;

	int getStart() const;

	int getEnd() const;

	bool covers(int start, int end);

private:
	BigDecimal val;
	int start, end;
	TreeNode *left, *right;

	friend std::ostream &operator<<(std::ostream &, const TreeNode &);
};


#endif //DZ2_TREENODE_H
