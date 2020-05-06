#include <iostream>
#include <random>
#include <RBTree.h>
#include "validate.h"
using namespace std;

int main() {
	// Initialize random number generator (with a fixed seed)
	mt19937 rng(99199u);
	uniform_int_distribution<> randInt(101, 5684721);
	uniform_int_distribution<> randInt2(-933842, -22233);

	// Create a tree, insert a medium number of elements
	int n = 33;
	RBTree<int, int> rbt;
	for (int i = 0; i < n; i++) {
		rbt.insert(randInt(rng), randInt2(rng));
	}

	// Search for a key that isn't there
	Node<int, int>* node = rbt.search(-555);

	return !(validate(rbt) && rbt.size() == n && node == NULL);
}
