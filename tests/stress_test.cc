#include "SkipList.h"

#include <iostream>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>

using namespace std;

static const int kNumThreads = 4;
static const int kNumOperations = 100000;

SkipList<int, string> list(INT_MAX);

void threadFunc(int threadId)
{
  auto tid = threadId;
  printf("tid:%d\n", threadId);
  int opsPerThread = kNumOperations / kNumThreads;

  for (int count = 0; count < opsPerThread; ++count)
  {
    list.insert(rand()%kNumOperations, "a");
  }
}

int main()
{
    srand(time(nullptr));
  vector<unique_ptr<thread>> threads(kNumThreads);

  auto startTime = chrono::high_resolution_clock::now();

  for (int i = 0; i < kNumThreads; ++i)
  {
    threads[i] = make_unique<thread>(threadFunc, i);
  } 
  for (int i = 0; i < kNumThreads; ++i)
  {
    if (threads[i]->joinable())
    {
      threads[i]->join();
    }
  }

  auto endTime = chrono::high_resolution_clock::now();
  chrono::duration<double> times = endTime - startTime;

  printf("skiplist size now: %d\n", list.size());
  
  printf("%d operations complete per second\n", int(kNumOperations / times.count()));
}