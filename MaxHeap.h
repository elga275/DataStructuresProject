#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <cstring>
#include <string>

using namespace std;

class MaxHeap
{
    private:
        int sizeHeap; //current size of max heap
        int capacity; //max amount of elements that the max heap can store
        int* maxHeap; //we use a dynamic array to store the elements of the max heap
    public:
        MaxHeap(); //default max heap constructor
        int parent (int i); //returns index of the parent of node i
        int left (int i); //returns index of the left child of node i
        int right (int i); //returns index of the right child of node i
        void BuildMaxHeap(string s); //creates the max heap with the numbers from input file s
        void heapify(int i); //maintains the structure of the heap
        int getSize(); //returns the size of max heap (number of elements in max heap)
        int findMax(); //returns the max of max heap (the root)
        void insertNumber(int n); //puts number n in the correct position in the heap
        int deleteMax(); //deletes max (the element at the root)
};
#endif // MAXHEAP_H
