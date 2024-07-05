#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <cstring>
#include "Node.h"

using namespace std;

class AVLtree
{
    private:
        int sizetree; //current size of nodes in avl tree
        node* root; //pointer to the root of the avl tree
    public:
        AVLtree(); //default avl tree constructor
        void BuildAVLtree(string s); //creates the AVL tree from the numbers from input file s
        int getSize(); //returns size of AVL tree
        node* findMin(node* root); //returns min number of AVL tree
        string searchNum(int n); //returns 'SUCCESS' if number n is found, or 'FAILURE' if not
        node* insertNum (node* root, int n); //inserts number n in AVL tree
        node* deleteNum (node* root, int n); //deletes number n from AVL tree
        node* getRoot() {return root;} //getter for the root of the avl tree

};

#endif // AVLTREE_H

