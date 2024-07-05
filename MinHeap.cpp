#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include "MinHeap.h"

using namespace std;

//this constructor initializes the min heap
MinHeap::MinHeap()
{
    minHeap = new int [1];
    sizeHeap = 0;
    capacity = 1;
}

//returns the index of the parent of node i
int MinHeap::parent(int i)
{
    return (i - 1)/2;
}

//returns the index of the left child of node i
int MinHeap::left(int i)
{
    return 2 * i + 1;
}

//returns the index of the right child of node i
int MinHeap::right(int i)
{
    return 2 * i + 2;
}

//we create the min heap from the numbers we read from input file s
void MinHeap::BuildMinHeap(string s)
{
    int* temp;
    int k,i,j;
    ifstream f;
    f.open(s, ios::in); //open input file s
    if (!f.is_open())
    {
        cerr << "Could not open input file." << endl;
    }
    else
    {
        while (f >> k) //read each number from the file and create heap.
        {
            //we check if min heap is full and if it is, then
            //we add another level to it.
            if (sizeHeap == capacity)
            {
                temp = new int [capacity];
                for (j = 0; j < sizeHeap; j++)
                    temp[j] = minHeap[j];
                delete[] minHeap;
                capacity = capacity * 2;
                minHeap = new int [capacity];
                for (j = 0; j < sizeHeap; j++)
                    minHeap[j] = temp[j];
                delete[] temp;
            }

            minHeap[sizeHeap] = k; //insert the new element at the end of the heap.
            i = sizeHeap++; //increase the amount of elements currently in the heap by one.

            while (i!=0 && minHeap[parent(i)] > minHeap[i])   //put the new element in
            {                                                 //the correct position.
                swap(minHeap[parent(i)], minHeap[i]);
                i = parent(i);
            }
        }
    }
    f.close(); //close input file s
}

//returns size (number of elements) of min heap
int MinHeap::getSize()
{
    return sizeHeap;
}

//keeps the structure of every element of the min heap (the value
//of every parent must be less than the value of their children)
void MinHeap::heapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    //find the index of the smallest element (out of i and its 2 children)
    if (l < sizeHeap && (minHeap[l] < minHeap[smallest]))
    {
        smallest = l;
    }
    if (r < sizeHeap && (minHeap[r] < minHeap[smallest]))
    {
        smallest = r;
    }

    //if one of i's children is smaller than i, then we swap them
    //and we execute heapify again
    if (smallest != i)
    {
        swap(minHeap[i],minHeap[smallest]); //put the smallest element in position i.
        heapify(smallest); //repeat the process until the element is in the correct position.
    }
}

//returns the min of min heap (the element at the root)
int MinHeap::findMin()
{
    if (sizeHeap == 0)
        return -1;
    return minHeap[0];
}

void MinHeap::insertNumber(int n)
{
    int i, j;
    //check if heap is full and if it is, then
    //add another level to it.
    if (sizeHeap == capacity)
    {
        int* temp = new int [capacity];
        for (j = 0; j < sizeHeap; j++)
            temp[j] = minHeap[j];
        delete[] minHeap;
        capacity = capacity * 2;
        minHeap = new int [capacity];
        for (j = 0; j < sizeHeap; j++)
            minHeap[j] = temp[j];
        delete[] temp;
    }
    minHeap[sizeHeap] = n;
    i = sizeHeap++;

    //put element n in the correct position
    while (i!=0 && minHeap[parent(i)] > minHeap[i])
    {
        swap(minHeap[parent(i)], minHeap[i]);
        i = parent(i);
    }
}

//deletes min of min heap
int MinHeap::deleteMin()
{
    //if the function returns 0, that means that the min heap
    //is empty and if it returns 1, that means that the min has
    //been deleted from min heap
    if (sizeHeap == 0)
        return 0;

    minHeap[0] = minHeap[sizeHeap - 1];
    sizeHeap--;
    heapify(0);
    return 1;
}
