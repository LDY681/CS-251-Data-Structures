#include "MinHeap.h"
#include <iostream>
#include <algorithm>

using namespace std;


//Test1-3: Insert 1000 leaf nodes and retrieve them from the min heap
int main()
{
  srand(0);
  MinHeap * mh = new MinHeap();

  for (int i = 0; i < 10000; i++)
  {
    unsigned int r = rand()%2000;

    TreeNode * n = new TreeNode((unsigned char)(r%255), r);
    mh->insert(n);
  }

  for (int i = 0; i < 10000; i++)
  {
    TreeNode * n = mh->removeMin();
    if (n == NULL)
    {
      return 1;
    }

    unsigned int f = n->getFrequency();
    unsigned char val = n->getVal();
    int s = mh->getSize();
    cout << f << " " << (int)val << " " << s << endl;
  }

  return 0;
}
