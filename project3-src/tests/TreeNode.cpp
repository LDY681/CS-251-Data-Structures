#include <iostream>
#include "TreeNode.h"

#include <string>


TreeNode::TreeNode(unsigned char val, unsigned frequency)
{
	//TODO: is this and TreeNode:: doing samely£¿
	this->val = val;
	TreeNode::frequency = frequency;
	left = right = NULL;
}

unsigned TreeNode::getFrequency()
{
	/*UPDATE
	if (this == 0) {
		return 0;
	}*/
	return frequency;
}

unsigned TreeNode::getVal()
{
	/*UPDATE
	if (this == 0) {
		return 0;
	}*/
	return val;
}

//TODO: 
bool TreeNode::isLeafNode() {
	/*UPDATE
	if (this == 0) {
	return 0;
	}*/

	if (this->left == NULL && this->right == NULL) {
		return true;
	}
	return false;
}

//TODO:
void TreeNode::join(TreeNode * left, TreeNode * right) {
	this->left = left;
	this->right = right;
}

//TODO:
TreeNode* TreeNode::getLeft() {
	/*UPDATE
	if (this == 0) {
	return 0;
	}*/
	if (this->left != NULL) {
		return this->left;
	}
	return NULL;
}

//TODO:
TreeNode* TreeNode::getRight() {
	/*UPDATE
	if (this == 0) {
	return 0;
	}*/
	if (this->right != NULL) {
		return this->right;
	}
	return NULL;
}