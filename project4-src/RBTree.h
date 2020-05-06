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
		Node<Key, Element> *nilNode;
		Node<Key, Element> *root;
		// Implement each of these methods
		RBTree() {
			this->nilNode = new Node<Key, Element>();
			this->root = nilNode;
			this->nilNode->right = this->root;
			this->nilNode->left = this->root;
			this->nilNode->parent = this->root;
			this->nilNode->col = BLACK;
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
		void DeleteFixUp(Node<Key, Element>* node);

		Node<Key, Element>* search(const Key& k);
		void printsearch(Node<Key, Element> * node, const Key& k);
		void del(const Key& k);
		Node<Key, Element>* inherit(Node<Key, Element>*delnode);

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
	Node<Key, Element>* insert_point = nilNode;
	Node<Key, Element>* index = root;
	while (index != nilNode){
		insert_point = index;
		if (k<index->key){	//traverse left	
			index = index->left;
		}
		else{	//traverse right
			index = index->right;
		}
	}

	//Create new node object
	Node<Key, Element>* insert_node = new Node<Key, Element>();
	insert_node->key = k;
	insert_node->ele = e;
	insert_node->col = RED;
	insert_node->right = nilNode;
	insert_node->left = nilNode;

	// if its an empty tree
	if (insert_point == nilNode)  {	
		root = insert_node;
		root->parent = nilNode;
		nilNode->left = root;
		nilNode->right = root;
		nilNode->parent = root;
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
	root->col = BLACK;
}


template <typename Key, typename Element>
bool RBTree<Key, Element>::RotateLeft(Node<Key, Element>* node) {

	//if node or its right is nil, return false;
	if (node == nilNode || node->right == nilNode){
		return false;
	}

	Node<Key, Element>* lower_right = node->right;
	lower_right->parent = node->parent;
	node->right = lower_right->left;
	if (lower_right->left != nilNode){
		lower_right->left->parent = node;
	}
	if (node->parent == nilNode){	//rotate on root
		root = lower_right;
		nilNode->left = root;
		nilNode->right = root;   
	}
	else{
		if (node == node->parent->left){
			node->parent->left = lower_right;
		}
		else{
			node->parent->right = lower_right;
		}
	}
	node->parent = lower_right;
	lower_right->left = node;
}

template <typename Key, typename Element>
bool RBTree<Key, Element>::RotateRight(Node<Key, Element>* node) {
	//if node or its left is nil, return false;
	if (node == nilNode || node->left == nilNode){
		return false;  
	}

	Node<Key, Element>* lower_left = node->left;
	node->left = lower_left->right;
	lower_left->parent = node->parent;
	if (lower_left->right != nilNode)
	{
		lower_left->right->parent = node;
	}
	if (node->parent == nilNode)    
	{
		root = lower_left;
		nilNode->left = root;
		nilNode->right = root;
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
	Node<Key, Element>* index = root;
	while (index != nilNode){
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
	if (index == nilNode) {
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
	inorderhelper(out, root);
	return;
}

template <typename Key, typename Element>
void RBTree<Key, Element>::inorderhelper(ostream& out, Node<Key, Element> * node) const{
	
	if (node == nilNode) {
		return;
	}

	// recur on left child
	inorderhelper(out, node->left);

	//print node
	out << node->key << endl;
	out << node->ele << endl;
	out  << endl;

	// recur on right child 
	inorderhelper(out, node->right);
}

// Function to perform level-order traversal
template <typename Key, typename Element>
void RBTree<Key, Element>::levelOrder(ostream& out) const {
	levelOrderhelper(out, root);
	return;
}

template <typename Key, typename Element>
void RBTree<Key, Element>::levelOrderhelper(ostream& out, Node<Key, Element> * node) const {
	if (node == nilNode) {
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

		if (temp->left != nilNode)
			q.push(temp->left);

		if (temp->right != nilNode)
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
	return root; 
}


template <typename Key, typename Element>
Node<Key, Element>* RBTree<Key, Element>::inherit(Node<Key, Element>*node) {
	if (node == nilNode){
		return nilNode;
	}
	Node<Key, Element>* sc = node->right;     

	//recur till sc's left is null
	while (sc != nilNode)       
	{
		if (sc->left != nilNode){
			sc = sc->left;
		}
		else{
			break;
		}
	} 

	//if successor is null
	if (sc == nilNode)
	{
		Node<Key, Element>* temp = node->parent;
		sc = node;
		//traverse back on nil
		while (temp != nilNode && sc == temp->right)
		{
			sc = temp;
			temp = temp->parent;
		}
		sc = temp;        
	}
	return sc;
}


//TODO
// Function to delete a node with given data
template <typename Key, typename Element>
void RBTree<Key, Element>::del(const Key& k) {
	//find the element to delete first 
	Node<Key, Element>* delnode = this->search(k);

	if (delnode == nilNode){
		return;	//TODO: maybe return NULL?
	}

	//if node has double child, decide who's node's successor
	if (delnode->left != nilNode && delnode->right != nilNode){
		//TODO:
		Node<Key, Element>* sc = inherit(delnode);
		delnode->key = sc->key;
		delnode->ele = sc->ele;
		//delnode->col = sc->col;
		delnode = sc;
	}

	//TODO
	Node<Key, Element>* delnodechild;
	//delnodechild->col = RED;
	//= new Node<Key, Element>();
	if (delnode->right != nilNode){
		delnodechild = delnode->right;
	}
	else if (delnode->left != nilNode){
		delnodechild = delnode->left;
	}
	else{
		delnodechild = nilNode;
	}
	delnodechild->parent = delnode->parent;
	if (delnode->parent == nilNode)   
	{
		root = delnodechild;
		nilNode->parent = root;
		nilNode->left = root;
		nilNode->right = root;
	}
	else if (delnode == delnode->parent->right)
	{
		delnode->parent->right = delnodechild;
	}
	else
	{
		delnode->parent->left = delnodechild;
	}
	if (delnode->col == BLACK && !(delnodechild == nilNode && delnodechild->parent == nilNode)){
		DeleteFixUp(delnodechild);
	}

	treesize--;
	return;
	//if deletion successful, size--;
}

template <typename Key, typename Element>
void RBTree<Key, Element>::DeleteFixUp(Node<Key, Element>* node){
	while (node != root && node->col == BLACK)
	{

		//CASEA: node is the left child of parent
		if (node == node->parent->left)
		{
			Node<Key, Element>* brother = node->parent->right;

			//CASE1:node's brother is red
			if (brother->col == RED){
				brother->col = BLACK;
				node->parent->col = RED;
				RotateLeft(node->parent);	//rotate left on parent
			}
			//CASE2: node's brother is black
			else{
				//CASE2A: black brother and all brother children black
				if (brother->left->col == BLACK && brother->right->col == BLACK){
					brother->col = RED;
					node = node->parent;
				}
				//CASE2B: black brother and red brother child
				else if (brother->right->col == BLACK){
					brother->col = RED;
					brother->left->col = BLACK;
					RotateRight(brother);	//rotate right on brother
				}

				brother->col = node->parent->col;
				node->parent->col = BLACK;
				brother->right->col = BLACK;
				RotateLeft(node->parent);	//rotate left on parent
				node = root;   
			}
		}
		else{
			Node<Key, Element>* brother = node->parent->left;
			if (brother->col == RED){
				brother->col = BLACK;
				node->parent->col = RED;
				RotateRight(node->parent);
			}
			else{
				if (brother->left->col == BLACK && brother->right->col == BLACK){
					brother->col = RED;
					node = node->parent;
				}
				else if (brother->left->col == BLACK){
					brother->col = RED;
					brother->right->col = BLACK;
					RotateLeft(brother);
				} 
				brother->col = node->parent->col;
				node->parent->col = BLACK;
				brother->left->col = BLACK;
				RotateRight(node->parent);
				node = root; 
			}
		}
	}
	nilNode->parent = root;       
	node->col = BLACK;
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
