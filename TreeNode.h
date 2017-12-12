#ifndef DZ2_TREENODE_H
#define DZ2_TREENODE_H


#include "BigDecimal.h"

/**
 * @brief Class for storing nodes in a segment tree
 */

class TreeNode {
public:
	/**
	 * @brief Main constructor
	 * @param start start of the interval beneath the node
	 * @param end end of the interval beneath the node
	 * @param val sum of all elements beneath the node
	 */
	TreeNode(int start, int end, BigDecimal *val);

	/**
	 * @brief Copy constructer
	 * @param treeNode the node to be copied
	 */
	TreeNode(const TreeNode &treeNode);

	/**
	 * @brief Standard destructor. Does nothing, since there are no dynamic fields
	 */
	virtual ~TreeNode();

	/**
	 * @brief Setter for the left child
	 * @param left new left node
	 */
	void setLeft(TreeNode *left);

	/**
	 * @brief Setter for the right child porn
	 * @param left new left node
	 */
	void setRight(TreeNode *right);

	/**
	 * @brief Getter for the left child
	 * @return pointer to the left child
	 */
	TreeNode *getLeft() const;

	/**
	 * @brief Getter for the right child
	 * @return pointer to the right child
	 */
	TreeNode *getRight() const;

	/**
	 * @brief Getter for the start of the interval
	 * @return start of the interval
	 */
	int getStart() const;

	/**
	 * @brief Getter for the end of the interval
	 * @return end of the interval
	 */
	int getEnd() const;

	/**
	 * @brief Checks whether the interval [start, end] covers the interval of the node
	 * @param start start of the interval to be checked against
	 * @param end end of the interval to be checked against
	 * @return true iff the interval of the node is contained in [start, end]
	 */
	bool covers(int start, int end);

	/**
	 * @brief Getter for the node's sum
	 * @return the sum of all leaves beneath the node
	 */
	const BigDecimal &getVal() const;

private:

	// Sum of all leaves beneath the node
	BigDecimal val;

	// Start and end of the interval that is covered by a node
	int start, end;

	// Left and right child of a node
	TreeNode *left, *right;

	/**
	 * @brief function for std::ostream operator<< overloading
	 * @return std::ostream that can print a TreeNode
	 */
	friend std::ostream &operator<<(std::ostream &, const TreeNode &);
};


#endif //DZ2_TREENODE_H
