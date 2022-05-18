#include "skiplist/SkipList.h"

int main()
{
  SkipList<int, std::string> list(INT_MAX);

  // for (int i = 0; i < 10; ++i)
  // {
  //   list.insert(i, i + 10);
  //   list.print();
  //   std::cout << "---------------------\n";
  // }
  
  // int deletedVal;
  // list.remove(2, &deletedVal);
  // printf("deleted key = %d, val = %d\n", 2, deletedVal);
  // list.print();

  list.loadFromFile("kv.txt");
  list.dumpToFile("dump.txt");
  list.print();
}