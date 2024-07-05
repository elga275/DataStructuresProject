#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "MaxHeap.h"

using namespace std;

//this constructor initializes the max heap
MaxHeap::MaxHeap()
{
    maxHeap = new int [1];
    sizeHeap = 0;
    capacity = 1;
}

//returns the index of the parent of node i
int MaxHeap::parent(int i)
{
    return (i - 1)/2;
}

//returns the index of the left child of node i
int MaxHeap::left(int i)
{
    return 2 * i + 1;
}

//returns the index of the right child of node i
int MaxHeap::right(int i)
{
    return 2 * i + 2;
}

//we create the max heap from the numbers we read from input file s
void MaxHeap::BuildMaxHeap(string s)
{
    int* temp;
    int k,i,j;
    ifstream f;
    f.open(s, ios::in); //open input file
    if (!f.is_open())
    {
        cerr << "Could not open input file." << endl;
    }
    else
    {
        while (f >> k) //read each number from the file and create heap.
        {
            //we check if max heap is full and if it is, then
            //we add another level to it.
            if (sizeHeap == capacity)
            {
                temp = new int [capacity];
                for (j = 0; j < sizeHeap; j++)
                    temp[j] = maxHeap[j];
                delete[] maxHeap;
                capacity = capacity * 2;
                maxHeap = new int [capacity];
                for (j = 0; j < sizeHeap; j++)
                    maxHeap[j] = temp[j];
                delete[] temp;
            }

            maxHeap[sizeHeap] = k; //insert the new element at the end of the heap.
            i = sizeHeap++; //increase the amount of elements currently in the heap by one.

            while (i!=0 && maxHeap[parent(i)] < maxHeap[i])   //put the new element in
            {                                                 //the correct position.
                swap(maxHeap[parent(i)], maxHeap[i]);
                i = parent(i);
            }
        }
    }
    f.close(); //close input file s
}

//returns size (number of elements) of max heap
int MaxHeap::getSize()
{
    return sizeHeap;
}

//keeps the structure of every element of the max heap (the value
//of every parent must be bigger than the value of their children)
void MaxHeap::heapify(int i)
{
    int l = left(i);
    int r = right(i);
    int biggest = i;

    //find the index of the biggest element (out of i and its 2 children)
    if (l < sizeHeap && (maxHeap[l] > maxHeap[biggest]))
    {
        biggest = l;
    }
    if (r < sizeHeap && (maxHeap[r] > maxHeap[biggest]))
    {
        biggest = r;
    }


    //if one of i's children is bigger than i, then we swap them
    //and we execute heapify again
    if (biggest != i)
    {
        swap(maxHeap[i],maxHeap[biggest]); //put the biggest element in position i.
        heapify(biggest); //repeat the process until the element is in the correct position.
    }
}

//returns the max of max heap (the element at the root)
int MaxHeap::findMax()
{
    if (sizeHeap == 0)
        return -1;
    return maxHeap[0];
}

void MaxHeap::insertNumber(int n)
{
        int i,j;
        //check if heap is full and if it is, then
        //add another level to it.
        if (sizeHeap == capacity)
            {
                int* temp = new int [capacity];
                for (j = 0; j < sizeHeap; j++)
                    temp[j] = maxHeap[j];
                delete[] maxHeap;
                capacity = capacity * 2;
                maxHeap = new int [capacity];
                for (j = 0; j < sizeHeap; j++)
                    maxHeap[j] = temp[j];
                delete[] temp;
            }
        maxHeap[sizeHeap] = n;
        i = sizeHeap++;

        //put element n in the correct position
        while (i!=0 && maxHeap[parent(i)] < maxHeap[i])
        {
            swap(maxHeap[parent(i)], maxHeap[i]);
            i = parent(i);
        }

}

//deletes max from max heap
int MaxHeap::deleteMax()
{
    //if the function returns 0, that means that the max heap
    //is empty and if it returns 1, that means that the max has
    //been deleted from max heap
    if (sizeHeap == 0)
        return 0;

    maxHeap[0] = maxHeap[sizeHeap - 1];
    sizeHeap--;
    heapify(0);
    return 1;
}

