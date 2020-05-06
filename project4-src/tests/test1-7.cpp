#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <RBTree.h>
#include "validate.h"
using namespace std;

int main() {
	// Initialize random number generator (with a fixed seed)
	mt19937 rng(1010101u);
	uniform_int_distribution<> randInt(-30, 0xC0FFEE);
	uniform_int_distribution<> randLen(3, 10);
	uniform_int_distribution<char> randChar('a', 'z');

	// Store keys inserted into tree
	vector<int> keys;
	// Create a tree, insert a number of elements
	int n = 72;
	RBTree<int, string> rbt;
	for (int i = 0; i < n; i++) {
		// Make a random string
		int l = randLen(rng);
		string e;
		for (int j = 0; j < l; j++)
			e.push_back(randChar(rng));

		int k = randInt(rng);
		rbt.insert(k, e);
		keys.push_back(k);
	}

	// Shuffle vector of keys
	shuffle(keys.begin(), keys.end(), rng);

	// Remove half of the keys in random order
	for (int i = 0; i < n / 2; i++) {
		// Search for the key in the tree
		int k = keys.back(); keys.pop_back();
		Node<int, string>* node = rbt.search(k);
		if (node == NULL) return 1;

		// Delete the key
		node = NULL;
		rbt.del(k);

		// Make sure tree is valid after deletion
		if (!validate(rbt) || rbt.size() != keys.size())
			return 1;

		// Search for it again to make sure it was removed
		node = rbt.search(k);
		if (node != NULL)
			return 1;
	}

	// All delete operations completed successfully, return success
	return 0;
}
