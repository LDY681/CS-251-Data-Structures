#include <iostream>
#include <random>
#include <RBTree.h>
#include "validate.h"
using namespace std;

int main() {
	// Initialize random number generator (with a fixed seed)
	mt19937 rng(250386u);
	uniform_int_distribution<> randInt(-1000000, 1000000);
	uniform_real_distribution<float> randFloat(0.0, 10.0);

	// Create a tree, insert a large-ish number of elements
	int n = 100;
	RBTree<int, float> rbt;
	for (int i = 0; i < n; i++) {
		rbt.insert(randInt(rng), randFloat(rng));
	}

	// Make sure tree is valid
	if (!validate(rbt)) return 1;

	// Output the inorder traversal
	rbt.inorder(cout);

	return 0;
}
