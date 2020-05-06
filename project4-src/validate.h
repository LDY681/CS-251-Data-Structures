#ifndef VALIDATE_H
#define VALIDATE_H

#include <sstream>
#include <vector>
#include <algorithm>
#include <RBTree.h>

// Test that the root is black
template <typename K, typename E>
bool rootProp(Node<K,E>* root) {
	if (root == NULL) return true;
	return root->getColor() == BLACK;
}

// Test that both children of each red node are black
template <typename K, typename E>
bool internalProp(Node<K,E>* root) {
	if (root == NULL) return true;

	Node<K,E>* l = root->getLeft();
	Node<K,E>* r = root->getRight();
	if (root->getColor() == RED) {
		if ((l != NULL && l->getColor() == RED) ||
			(r != NULL && r->getColor() == RED))
			return false;
	}

	return internalProp(l) && internalProp(r);
}

// Test that all leaves have the same black depth
template <typename K, typename E>
bool depthProp(Node<K,E>* root) {
	if (root == NULL) return true;

	Node<K,E>* l = root->getLeft();
	Node<K,E>* r = root->getRight();
	// If both children are leaves, this subtree is valid
	if (l == NULL && r == NULL)
		return true;
	else if (l == NULL) {
		// If left is a leaf but right is non-leaf and black,
		// black depth is violated
		if (r->getColor() == BLACK)
			return false;
		else {
			Node<K,E>* rl = r->getLeft();
			Node<K,E>* rr = r->getRight();
			// Left is a leaf, right is non-leaf and red,
			// but one of right's children isn't a leaf --
			// black depth is violated
			if (rl != NULL || rr != NULL)
				return false;
			// Left is leaf, right is non-leaf red, right's
			// children are both leaves, so black depth isn't violated
			return true;
		}
	} else if (r == NULL) {
		// Symmetric to above
		if (l->getColor() == BLACK)
			return false;
		else {
			Node<K,E>* ll = l->getLeft();
			Node<K,E>* lr = l->getRight();
			if (ll != NULL || lr != NULL)
				return false;
			return true;
		}
	// Both children are non-leaf, so recurse
	} else
		return depthProp(l) && depthProp(r);
}

// Test that all keys are in the correct order
template <typename K, typename E>
bool ordered(RBTree<K,E>& rbt) {
	// Write the inorder traversal to stringstream
	stringstream ss;
	rbt.inorder(ss);

	// Extract each key
	vector<K> keys;
	for (int i = 0; i < rbt.size(); i++) {
		K k; E e;
		ss >> k >> e;
		keys.push_back(k);
	}

	return is_sorted(keys.begin(), keys.end());
}

// Test all Red-Black properties (except external property, which
// is implied)
template <typename K, typename E>
bool validate(RBTree<K,E>& rbt) {
	if (!rootProp<K,E>(rbt.getRoot())) {
		cout << "Root is not black!" << endl;
		return false;
	}
	if (!internalProp<K,E>(rbt.getRoot())) {
		cout << "A double red was found!" << endl;
		return false;
	}
	if (!depthProp<K,E>(rbt.getRoot())) {
		cout << "All leaves do not have the same black-depth!" << endl;
		return false;
	}
	if (!ordered<K,E>(rbt)) {
		cout << "Tree is not ordered!" << endl;
		return false;
	}
	return true;
}

#endif
