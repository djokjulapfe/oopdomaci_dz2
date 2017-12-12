#ifndef DZ2_RSEARCHTREE_H
#define DZ2_RSEARCHTREE_H

#include <vector>
#include "TreeNode.h"

// TODO: define LEFT and RIGHT as an enum

#define LEFT true
#define RIGHT false

class RSearchTree {
public:
	RSearchTree(std::vector<BigDecimal *> &values);

	~RSearchTree();

	RSearchTree(const RSearchTree &rSearchTree);

	RSearchTree &operator=(const RSearchTree &rSearchTree);

	std::vector<TreeNode *> intervalNodes(int start, int end);

	BigDecimal intervalSum(int start, int end);

private:
	TreeNode *root;

	friend std::ostream &operator<<(std::ostream &, const RSearchTree &);

	class StackElement {
	public:
		TreeNode *parent;
		int start, end;
		bool side;

		StackElement(TreeNode *parent, bool side, int start, int end);

	private:
	};
};


#endif //DZ2_RSEARCHTREE_H
