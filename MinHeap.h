#ifndef MINHEAP_H
#define MINHEAP_H

#include <string>
#include <cstring>

using namespace std;

class MinHeap
{
    private:
        int sizeHeap; //current size of min heap
        int capacity; //max amount of elements that the min heap can store
        int* minHeap; //we use a dynamic array to store the elements of the min heap
    public:
        MinHeap(); //default min heap constructor
        int parent (int i); //returns index of the parent of node i
        int left (int i); //returns index of the left child of node i
        int right (int i); //returns index of the right child of node i
        void BuildMinHeap(string s); //creates the min heap with the numbers from input file s
        void heapify(int i); //maintains the structure of the heap
        int getSize(); //returns the size of min heap (number of elements in min heap)
        int findMin(); //returns the min of min heap (the root)
        void insertNumber(int n); //puts number n in the correct position in the heap
        int deleteMin(); //deletes min (the element at the root)
};

#endif // MINHEAP_H
