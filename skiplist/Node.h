#ifndef SKIPLIST_NODE_H
#define SKIPLIST_NODE_H

template<typename K, typename V>
class SkipList;

template<typename K, typename V>
class Node 
{
  friend class SkipList<K, V>;

  public:
    Node() {}
    Node(K k, V v);
    ~Node();

    K getKey() const;
    V getValue() const;

  private:
    K key_;
    V value_;
    Node<K, V> **forward_;
    int nodeLevel_;
};

#endif	// SKIPLIST_NODE_H