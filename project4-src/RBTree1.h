#ifndef PROJ4_RBTREE_H
#define PROJ4_RBTREE_H

#include <assert.h>
#include "Node.h"
#include <iostream>
#include <string>
#include <queue>

using namespace std;

//TODO: check if implementation is correct
template <typename Key, typename Element>
class RBTree {
	private:
		// Add class members here
		//Node<Key, Element> *root;
		//Node<Key, Element> *result;	//search result
		//Node<Key, Element> *tras;	//the node that we transversal to 

	public:
		size_t treesize;
		Node<Key, Element> *m_nullNode;
		Node<Key, Element> *m_root;
		// Implement each of these methods
		RBTree() {
			this->m_nullNode = new Node<Key, Element>();
			this->m_root = m_nullNode;
			this->m_nullNode->right = this->m_root;
			this->m_nullNode->left = this->m_root;
			this->m_nullNode->parent = this->m_root;
			this->m_nullNode->col = BLACK;
			treesize = 0;

			//root = NULL;
			//tras = root;
			//result = NULL;
		}

		void inorder(ostream& out) const;
		//void inorderHelper(Node *root) const;
		void inorderhelper(ostream& out, Node<Key, Element> * node) const;
		void levelOrder(ostream& out) const;
		void levelOrderhelper(ostream& out, Node<Key, Element> * node) const;

		void insert(const Key& k, const Element& e);
		void InsertFixUp(Node<Key, Element>* node);
		bool RotateRight(Node<Key, Element>* node);
		bool RotateLeft(Node<Key, Element>* node);
		void fixviolation(Node<Key, Element> * pt);
		
		Node<Key, Element>* search(const Key& k);
		void printsearch(Node<Key, Element> * node, const Key& k);
		void del(const Key& k);

		size_t size() const;
		Node<Key, Element>* getRoot();
		//Node<Key, Element>* ggrandparent(Node<Key, Element> *n);
		////sibling vs uncle, uncle is when you also have a grandparent
		//Node<Key, Element>* ssibling(Node<Key, Element> *n);
		//Node<Key, Element>* uuncle(Node<Key, Element> *n);
		//Node<Key, Element>* pparent(Node<Key, Element> *n);
		
};

//Function to fix violation 
template <typename Key, typename Element>
void RBTree<Key, Element>::fixviolation(Node<Key, Element> * pt) {

	/*
	Node<Key, Element> * parent = NULL;
	Node<Key, Element> * grandparent = NULL;
	Node<Key, Element> * uncle = NULL;

	while ((pt != root) && (pt->currColor != BLACK) && (pparent(pt)->currColor == RED)) {
		parent = pparent(pt);
		grandparent = ggrandparent(pt);
		uncle = uuncle(pt);

		//CASE: uncle is red, recolor
		if (uncle != NULL && uncle->currColor == RED) {
			parent->currColor = uncle->currColor = BLACK;
			grandparent->currColor = RED;
			pt = grandparent;
		}
		//CASE: uncle is black
		if (uncle == NULL || uncle->currColor == BLACK) {
			//CASE triangle
			if ((parent == grandparent->right && pt == parent->left) || (parent == grandparent->left && pt == parent->right)) {
				//CASE left rotation on parent
				if (parent == grandparent->left) {
					cout << "We are going to operate left rotation of triangle, left case: " << endl;
					cout << "Original Grandparent: " << grandparent->currKey << endl;
					cout << "Original Parent: " << parent->currKey << endl;
					cout << "Original Pt: " << pt->currKey << endl;
					grandparent->left = pt;
					pt->parent = grandparent;
					Node<Key, Element> * oldptleft = pt->left;
					pt->left = parent;
					parent->parent = pt;
					parent->right = oldptleft;
					pt = parent;
					cout << "Now new orders are: " << endl;
					cout << "Grandparent: " << ggrandparent(pt)->currKey << endl;
					cout << "parent: " << pparent(pt)->currKey << endl;
					cout << "Pt: " << pt->currKey << endl;
				}
				else {
					//CASE right rotation on parent
					cout << "We are going to operate right rotation of triangle, left case: " << endl;
					cout << "Original Grandparent: " << grandparent->currKey << endl;
					cout << "Original Parent: " << parent->currKey << endl;
					cout << "Original Pt: " << pt->currKey << endl;
					grandparent->right = pt;
					pt->parent = grandparent;
					Node<Key, Element> * oldptright = pt->right;
					pt->right = parent;
					parent->parent = pt;
					parent->left = oldptright;
					pt = parent;
					cout << "Now new orders are: " << endl;
					cout << "Grandparent: " << ggrandparent(pt)->currKey << endl;
					cout << "parent: " << pparent(pt)->currKey << endl;
					cout << "Pt: " << pt->currKey << endl;
				}
			}
			else {
				//CASE LINE
					//CASE right line
				if (parent == grandparent->right) {
					Node<Key, Element> * oldptlt = parent->left;
					parent->left = grandparent;
					parent->parent = grandparent->parent;
					grandparent->parent = parent;
					grandparent->right = oldptlt;
					parent->currColor = BLACK;
					if (grandparent->currColor == RED) {
						grandparent->currColor == BLACK;
					}
					else {
						grandparent->currColor == RED;
					}
					pt = parent;
				}
				//CASE left line
				else{
					Node<Key, Element> * oldptrt = parent->right;
					parent->right = grandparent;

					//CASE: if grandparent is root
					if (grandparent == root) {
						parent = root;
					}
					else {
						//CASE is grandparent is left of grandgrandparent
						if (grandparent->parent->left = grandparent) {
							grandparent->parent->left = parent;
						}
						else {
						//CASE if grandparent is right of grandparent
							grandparent->parent->right = parent;
						}
						parent->parent = grandparent->parent;
					}
					grandparent->parent = parent;
					grandparent->left = oldptrt;
					parent->currColor = BLACK;
					if (grandparent->currColor == RED) {
						grandparent->currColor == BLACK;
					}
					else{
						grandparent->currColor == RED;
					}
					pt = parent;
				}
			}
		}
	}
	*/
}

