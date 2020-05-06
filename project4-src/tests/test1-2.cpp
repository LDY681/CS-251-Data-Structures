#include <random>
#include <RBTree.h>
#include "validate.h"
using namespace std;

int main() {
	// Initialize random number generator (with a fixed seed)
	mt19937 rng(13579u);
	uniform_int_distribution<> randInt(0, 1000000);
	uniform_int_distribution<char> randChar('a', 'z');

	// Create a tree, insert a large number of elements
	int n = 500;
	RBTree<int, char> rbt;
	for (int i = 0; i < n; i++) {
		rbt.insert(randInt(rng), randChar(rng));
	}

	return !(validate(rbt) && rbt.size() == n);
}
