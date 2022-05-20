#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include "Node.h"

#include <assert.h>

#include <any>
#include <climits>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mutex>

static const std::string kDelimiter = ":";

template<typename K, typename V>
class SkipList
{
  public:
    SkipList(K tailerKey);
    ~SkipList();

    Node<K, V> *find(K key) const;

    bool insert(const K key, const V val);

    bool remove(const K key, V* val);

    int size() const { return size_; }

    int getLevel() const { return level_; }

    void print() const;

    void loadFromFile(std::string filename);

    void dumpToFile(std::string filename);

  private:

    void initateList(K tailerKey);

    void destroyList();

    int getRandomLevel();

    int level_;
    Node<K, V>* header_;
    Node<K, V>* tailer_;

    size_t size_;

    static const int kMaxLevel = 16;

    std::ifstream is_;
    std::ofstream os_;

    std::mutex mutex_;
};


template<typename K, typename V>
SkipList<K, V>::SkipList(K tailerKey)
{
  initateList(tailerKey);
}

template<typename K, typename V>
SkipList<K, V>::~SkipList()
{
  destroyList();
}

// 创建空跳表，包含头尾标志
template<typename K, typename V>
void SkipList<K, V>::initateList(K tailerKey)
{
  tailer_ = new Node<K, V>{tailerKey, {}, 0};

  level_ = 0;

  header_ = new Node<K, V>{{}, {}, kMaxLevel};

  for (int i = 0; i <= kMaxLevel; ++i)
  {
    header_->forward_[i] = tailer_;
  }
  size_ = 0;
}

// 销毁跳表，释放内存
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

// 查找节点
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

// 插入节点
template<typename K, typename V>
bool SkipList<K, V>::insert(const K key, const V value)
{
  std::lock_guard<std::mutex> lock(mutex_);
  Node<K, V>* update[kMaxLevel+1];
  Node<K, V>* current = header_;

  for (int i = level_; i >= 0; --i)
  {
    while ((current->forward_[i])->key_ < key)
    {
      current = current->forward_[i];
    }
    update[i] = current;
  }
  current = current->forward_[0];

  if (current->key_ == key)
  {
    return false;
  }

  int nodeLevel = getRandomLevel();

  if (nodeLevel > level_)
  {
    nodeLevel = ++level_;
    update[nodeLevel] = header_;
  }

  Node<K, V>* newNode = new Node<K, V>{key, value, nodeLevel};

  for (int i = nodeLevel; i >= 0; --i)
  {
    newNode->forward_[i] = update[i]->forward_[i];
    update[i]->forward_[i] = newNode;
  }

  ++size_;

  return true;
}

// 移除节点
template<typename K, typename V>
bool SkipList<K, V>::remove(const K key, V* value)
{
  std::lock_guard<std::mutex> lock(mutex_);
  Node<K, V>* update[kMaxLevel + 1];
  Node<K, V>* node = header_;

  for (int i = level_; i >= 0; --i)
  {
    while (node->forward_[i]->key_ < key)
    {
      node = node->forward_[i];
    }
    update[i] = node;
  }

  node = node->forward_[0];

  if (node->key_ != key)
  {
    return false;
  }

  *value = node->value_;
  for (int i = 0; i <= level_; ++i)
  {
    if (update[i]->forward_[i] != node)
    {
      break;
    }
    update[i]->forward_[i] = node->forward_[i];
  }

  delete node;

  while (level_ > 0 && header_->forward_[level_] == tailer_)
  {
    --level_;
  }

  --size_;

  return true;
}

// 打印跳表
template<typename K, typename V>
void SkipList<K, V>::print() const
{
  
  for (int i = 0; i <= level_; ++i)
  {
    std::cout << "level " << i << ": ";
    std::cout << "header-> ";
    Node<K, V>* tmp = header_;
    tmp = tmp->forward_[i];
    while (tmp != tailer_)
    {
      std::cout << tmp->getKey() << ":" << tmp->getValue() << ";";
      tmp = tmp->forward_[i];
    }
    std::cout << " ->tailer";
    std::cout << std::endl;
  }
}

// 从一行中解析key和value
static void readNode(std::string* key, std::string* value, std::string &line)
{
  size_t posDelimiter;
  posDelimiter = line.find(kDelimiter);

  *key = line.substr(0, posDelimiter - 0);
  *value = line.substr(posDelimiter + 1, line.size() - 1);
}

// 从文件导入
template<typename K, typename V>
void SkipList<K, V>::loadFromFile(std::string filename)
{
  is_.open(filename, std::ios::in | std::ios::binary);
  if (is_.is_open())
  {
    std::string line;
    std::string key;
    std::string val;
    while (getline(is_, line))
    {
      if (line.empty())
      {
        continue;
      }
      readNode(&key, &val, line);

      insert(stoi(key), val);
    }
  }
  else   
  {
    printf("open file failed.");
  }
}

// 保存至文件
template<typename K, typename V>
void SkipList<K, V>::dumpToFile(std::string filename)
{
  os_.open(filename, std::ios::out | std::ios::trunc);
  Node<K, V>* tmp = header_;
  while (tmp->forward_[0] != tailer_)
  {
    os_ << tmp->forward_[0]->key_ << kDelimiter << tmp->forward_[0]->value_ << std::endl;
    tmp = tmp->forward_[0];
  }
}

template<typename K, typename  V>
int SkipList<K, V>::getRandomLevel()
{
  int nodeLevel = 1;
  while (rand() % 2) {
      nodeLevel++;
  }
  nodeLevel = (nodeLevel < kMaxLevel) ? nodeLevel : kMaxLevel;
  return nodeLevel;
}

#endif	// SKIPLIST_SKIPLIST_H