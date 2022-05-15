#include "SkipList.h"

#include <assert.h> 

template<typename K, typename V>
SkipList<K, V>::SkipList(K tailerKey)
{
  createList(tailerKey);
}

template<typename K, typename V>
SkipList<K, V>::~SkipList()
{
  destroyList();
}

template<typename K, typename V>
void SkipList<K, V>::createList(K tailerKey)
{

}

template<typename K, typename V>
void SkipList<K, V>::createNode(int level, Node<K, V>*& node)
{
  node = new Node<K, V> *[level + 1];
  node->nodeLevel_ = level;
  assert(node != nullptr);
}