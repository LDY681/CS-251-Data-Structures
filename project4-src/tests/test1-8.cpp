#include <iostream>
#include <RBTree.h>
#include "validate.h"
using namespace std;

int main() {
	// Create a tree
	RBTree<int, int> rbt;
	int s = 0;
	int k;

	// Insert specific elements
	rbt.insert(k = 4, 0);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 7, 1);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 12, 2);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 15, 3);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 3, 4);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 5, 5);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 14, 6);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 18, 7);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 16, 8);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;

	rbt.insert(k = 17, 9);
	if (!validate(rbt) || rbt.size() != ++s
		|| rbt.search(k) == NULL) return 1;


	// Remove specific elements
	rbt.del(k = 3);
	if (!validate(rbt) || rbt.size() != --s
		|| rbt.search(k) != NULL) return 1;

	rbt.del(k = 12);
	if (!validate(rbt) || rbt.size() != --s
		|| rbt.search(k) != NULL) return 1;

	rbt.del(k = 17);
	if (!validate(rbt) || rbt.size() != --s
		|| rbt.search(k) != NULL) return 1;

	rbt.del(k = 18);
	if (!validate(rbt) || rbt.size() != --s
		|| rbt.search(k) != NULL) return 1;

	rbt.del(k = 15);
	if (!validate(rbt) || rbt.size() != --s
		|| rbt.search(k) != NULL) return 1;

	rbt.del(k = 16);
	if (!validate(rbt) || rbt.size() != --s
		|| rbt.search(k) != NULL) return 1;


	// All operations completed successfully, return success
	return 0;
}
