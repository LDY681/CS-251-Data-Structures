#include "MinHeap.h"
#include <iostream>
#include <algorithm>

using namespace std;


//Test1-2: Interleaved calls to insert and removeMin
int main()
{
  srand(0);
  MinHeap * mh = new MinHeap();

  for (int i = 0; i < 50; i++)
  {
    unsigned int f = rand() % 10;
    unsigned char val = (unsigned char)('a' + f);

    TreeNode * n = new TreeNode(val, f);

    mh->insert(n);
    int s = mh->getSize();
    cout << f << " " << (int)val << " " << s << endl;

    if (i % 3 == 2)
    {
      TreeNode * m = mh->removeMin();
      if (m == NULL)
      {
        return 1;
      }

      unsigned int f = m->getFrequency();
      unsigned char val = m->getVal();
      int s = mh->getSize();
      cout << f << " " << (int)val << " " << s << endl;

    }
  }

  return 0;
}
