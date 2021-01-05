//----------------------------------------------------------------------
// FILE: array_list.h
// NAME: Maria Elena Aviles-Baquero
// DATE: December 06, 2020
// DESC: Implements a resizable array version of the list
//       class. Elements are added by default to the last available
//       index in the array. 
//----------------------------------------------------------------------

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "list.h"

template<typename T>
class ArrayList : public List<T>
{
public:
  ArrayList();
  ArrayList(const ArrayList<T>& rhs);
  ~ArrayList();
  ArrayList& operator=(const ArrayList<T>& rhs);

  void add(const T& item);
  bool add(size_t index, const T& item);
  bool get(size_t index, T& return_item) const;
  bool set(size_t index, const T& new_item);
  bool remove(size_t index);
  size_t size() const;
  void selection_sort();
  void insertion_sort();
  void merge_sort();
  void quick_sort();
  void sort();

private:
  T* items;
  size_t capacity;
  size_t length;

  // helper to resize items array
  void resize();
  void swap(T& a, T& b);
  void merge_sort(size_t start, size_t end);
  void quick_sort(size_t start, size_t end);
};

// Constructor for Array List
template<typename T>
ArrayList<T>::ArrayList()
  : capacity(10), length(0), items(nullptr) 
{
  items = new T[capacity];
}

// Copy Constructor for Array List
template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& rhs)
  : capacity(10), length(0), items(nullptr) 
{
  // defer to assignment operator
  *this = rhs;
}

// Destructor for Array List
template<typename T>
ArrayList<T>::~ArrayList() 
{
  delete[] this->items;
  items = nullptr;
  length = 0;
  capacity = 10;
}

// Assignment Operator Overloading Function
template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs)
{
  if(this != &rhs) 
  {
    delete[] items;
    capacity = rhs.capacity;
    length = rhs.length;
    items = new T[capacity];

    // Creates a copy of the array
    for(int i = 0; i < length; ++i)
      items[i] = rhs.items[i];
    
  }
  return *this;
}

// Adds an item at the end of the array
template<typename T>
void ArrayList<T>::add(const T& item) 
{
  // Checks to see if length exceeds capacity
  if(length == capacity)
    resize();
  
  // Assigns item at length position in array
  items[length] = item;
  length++;
}  

// Adds an item at specified index of the array
template<typename T>
bool ArrayList<T>::add(size_t index, const T& item)
{ 
  // Checks to see if length exceeds capacity
  if(length == capacity)
    {
      resize();
    }

  // Checks if the index is valid
  if(index >= 0 && index <= length)
  { 
    // Shifts over items to add item to index 
    for(int i = length; i > index; --i)
    {
      items[i] = items[i-1];
    }
    items[index] = item;

    length++; 
    return 1;
  }
  return 0;
}

// Returns the item at specified index
template<typename T>
bool ArrayList<T>::get(size_t index, T& return_item) const 
{ 
  // Checks if the index is valid
  if (index >= 0 && index <= length-1) 
  {
    return_item = items[index];
    return 1;
  }
  return 0;
}

// Sets item at index to new item
template<typename T>
bool ArrayList<T>::set(size_t index, const T& new_item) 
{ 
  // Checks if the index is valid
  if(index >= 0 && index <= length - 1)
  {
    items[index] = new_item;
    return 1;
  }
  return 0;
}

// Removes item at specified index
template<typename T>
bool ArrayList<T>::remove(size_t index) 
{ 
  // Checks if the index is valid
  if(index >= length) //(index >= 0) && (index <= length-1) && (length != 0)) 
  {
    return 0;
    // Shifts over items to remove value at index
  }
  
  for(int i = index; i < length; ++i)
    {
      items[i] = items[i+1];
    }
  length--;
  return 1;
}

// Returns the length of the array
template<typename T>
size_t ArrayList<T>::size() const 
{ 
  return length;
}

// Creates a new array twice the size of the original array
template<typename T>
void ArrayList<T>::resize() 
{ 
  capacity *= 2;
  T* temp = new T[capacity];

  // Copies the array items[] to temp[]
  for(size_t i = 0; i < length; ++i)
    temp[i] = items[i];
  
  delete[] items;
  items = temp; 
}

// Sorts the array using this the selection sort algorithm
template<typename T>
void ArrayList<T>::selection_sort() 
{
  int i, j, min;
  for(i = 0; i < length; i++)
  {
    min = i;
    for(j = i + 1; j < length; j++)
    {
      if(items[j] < items[min])
      {
        min = j;
      }
    }
    swap(items[min], items[i]);
  }
}

// Sorts the array using this the insertion sort algorithm
template<typename T>
void ArrayList<T>::insertion_sort()
{
  int i, j, val;
  for(i = 1; i < length; i++)
  {
    j = i;
    while(j > 0 && items[j] < items[j - 1])
    {
      swap(items[j], items[j-1]);
      j = j - 1;
    }
  }
}

// Swaps two given values in the array
template<typename T>
void ArrayList<T>::swap(T& x, T& y)
{
  T tmp = x;
  x = y;
  y = tmp;
}

// Calls the helper function merge_sort to sort 
template<typename T>
void ArrayList<T>::merge_sort()
{
  merge_sort(0, length-1);
}

// Sorts linked list using merge sort algorithm
template<typename T>
void ArrayList<T>::merge_sort(size_t start, size_t end)
{
  if(start < end) 
  {
    size_t mid = (start + end)/2;
    merge_sort(start, mid);
    merge_sort(mid+1, end);

    size_t i = start, j = mid, k = end;
    size_t mergeS = k - i + 1;
    size_t mergeP = 0, leftP, rightP;
    T* merged = new T[mergeS];

    leftP = i;
    rightP = j+1;

    while(leftP <= j && rightP <= k)
    {
      if(items[leftP] <= items[rightP])
      {
        merged[mergeP] = items[leftP];
        leftP++;
      } else {
        merged[mergeP] = items[rightP];
        rightP++;
      }
      mergeP++;
    }

    while(leftP <= j)
    {
      merged[mergeP] = items[leftP];
      leftP++;
      mergeP++;
    }

    while(rightP <= k)
    {
      merged[mergeP] = items[rightP];
      rightP++;
      mergeP++;
    }

    for(mergeP = 0; mergeP < mergeS; mergeP++)
    {
      items[i+mergeP] = merged[mergeP];
    }
  }

}

// Calls the helper function quick_sort
template<typename T>
void ArrayList<T>::quick_sort()
{
  quick_sort(0, length-1);
}

// Sort linked list using the quick sort algorthim
template<typename T>
void ArrayList<T>::quick_sort(size_t start, size_t end)
{
  if(start >= end)
  {
    return;
  }

  T pivot;
  pivot = items[start];
  size_t tmp_start = start;
  int i;

  for(i = start + 1; i <= end; ++i)
  {
    if(items[i] < pivot)
    {
      tmp_start++;
      T tmp;
      tmp = items[tmp_start];
      items[tmp_start] = items[i];
      items[i] = tmp;
    }
  }
  items[start] = items[tmp_start];
  items[tmp_start] = pivot;

  if(tmp_start > start)
  {
    quick_sort(start, tmp_start - 1);
  }
  if(tmp_start < end)
  {
    quick_sort(tmp_start + 1, end);
  }
}


template<typename T>
void ArrayList<T>::sort()
{
  quick_sort();
}

#endif