// Function to insert a new node with given data
template <typename Key, typename Element>
void RBTree<Key, Element>::insert(const Key& k, const Element& e) {
	Node<Key, Element>* insert_point = m_nullNode;
	Node<Key, Element>* index = m_root;
	while (index != m_nullNode){	
		insert_point = index;
		if (k<index->key){
			index = index->left;
		}
		else{ //(k>index->key)
			index = index->right;
		}
	}
	Node<Key, Element>* insert_node = new Node<Key, Element>();
	insert_node->key = k;
	insert_node->ele = e;
	insert_node->col = RED;
	insert_node->right = m_nullNode;	
	insert_node->left = m_nullNode;	

	if (insert_point == m_nullNode)  {	//if empty tree
		m_root = insert_node;
		m_root->parent = m_nullNode;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		m_nullNode->parent = m_root;
		treesize++;
	}
	else{
		if (k < insert_point->key){
			insert_point->left = insert_node;
		}
		else{
			insert_point->right = insert_node;
		}
		insert_node->parent = insert_point;
	}
	treesize++;
	InsertFixUp(insert_node);   

	//if tree is empty, make root node 
	//if (root == null){
	//	root = new node<key, element>();
	//	root->currele = e;
	//	root->currkey = k;
	//	root->currcolor = black;
	//	root->left = null;
	//	root->right = null;
	//	tras = root;
	//	if insert successful, size++;
	//	treesize++;
	//}
	//else {
	//	if (tras == null){
	//		tras = new node<key, element>();
	//		tras->currele = e;
	//		tras->currkey = k;
	//		tras->currcolor = red;
	//		tras->left = null;
	//		tras->right = null;
	//		treesize++;
	//		return;
	//	}
	//	else if (k < tras->currkey) {
	//		node<key, element> *oldtras = tras;
	//		tras = tras->left;
	//		insert(k, e);
	//		tras->parent = oldtras;
	//		tras->parent->left = tras;
	//	}
	//	else{
	//		node<key, element> *oldtras = tras;
	//		tras = tras->right;
	//		insert(k, e);
	//		tras->parent = oldtras;
	//		tras->parent->right = tras;
	//	}


	//	if (tras->parent != root) {	//make sure we do have grandparent
	//		fixviolation(tras);
	//	}
	//}
	//tras = root;
}

