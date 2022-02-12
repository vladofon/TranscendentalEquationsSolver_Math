#pragma once
#include "List.h"

template<class T>
class ArrayList :public List<T>
{
public:
   ArrayList()
   {
      this->size = 0;
      this->initialCapacity = 10;
      this->capacity = initialCapacity;
      this->elementData = new T[initialCapacity];
   }

   void add(T item) override
   {
      if (size >= capacity) {

         int smth = extendArraySize();
      }

      elementData[size] = item;
      size++;
   }

   void clear() override
   {
      elementData = new T[initialCapacity];
      size = 0;
   }

   void put(long index, T item) override
   {
      //if (size >= capacity) {
      //   extendArraySize();
      //}

      //T previous;
      //T current;
      //for (long i = index; i <= size; i++)
      //{
      //   if (i == index)
      //   {
      //      current = elementData[i];
      //      elementData[i] = item;
      //   }
      //   else if (i == index + 1)
      //   {
      //      previous = elementData[i];
      //      elementData[i] = current;
      //   }
      //   else
      //   {
      //      current = previous;
      //      previous = elementData[i];
      //      elementData[i] = current;
      //   }
      //}

      //size++;
   }

   void remove(long index) override
   {
      for (long i = index; i < size; i++)
      {
         elementData[i] = elementData[i + 1];
      }

      size--;
   }

   void merge(List<T>* list) override
   {
      long listSize = list->getSize();
      extendArraySize(listSize);

      for (long i = 0; i < listSize; i++)
      {
         elementData[i + size] = list->get(i);
      }

      size += listSize;

      delete list;
   }

   bool contains(T item) override
   {
      //for (long i = 0; i < size; i++)
      //{
      //   if (elementData[i] == item)
      //   {
      //      return true;
      //   }
      //}

      return false;
   }

   T get(long index)
   {
      return elementData[index];
   }

   T* toArray() override
   {
      return elementData;
   }

   void copy(List<T>& copied) override
   {
      long counter = 0;

      while (counter != size)
      {
         copied.add(get(counter));
         counter++;
      }
   }

   void addAll(long count, T* items) override
   {
      increaseCapacity(count);

      mergeArray(elementData, items, count);

      size += count;
   }

   long getSize() override
   {
      return size;
   }

   long getCapacity() override
   {
      return capacity;
   }

private:
   long size;
   long initialCapacity;
   long capacity;
   T* elementData;

   void increaseCapacity()
   {
      capacity += capacity / 2;
   }

   void increaseCapacity(long additionalSize)
   {
      while (capacity < (size + additionalSize))
      {
         capacity += capacity / 2;
      }
   }

   void copyArray(T* to, T* from, long size)
   {
      for (long i = 0; i < size; i++)
      {
         to[i] = from[i];
      }
   }

   void mergeArray(T* to, T* from, long size)
   {
      for (long i = 0; i < size; i++)
      {
         to[i + this->size] = from[i];
      }

      delete[] from;
   }

   int extendArraySize()
   {
      long oldSize = capacity;
      increaseCapacity();

      T* newArray = new T[capacity];
      copyArray(newArray, elementData, oldSize);

      elementData = newArray;

      return size;
   }

   void extendArraySize(long additionalSize)
   {
      if (size + additionalSize > capacity)
      {
         long oldSize = capacity;
         increaseCapacity(additionalSize);

         T* newArray = new T[capacity];
         copyArray(newArray, elementData, oldSize);

         elementData = newArray;
      }
   }
};