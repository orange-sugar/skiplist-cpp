#ifndef SKIPLIST_RANDOMGENERATOR_H
#define SKIPLIST_RANDOMGENERATOR_H

#include <random>
#include <chrono>

static int currentTimeSeconds()
{
  auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

class RandomGenerator
{
  public:
    RandomGenerator(int seed = currentTimeSeconds()) 
      : generator_(seed)
    {  }

    int nextInt(int low, int high)
    {
      std::uniform_int_distribution<int> dist(low, high);
      return dist(generator_);
    }
    
  private:
    std::mt19937 generator_;
};  

#endif	// SKIPLIST_RANDOMGENERATOR_H