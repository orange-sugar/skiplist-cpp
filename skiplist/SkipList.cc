#include "SkipList.h"

template<>
void SkipList<int, std::string>::parseNode(int* key, std::string* value, std::string keySrc, std::string valueSrc)
{
  size_t pos{};
  *key = stoi(*value);
  *value = std::move(valueSrc);
}