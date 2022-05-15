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
  createNode(0, tailer_);

  tailer_->key_ = tailerKey;
  level_ = 0;

  createNode(MAX_LEVEL, header_);
  for (int i = 0; i < MAX_LEVEL; ++i)
  {
    header_->forward_[i] = tailer_;
  }
  size_ = 0;
}

template<typename K, typename V>
void SkipList<K, V>::createNode(int level, Node<K, V>*& node)
{
  node = new Node<K, V>{nullptr, nullptr};
  node->forward_ = new Node<K, V> *[level + 1];
  node->nodeLevel_ = level;
  assert(node != nullptr);
}

template<typename K, typename V>
void SkipList<K, V>::createNode(int level, Node<K, V>*& node, K key, V value)
{
  node = new Node<K, V>(key, value);
  if (level > 0)
  {
    node->forward_ = new Node<K, V>* [level + 1];
  }
  node->nodeLevel_ = level;
  assert(node != nullptr);
}

template<typename K, typename V>
void SkipList<K, V>::destroyList()
{
  Node<K, V>* p = header_;
  Node<K, V>* q;
  while (p != nullptr)
  {
    q = p->forward_[0];
    delete p;
    p = q;
  }
  delete p;
}

template<typename K, typename V>
Node<K, V>* SkipList<K, V>::find(K key) const
{
  Node<K, V>* node = header_;
  for (int i = level_; i >= 0; --i)
  {
    while ((node->forward_[i])->key_ < key)
    {
      node = node->forward_[i];
    }
  }
  node = node->forward_[0];
  if (node->key_ == key)
  {
    return node;
  }
  return nullptr;
}

template<typename K, typename V>
bool SkipList<K, V>::insert(K key, V val)
{
  Node<K, V>* update[MAX_LEVEL];
  Node<K, V>* node = header_;

  for (int i = level_; i >= 0; --i)
  {
    while ((node->forward_[i])->key_ < key)
    {
      node = node->forward_[i];
    }
    update[i] = node;
  }
  node = node->forward_[0];

  if (node->key_ == key)
  {
    return false;
  }

  int nodeLevel = rnd_.nextInt(0, level_);
  nodeLevel = nodeLevel == 0 ? 1 : nodeLevel;

  if (nodeLevel > level_)
  {
    nodeLevel = ++level_;
    update[nodeLevel] = header_;
  }

  // TODO
}


