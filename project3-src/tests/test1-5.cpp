#include "MinHeap.h"
#include <iostream>

using namespace std;


//Test1-5: Insert duplicate frequencies
int main()
{

  MinHeap * mh = new MinHeap();

  for (int i = 0; i < 10000; i++)
  {
    TreeNode * n = new TreeNode((unsigned char)(i%255), i%10);
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
