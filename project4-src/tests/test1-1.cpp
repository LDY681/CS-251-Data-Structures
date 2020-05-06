#include <random>
#include <RBTree.h>
#include "validate.h"
using namespace std;

int main() {
	// Initialize random number generator (with a fixed seed)
	mt19937 rng(5555u);
	uniform_int_distribution<> randInt(0, 1000);

	// Create a tree, insert a small number of elements
	RBTree<int, int> rbt;
	rbt.insert(randInt(rng), randInt(rng));
	rbt.insert(randInt(rng), randInt(rng));
	rbt.insert(randInt(rng), randInt(rng));

	return !(validate(rbt) && rbt.size() == 3);
}
