#ifndef DZ2_RSEARCHTREE_H
#define DZ2_RSEARCHTREE_H

#include <vector>
#include "TreeNode.h"

// TODO: define LEFT and RIGHT as an enum

#define LEFT true
#define RIGHT false

/**
 * @brief Class for storing a segment tree
 */

class RSearchTree {
public:
	/**
	 * @brief Main constructor
	 * @param values array of values for initializing the segment tree
	 */
	RSearchTree(std::vector<BigDecimal *> &values);

	/**
	 * @brief Default destructor that deletes all the nodes that make up the tree
	 */
	~RSearchTree();

	/**
	 * @brief Copy constructor
	 * @param rSearchTree the tree to be copied from
	 */
	RSearchTree(const RSearchTree &rSearchTree);

	/**
	 * @brief Assignment operator that copies a value
	 * @param rSearchTree the tree to be copied from
	 * @return *this
	 */
	RSearchTree &operator=(const RSearchTree &rSearchTree);

	/**
	 * @brief Determines the nodes that encompass an interval
	 * @param start start of the interval to be checked
	 * @param end end of the interval to be checked
	 * @return the minimal number of nodes required to encompass the interval
	 */
	std::vector<TreeNode *> intervalNodes(int start, int end) const;

	/**
	 * @brief Calculates the sum of elements in an interval
	 * @param start start of the interval to be checked
	 * @param end end of the interval to be checked
	 * @return the sum of elements in an interval
	 */
	BigDecimal intervalSum(int start, int end) const;

private:

	/**
	 * @brief Helper function that deletes all nodes from a tree
	 */
	void free_tree();

	// Pointer to the root of the tree
	TreeNode *root;

	/**
	 * @brief function for std::ostream operator<< overloading
	 * @return std::ostream that can print a RSearchTree
	 */
	friend std::ostream &operator<<(std::ostream &, const RSearchTree &);

	/**
	 * @brief Helper class for the tree construction
	 */
	class StackElement {
	public:
		// Pointer to a TreeNode that represents a parent of the next node to be added
		TreeNode *parent;

		// Start and end of the interval of the parent
		int start, end;

		// Stores whether the next node should be the left or right child of parent
		bool side;

		/**
		 * @brief Helper constructor
		 * @param parent initial value of the parent
		 * @param side initial value of the side
		 * @param start initial value of the start
		 * @param end initial value of the end
		 */
		StackElement(TreeNode *parent, bool side, int start, int end);

	private:
	};
};


#endif //DZ2_RSEARCHTREE_H
