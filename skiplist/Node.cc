#include "Node.h"

template<typename K, typename V>
Node<K, V>::Node(const K k, const V v)
{
  key_ = k;
  value_ = v;
}

template<typename K, typename V>
Node<K, V>::~Node()
{
  delete [] forward_;
}

template<typename K, typename V>
K Node<K, V>::getKey() const
{
  return key_;
}

template<typename K, typename V>
V Node<K, V>::getValue() const
{
  return value_;
}
