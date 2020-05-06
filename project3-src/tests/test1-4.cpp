#include "MinHeap.h"
#include <iostream>

using namespace std;


//Test1-4: Attempting to to call removeMin on an empty heap
int main()
{

  MinHeap * mh = new MinHeap();

  TreeNode * m = mh->removeMin();

  if (!m && !mh->getSize()) return 0;
  else return 1;

}
