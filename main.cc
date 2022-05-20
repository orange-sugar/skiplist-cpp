#include "skiplist/SkipList.h"

int main()
{
  srand(time(NULL));
  SkipList<int, std::string> list(INT_MAX);

  {
    SkipList<int, std::string> list1(INT_MAX);
  }

  for (int i = 0; i < 10; ++i)
  {
    list.insert(i, "a");
    list.print();
    std::cout << "---------------------\n";
  }
  
  std::string deletedVal;
  list.remove(2, &deletedVal);
  printf("deleted key = %d, val = %s\n", 2, deletedVal.c_str());
  list.print();

  // list.loadFromFile("kv.txt");
  // list.dumpToFile("dump.txt");
  // list.insert(-1, "hello");
  // list.insert(0, "world");
  // list.insert(2, "!");
  // list.print();
}