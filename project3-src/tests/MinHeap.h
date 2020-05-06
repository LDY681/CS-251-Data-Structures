#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"


using namespace std;

class MinHeap
{
	private:
		int size;	//current size of minheap
		int capacity;	//capacity of minheap, TODO: if capacity == size, enlarge capacity
		TreeNode ** array;	//pointer array of treenode

	public:
		MinHeap();
		TreeNode * removeMin(); //returns root of heap		
		void downHeapify(MinHeap *minHeap, int i);	//Heapify to make sure heap is in shape
		void insert(TreeNode * val); //adds element to heap
		int getSize(); //returns size of heap
		~MinHeap();
		TreeNode * top();
};


#endif
