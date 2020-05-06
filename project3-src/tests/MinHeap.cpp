#include <iostream>
#include <climits>
#include "MinHeap.h"



//implement the methods in MinHeap.h

MinHeap::MinHeap()
{
	size = 0;
	capacity = 9999;
	array = new TreeNode*[capacity];	
}

//TODO: because we dont have main, we may need this to call this function
void MinHeap::downHeapify(MinHeap *minHeap, int i) {
	int smallest = i;
	int left = 2 * i + 1;	//so we can get a tree of 0 |1 2|3 4 5 6| 7 8 9 10 11 12 13 14| and so on
	int right = 2 * i + 2;

	//handle left and right separately in case there is no right or left
	if (left < minHeap->size && minHeap->array[left]->getFrequency() < minHeap->array[smallest]->getFrequency() ) {
		smallest = left;
	}

	if (right < minHeap->size && minHeap->array[right]->getFrequency() < minHeap->array[smallest]->getFrequency() ) {
		smallest = right;
	}

	if (smallest != i) {	//if left or right of idx node is the smallest
		//swap the smallest with node of current index
		TreeNode* t = minHeap->array[smallest];
		minHeap->array[smallest] = minHeap->array[i];	//not swap the value, we need to actually swap the pointer so no *
		minHeap->array[i] = t;
		downHeapify(minHeap, smallest);	//recurse until heap is heapified
	}

}

void MinHeap::insert(TreeNode * val)
{
	//TODO:enlarge array if max reached
	if (size == capacity - 1) {
		capacity = capacity * 2;
		TreeNode **newarray = new TreeNode*[capacity];
		int j;
		for (j = 0; j < size; j++) {
			newarray[j] = array[j];
		}
		array = newarray;
	}

	this->size++;
	int i = this->size - 1;

	//up heapify
	while (i && val->getFrequency() < this->array[(i - 1) / 2]->getFrequency()) {	//when child is less than parent// when greater or equal ->end
		this->array[i] = this->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	this->array[i] = val;
}

TreeNode * MinHeap::removeMin()
{
	if (size == 0) {
		return NULL;
	}
	TreeNode* min = this->array[0];
	this->array[0] = this->array[this->size - 1];	//replace top with last (smallest) element
	this->size--;
	downHeapify(this, 0);	//make sure last is the smallest or we heapify
	return min;
}

TreeNode * MinHeap::top() {
	return this->array[0];
}

int MinHeap::getSize()
{
	return this->size;
}

MinHeap::~MinHeap() {
	return;
}



