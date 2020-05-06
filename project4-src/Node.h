#ifndef NODE_H
#define NODE_H
#include "RBTree.h"
#include <iostream>
using namespace std;

enum color {RED, BLACK};

//TODO: check if each implementation is correct
template <typename Key, typename Element>
class Node {
	private:
	public:
		Key key;
		Element ele;
		Node<Key, Element> * parent;
		Node<Key, Element> * left;
		Node<Key, Element> * right;
		enum color col;

		// Implement each of these methods
		Node() {
			this->parent = this->left = this->right = NULL;
			//this->currColor = RED;
		}
		Node(Key currKey, Element currEle) {
			this->parent = this->left = this->right = NULL;
			this->currKey = currKey;
			this->currEle = currEle;
			//this->currColor = RED;
		}

	// These implementations are only to get the skeleton
	// code to compile. Ignore the warnings they generate
	// until you replace their implementations with your own
		const Key& getKey() const { 
			return this->key;
			//Key k; return k; 
		}
		const Element& getElement() const { 
			return this->ele;
			//Element e; return e; 
		}
		Element& getElement() { 
			return this->ele;
			//Element e; return e; 
		}

		color getColor() const { 
			return this->col;
			//return RED; 
		}
		Node* getParent() { 
			return this->parent;
			//return NULL; 
		}
		Node* getLeft() { 
			if (this->left ==this->right) {
				return NULL;
			}
			return this->left;
			//return NULL; 
		}
		Node* getRight() { 
			if (this->left == this->right) {
				return NULL;
			}
			return this->right;
			//return NULL; 
		}

		void setKey(const Key& k) {
			this->key = k;
		}
		void setElement(const Element& e) {
			this->ele = e;
		}
		void setColor(color c) {
			this->col = c;
		}	
};



// The following functions have been provided for you, and do not
// need to be modified:


// Output stream operator overload -- writes the contents of a
// Node to the specified output stream. Note that there must be
// a similar operator overload for Key and Element types in
// order for this to compile.
// Example usage:
//		Node<K,E> n;
//		cout << n << endl;
template <typename Key, typename Element>
ostream& operator<<(ostream& out, const Node<Key, Element>& n) {
	out << n.getKey() << endl;
	out << n.getElement() << endl;
	return out;
}

// Input stream operator overload -- reads the contents of a
// Node from the specified input stream. Note that there must be
// a similar operator overload for Key and Element types in order
// for this to compile.
// Example usage:
//		Node<K,E> n;
//		cin >> n;
template <typename Key, typename Element>
istream& operator>>(istream& in, Node<Key, Element>& n) {
	// Clear existing contents, if any
	n = Node<Key, Element>();

	Key k;
	in >> k;
	Element e;
	in >> e;
	n.setKey(k);
	n.setElement(e);

	return in;
}

#endif
