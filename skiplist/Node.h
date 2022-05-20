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
    Node(const K k, const V v, int level = 0);
    ~Node();

    K getKey() const;
    V getValue() const;

  private:
    K key_;
    V value_;
    Node<K, V> **forward_;
    int nodeLevel_;
};

template<typename K, typename V>
Node<K, V>::Node(const K k, const V v, int level)
  : key_(k),
    value_(v),
    forward_(new Node<K, V>* [level + 1]),
    nodeLevel_(level)
{
  memset(forward_, 0, sizeof (Node<K, V>*) * (level + 1));
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

#endif	// SKIPLIST_NODE_H