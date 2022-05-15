#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include "Node.h"
#include "RandomGenerator.h"

#include <cstddef>

template<typename K, typename V>
class SkipList
{
  public:
    SkipList(K tailerKey);
    ~SkipList();

    Node<K, V> *find(K key) const;

    bool insert(K key, V val);

    bool remove(K key, V val);

    int size() const { return size_; }

    int getLevel() const { return level_; }

  private:

    void createList(K tailerKey);

    void destroyList();

    void createNode(int level, Node<K, V> *&node);

    void createNode(int level, Node<K, V> *&node, K key, V val);

    void dumpAllNodes();

    void dumpNodeDetail(Node<K, V>* node, int nodeLevel);

    int level_;
    Node<K, V>* header_;
    Node<K, V>* tailer_;

    size_t size_;

    static const int MAX_LEVEL = 16;

    RandomGenerator rnd_;
};

#endif	// SKIPLIST_SKIPLIST_H