#include <iostream>
#include <random>
#include <RBTree.h>
#include "validate.h"
using namespace std;

int main() {
	// Initialize random number generator (with a fixed seed)
	mt19937 rng(1u);
	uniform_int_distribution<> randInt(0, 8000);
	exponential_distribution<float> expDistr(3.5);

	// Create a tree, insert a small number of elements
	int n = 10;
	// Set aside a specific key,element pair
	int k = randInt(rng);
	float e = expDistr(rng);
	RBTree<int, float> rbt;
	for (int i = 0; i < n; i++) {
		if (i == 5)
			// Insert a specific key,element
			rbt.insert(k, e);
		else
			rbt.insert(randInt(rng), expDistr(rng));
	}

	// Search for the one we know about
	Node<int, float>* node = rbt.search(k);

	return !(validate(rbt) && node != NULL &&
		node->getKey() == k && node->getElement() == e);
}
