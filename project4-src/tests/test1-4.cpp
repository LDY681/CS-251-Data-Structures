#include <iostream>
#include <random>
#include <RBTree.h>
#include "validate.h"
using namespace std;

int main() {
	// Initialize random number generator (with a fixed seed)
	mt19937 rng(72464u);
	uniform_int_distribution<> randInt(-280000, 0);
	bernoulli_distribution randBool(0.4);

	// Create a tree, insert a large-ish number of elements
	int n = 144;
	RBTree<int, bool> rbt;
	for (int i = 0; i < n; i++) {
		rbt.insert(randInt(rng), randBool(rng));
	}

	// Make sure tree is valid
	if (!validate(rbt)) return 1;

	// Output the level-order traversal
	rbt.levelOrder(cout);

	return 0;
}
