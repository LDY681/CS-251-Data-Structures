#include "MinHeap.h"
#include <iostream>

using namespace std;


//Test1-1: Insert one leaf node and retrieve it from the min heap
int main()
{

  MinHeap * mh = new MinHeap();

  //sanity check
  TreeNode * n = new TreeNode(0, 0);
  mh->insert(n);

  TreeNode * m = mh->removeMin();

  if (m != n) return 1;
  else return 0;

}
