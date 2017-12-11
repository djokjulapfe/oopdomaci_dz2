#ifndef DZ2_RSEARCHTREE_H
#define DZ2_RSEARCHTREE_H


#include <vector>
#include "TreeNode.h"

class RSearchTree {
public:
	RSearchTree(std::vector<BigDecimal *> &values);

	RSearchTree(const RSearchTree &rSearchTree);

	RSearchTree &operator=(const RSearchTree &rSearchTree);

	std::vector<TreeNode *> intervalNodes(int start, int end);

	BigDecimal intervalSum(int start, int end);

private:
	TreeNode *root;

	friend std::ostream &operator<<(std::ostream &, const RSearchTree &);
};


#endif //DZ2_RSEARCHTREE_H
