#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <cstring>
using namespace std;


//linked list node class
class LLnode
{
    public:
        int value; //the value that the linked list node stores
        LLnode* next; //the pointer to the next linked list node
        LLnode(); //default linked list node constructor
        LLnode(int n); //second linked list node constructor
};

//linked list class
class LinkedList
{
    public:
        LLnode* header; //pointer to header of the linked list(first node in linked list)
        LinkedList(); //default linked list constructor
        void pushback(int n); //this function adds number n in the linked list
};


//hash table class
class HashTable
{
    private:
        int htsize; //this variable counts the number of integers in hash table
        LinkedList hashtable[20]; //the number of buckets in the hash table is 20
    public:
        HashTable(); //default hash table constructor
        void printHT();
        int HashFunction(int x);//we chose the hash function: x % buckets => x% 20
        void BuildHashTable(string s); //we read integers from the input file s and we create the hash table
        int getSize(); //returns the number of integers in hash table(htsize)
        string searchNum(int n); //the function searches if number n exists in the hash table
        void Insert(int n); //the function inserts number n in the hash table
};

#endif // HASHTABLE_H