template <typename Key, typename Element>
void RBTree<Key, Element>::InsertFixUp(Node<Key, Element>* node) {
	while (node->parent->col == RED)
	{
		if (node->parent == node->parent->parent->left)   //CASEA:parent is left of grand 
		{
			Node<Key, Element>* uncle = node->parent->parent->right;
			if (uncle->col == RED)   //CASE1: uncle is red   
			{
				node->parent->col = BLACK;
				uncle->col = BLACK;
				node->parent->parent->col = RED;
				node = node->parent->parent;
			}
			else if (uncle->col == BLACK)  //CASE2: uncle is black   
			{
				if (node == node->parent->right) //right child of parent    
				{
					node = node->parent;
					RotateLeft(node);
				}
				//else                 //CASE3£ºblack unvle and left child   
				//{    
				node->parent->col = BLACK;
				node->parent->parent->col = RED;
				RotateRight(node->parent->parent);
				//}  
			}
		}
		else //CASEB:parent is right of grand  
			 //15 else (same as then clause with "right" and "left" exchanged)    
		{
			Node<Key, Element>* uncle = node->parent->parent->left;
			if (uncle->col == RED)
			{
				node->parent->col = BLACK;
				uncle->col = BLACK;
				uncle->parent->col = RED;
				node = node->parent->parent;
			}
			else if (uncle->col == BLACK)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RotateRight(node);     //  
				}
				//else    
				//{    
				node->parent->col = BLACK;
				node->parent->parent->col = RED;
				RotateLeft(node->parent->parent);   //¡£    
													//}    
			}
		}
	}
	m_root->col = BLACK;
}


template <typename Key, typename Element>
bool RBTree<Key, Element>::RotateLeft(Node<Key, Element>* node) {
	if (node == m_nullNode || node->right == m_nullNode)
	{
		return false;//can't rotate    
	}
	Node<Key, Element>* lower_right = node->right;
	lower_right->parent = node->parent;
	node->right = lower_right->left;
	if (lower_right->left != m_nullNode)
	{
		lower_right->left->parent = node;
	}
	if (node->parent == m_nullNode) //rotate node is root    
	{
		m_root = lower_right;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		//m_nullNode->parent = m_root;    
	}
	else
	{
		if (node == node->parent->left)
		{
			node->parent->left = lower_right;
		}
		else
		{
			node->parent->right = lower_right;
		}
	}
	node->parent = lower_right;
	lower_right->left = node;
}

template <typename Key, typename Element>
bool RBTree<Key, Element>::RotateRight(Node<Key, Element>* node) {
	if (node == m_nullNode || node->left == m_nullNode)
	{
		return false;//can't rotate    
	}
	Node<Key, Element>* lower_left = node->left;
	node->left = lower_left->right;
	lower_left->parent = node->parent;
	if (lower_left->right != m_nullNode)
	{
		lower_left->right->parent = node;
	}
	if (node->parent == m_nullNode) //node is root    
	{
		m_root = lower_left;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		//m_nullNode->parent = m_root;    
	}
	else
	{
		if (node == node->parent->right)
		{
			node->parent->right = lower_left;
		}
		else
		{
			node->parent->left = lower_left;
		}
	}
	node->parent = lower_left;
	lower_left->right = node;
}


// Function to search a node with given data
template <typename Key, typename Element>
Node<Key, Element>* RBTree<Key, Element>::search(const Key& k) {
	Node<Key, Element>* index = m_root;
	while (index != m_nullNode){
		if (k<index->key){
			index = index->left;  
		}
		else if (k>index->key){
			index = index->right; 
		}
		else{
			break;
		}
	}
	if (index == m_nullNode) {
		return NULL;
	}
	return index;
	//return NULL;
	//result = NULL;
	//printsearch(root, k);
	//return result;
}

template <typename Key, typename Element>
void RBTree<Key, Element>::printsearch(Node<Key, Element> * node, const Key& k) {
	
	//return;
	//if (result != NULL) {
	//	return;
	//}
	//if (node == NULL) {
	//	return;
	//}
	// first recur on left child 
	//printsearch(node->left, k);

	// then print the data of node 
	//if (node->currKey == k) {
	//	result = node;
	//	return;
	//}

	// now recur on right child 
	//printsearch(node->right, k);
}

// Function to do inorder traversal
template <typename Key, typename Element>
void RBTree<Key, Element>::inorder(ostream& out) const {
	inorderhelper(out, m_root);
	return;
}

