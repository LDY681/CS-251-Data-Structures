#include "MinHeap.h"
#include <iostream>

using namespace std;


//Test1-6: Making sure multiple calls to removeMin on an empty heap does not corrupt it
int main()
{

  MinHeap * mh = new MinHeap();
  mh->removeMin();
  mh->removeMin();
  mh->removeMin();

  TreeNode * n1 = new TreeNode(0, 10);
   mh->insert(n1);

  mh->removeMin(); 

  TreeNode * n2 = new TreeNode(0, 1);
  mh->insert(n2);

  TreeNode * n3 = new TreeNode(0, 12);
  mh->insert(n3);

  TreeNode * n = mh->removeMin();

  if (n == n2) return 0;
  else return 1;

}
