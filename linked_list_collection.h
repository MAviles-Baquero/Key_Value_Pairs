//----------------------------------------------------------------------
// Author: Maria Elena Aviles-Baquero
// File:   linked_list_collection.h
// Date:   Fall 2020
//
// Assumptions:
//
//   1. Collections consist of a set of unique keys, where each key
//      has an associated value. A key together with its value is
//      called a "key-value pair".
//
//   2. Because a collection stores a particular key only once, if a
//      key can be associated with multiple underlying values, then
//      the key must be associated with a list containing the
//      underlying values. Thus, the collection would consist of
//      key-value pairs such that each key's corresponding value is
//      a list.
// 
//   3. A key should only be added into a collection if the key isn't
//      already in the collection. If the same key is added more than
//      once, then the behavior of the collection becomes undefined
//      (in terms of finding and removing keys).
//----------------------------------------------------------------------

 
#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include "collection.h"
#include "linked_list.h"
#include "array_list.h"


template<typename K, typename V>
class LinkedListCollection: public Collection <K,V>
{
public:
  void add(const K& a_key, const V& a_val);
  void remove(const K& a_key);
  bool find(const K& search_key, V& the_val) const;
  void find(const K& k1, const K& k2, ArrayList<K>& keys) const;
  void keys(ArrayList<K>& all_keys) const;
  void sort(ArrayList<K>& all_keys_sorted) const; // merge sort
  size_t size() const;

private:
  LinkedList<std::pair<K,V>> kv_list;

};

// Add a key-value pair to the kv_list
template<typename K, typename V>
void LinkedListCollection<K,V>::add(const K& a_key, const V& a_val)
{
  kv_list.add(std::pair<K,V>(a_key, a_val));
}

// Removes a key-value pair at the given key
template<typename K, typename V>
void LinkedListCollection<K,V>::remove(const K& a_key)
{
  if(size() <= 0)
  {
    return;
  }
  std::pair<K,V> tmp_list;
  kv_list.get(0, tmp_list);

  size_t idx = 0;
  // increments until the key is found
  while(tmp_list.first != a_key) 
  {
    idx++;
    kv_list.get(idx, tmp_list);
  }

  // Removes the key-value pair
  kv_list.remove(idx);
}

// Searchs the kv_list to find the given key and return by reference the value of the key
// If the key is found in the kv_list, then true is returned; Else it is false
template<typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& search_key, V& the_val) const
{
  std::pair<K,V> tmp_list;

  // Iterates through kv_list
  for(int i = 0; i < size(); i++)
  {
    kv_list.get(i, tmp_list);

    // If the key is found, the_val is assigned the value found and returns true
    if(tmp_list.first == search_key)
    {
      the_val = tmp_list.second;
      return 1;
    }
  }

  // If the key is not found, false is returns
  return 0;
}


// Searchs the kv_list to find all of the keys from k1 to k2
template<typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const
{
  // If the range is valid then the function continues
  if (k1 <= k2) 
  {
    std::pair<K,V> tmp_list;

    // Iterates through kv_list and when the range is found, keys is assigned the keys found
    for(int i = 0; i < size(); i++)
    {
      kv_list.get(i, tmp_list);
      if((tmp_list.first >= k1) && (tmp_list.first <= k2))
      {
        keys.add(tmp_list.first);
      }
    }
  }
}

// Returns all of the keys in a KV Collection
template<typename K, typename V>
void LinkedListCollection<K,V>::keys(ArrayList<K>& all_keys) const
{
  std::pair<K,V> tmp_list;

  // Iterates thorugh kv_list and adds the keys to all_keys
  for(int i = 0; i < size(); i++)
  {
    kv_list.get(i, tmp_list);
    all_keys.add(i, tmp_list.first);
  }
}

// Sorts the KV Collection
template<typename K, typename V>
void LinkedListCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const
{
  // uses the function above to find all the keys, then sorts them
  keys(all_keys_sorted);
  all_keys_sorted.sort();
}

// Returns the size of the KV Collection
template<typename K, typename V>
size_t LinkedListCollection<K,V>::size() const
{
  return kv_list.size();
}


#endif