template <typename Key, typename Element>
void RBTree<Key, Element>::inorderhelper(ostream& out, Node<Key, Element> * node) const{
	
	if (node == m_nullNode) {
		return;
	}
	//first recur on left child
	inorderhelper(out, node->left);

	//then print the data of node 
	//cout << node->key << endl;
	out << node->key << endl;
	out << node->ele << endl;
	out  << endl;
	//now recur on right child 
	inorderhelper(out, node->right);
}

// Function to perform level-order traversal
template <typename Key, typename Element>
void RBTree<Key, Element>::levelOrder(ostream& out) const {
	levelOrderhelper(out, m_root);
	return;
}

template <typename Key, typename Element>
void RBTree<Key, Element>::levelOrderhelper(ostream& out, Node<Key, Element> * node) const {
	if (node == m_nullNode) {
		return;
	}

	std::queue<Node<Key, Element> * > q;
	q.push(node);

	while (!q.empty())
	{
		Node<Key, Element> *temp = q.front();
		out << temp->key << endl;
		out << temp->ele << endl;
		out << endl;

		q.pop();

		if (temp->left != m_nullNode)
			q.push(temp->left);

		if (temp->right != m_nullNode)
			q.push(temp->right);
	}

}

// Function to return the number of nodes in the RBTree
template <typename Key, typename Element>
size_t RBTree<Key, Element>::size() const { 
	return treesize-1;
}

// Function to return a pointer to the root of the RBTree
template <typename Key, typename Element>
Node<Key, Element>* RBTree<Key, Element>::getRoot() { 
	return m_root; 
}

// Function to delete a node with given data
template <typename Key, typename Element>
void RBTree<Key, Element>::del(const Key& k) {

	//if deletion successful, size--;
}


//Fucntion to find grandparent, abort if no grandparent
//template <typename Key, typename Element>
//Node<Key, Element>* RBTree<Key, Element>::ggrandparent(Node<Key, Element> *n) {
//	assert(n != NULL);
//	assert(n->parent != NULL);
//	assert(n->parent->parent != NULL);
//	return n->parent->parent;
//}
////Fucntion to find sibling, abort if no sibling
//template <typename Key, typename Element>
//Node<Key, Element>* RBTree<Key, Element>::ssibling(Node<Key, Element> *n) {
//	assert(n != NULL);
//	assert(n->parent != NULL);
//	if (n == n->parent->left) {
//		return n->parent->right;
//	}
//	else {
//		return n->parent->left;
//	}
//}
////Fucntion to find uncle, abort if no uncle
//template <typename Key, typename Element>
//Node<Key, Element>* RBTree<Key, Element>::uuncle(Node<Key, Element> *n) {
//	assert(n != NULL);
//	assert(n->parent != NULL);
//	assert(n->parent->parent != NULL);
//	return ssibling(n->parent);
//}
////Fucntion to find parent, abort if no parent
//template <typename Key, typename Element>
//Node<Key, Element>* RBTree<Key, Element>::pparent(Node<Key, Element> *n) {
//	assert(n != NULL);
//	assert(n->parent != NULL);
//	return n->parent;
//}

// The following functions have been provided for you, and do not
// need to be modified:
// Output stream operator overload -- writes the contents of the
// entire RBTree to the specified output stream, using an in-order
// traversal. Note that there must be a similar operator overload
// for Key and Element types in order for this to compile.
// Example usage:
//		RBTree<K,E> rbt;
//		cout << rbt << endl;
template <typename Key, typename Element>
ostream& operator<<(ostream& out, const RBTree<Key, Element>& rbtree) {
	out << rbtree.size() << endl;
	rbtree.inorder(out);
	return out;
}

// Input stream operator overload -- reads the contents of an RBTree
// from the specified input stream, inserting each Node as it is
// read. Note that there must be a similar operator overload for Key
// and Element types in order for this to compile.
// Example usage:
//		RBTree<K,E> rbt;
//		cin >> rbt;
template <typename Key, typename Element>
istream& operator>>(istream& in, RBTree<Key, Element>& rbtree) {
	// Clear existing contents, if any
	rbtree = RBTree<Key, Element>();

	// Read in the number of elements to read
	size_t size;
	in >> size;
	for (size_t i = 0; i < size; i++) {
		// Read in each node as it appears in the stream
		Node<Key, Element> n;
		in >> n;
		// Insert the node into the RBTree
		rbtree.insert(n.getKey(), n.getElement());
	}

	return in;
}

#endif //PROJ4_RBTREE_H
