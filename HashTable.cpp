#include <iostream>
#include <fstream>
#include "HashTable.h"

using namespace std;

//default constructor for linked list node
LLnode::LLnode()
{
    //sets the value of the node equal to -1 and
    //sets the pointer to the next node to NULL
    value = -1;
    next = NULL;
}

//second constructor for linked list node
LLnode::LLnode(int n)
{
    //sets the value of the node equal to n and
    //sets the pointer to the next node to NULL
    value = n;
    next = NULL;
}

//default linked list constructor
LinkedList::LinkedList()
{
    //sets header of the linked list to NULL
    header = NULL;
}

//default hash table constructor
HashTable::HashTable()
{
    //we set the number of integers in the hash table equal to
    //0 and then we create an empty linked list in every bucket
    //of the hash table
    htsize = 0;
    for (int i = 0; i < 20; i++)
    {
        hashtable[i] = LinkedList();
    }
}

void HashTable::printHT()
{
    LLnode* temp;
    temp = NULL;
    for (int i = 0; i < 20; i++)
    {
        temp = hashtable[i].header;
        cout << i << ") ";
        do
        {
            if (temp == NULL)
                break;
            cout << " -> " << temp -> value;
            temp = temp -> next;
        }
        while (temp != NULL);
        cout << endl;
    }
}

//this is the hash function
int HashTable::HashFunction(int x)
{
    //returns the index of the bucket that number x is
    //supposed to be added to
    return x % 20;
}


void LinkedList::pushback(int n)
{
    LLnode* new_n = new LLnode();
    LLnode* last = header;
    new_n -> value = n;
    new_n -> next = NULL;
    if (header == NULL)
        header = new_n;
    else
    {
        while(last -> next != NULL)
            last = last -> next;
        last -> next = new_n;
    }
}

//this function inserts number n in the hash table
void HashTable::Insert(int n)
{
    //we insert number n in the correct linked list(the number
    //of the bucket is determined by the hash function) and then
    //we increase htsize by one
    hashtable[HashFunction(n)].pushback(n);
    htsize++;
}

//this function creates the hash table by reading numbers from
//an input file s
void HashTable::BuildHashTable(string s)
{
    int k;
    ifstream f;
    f.open(s, ios::in); //we open input file s
    if (!f.is_open())
        cerr << "Could not open input file." << endl;
    else
    {
        //we read each number until the end of the file
        //and using the Insert() function we implemented earlier
        //we insert every number in its correct position
        while (!f.eof())
        {
            f >> k;
            Insert(k);
        }
    }
    f.close(); //we close input file s
}

//returns number of integers in hash table
int HashTable::getSize()
{
    return htsize;
}


//this function searches if number n exists in the hash table. If
//it exists, then the function returns 'SUCCESS', otherwise it
//returns 'FAILURE'
string HashTable::searchNum(int n)
{
    int index = HashFunction(n);
    bool found = false;
    LLnode* current = hashtable[index].header;

    while (current != NULL && found == false)
    {
        if (current -> value == n)
            found = true;
        else
            current = current -> next;
    }

    if (found == true)
        return "SUCCESS"; //number n has been found
    else
        return "FAILURE"; //number n has NOT been found
}
