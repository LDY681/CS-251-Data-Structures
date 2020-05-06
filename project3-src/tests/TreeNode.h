#ifndef TREENODE_H
#define TREENODE_H

#include <string>

using namespace std;

class TreeNode
{
	private:
		TreeNode * left;
		TreeNode * right;
		unsigned frequency;
		unsigned char val;
	public:
		
		//TreeNode();
		TreeNode(unsigned char val, unsigned frequency);
				
		//returns true if this node is a leaf node, returns false otherwise
		bool isLeafNode();

		//puts left as the left child and right as the right child of this node
		void join(TreeNode * left, TreeNode * right); 

		TreeNode * getLeft(); //returns the left child
		TreeNode * getRight(); //returns the right child

		unsigned getFrequency(); //returns frequency member variable
		unsigned getVal(); //returns val member variable
};





#endif