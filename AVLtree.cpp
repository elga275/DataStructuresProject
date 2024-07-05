#include <iostream>
#include <fstream>
#include <algorithm>
#include "AVLtree.h"

using namespace std;

//default avl tree constructor
AVLtree::AVLtree()
{
    sizetree = 0;
    root = NULL;
}

//returns the height of the avl tree (the longest
//path from the root to a leaf)
int getHeight(node* root)
{
    if (root == NULL)
        return 0;
    else
    {
      //find the height of each subtree
        int lst_height = getHeight(root -> left);
        int rst_height = getHeight(root -> right);

      //return the biggest of the two heights
        if (lst_height > rst_height)
            return (lst_height + 1);
        else
            return (rst_height + 1);
    }
}

//returns the balancing factor which is height_of_left_subtree - height_of_right_subtree
//(the balancing factor indicates whether there is a left imbalance or a right imbalance)
int getBalancingFactor(node* k)
{
    if (k == NULL)
        return 0;
    return getHeight(k->left) - getHeight(k->right);
}

//this function performs a left rotation
node* leftRotation (node* x)
{
    node* y = x -> right;
    node* subtree = y -> left;

    //do the left rotation
    y -> left = x;
    x -> right = subtree;

    //return the new root that occurred after the left rotation
    return y;
}

//this function performs a right rotation
node* rightRotation (node* x)
{
    node* y = x -> left;
    node* subtree = y -> right;

    //do the right rotation
    y -> right = x;
    x -> left = subtree;

    //return the new root that occurred after the right rotation
    return y;
}

//this function inserts a node with value n in the avl tree
node* AVLtree::insertNum(node* root, int n)
{
    //if root is empty, then assign n to the root
    if (root == NULL)
    {
        root = new node(n);
        sizetree++;
        return root;
    }

    //insert the new node in the correct position
    if (n < root -> value)
        root -> left = insertNum(root -> left, n);
    else if (n > root -> value)
        root -> right = insertNum(root -> right, n);
    else
        return root; //duplicates are not allowed in avl trees


    //we check whether or not an imbalance occurred
    int bf = getBalancingFactor(root);

    if (bf > 1 && n < root -> left -> value) //left left case
    {
        return rightRotation(root);
    }
    else if (bf > 1 && n > root -> left -> value) //left right case
    {
        root -> left = leftRotation(root -> left);
        return rightRotation(root);
    }
    else if (bf < -1 && n > root -> right -> value) //right right case
    {
        return leftRotation(root);
    }
    else if (bf < -1 && n < root -> right -> value) //right left case
    {
        root -> right = rightRotation(root -> right);
        return leftRotation(root);
    }

    //return the pointer that points to the root(there is a chance that
    //the root has changed after the rotations)
    return root;
}

//this function creates the avl tree by reading numbers from an input file s
void AVLtree::BuildAVLtree(string s)
{
    int k;
    ifstream f;
    f.open(s, ios::in); //open input file s
    if (!f.is_open())
        cerr << "Could not open input file." << endl;
    else
    {
        while (!f.eof()) //read each number from the file and create avl tree
        {
            f >> k; //read one number
            root = insertNum(root, k); //insert number in avl tree
        }
    }
    f.close(); //close input file s
}

//returns the number of nodes in the avl tree
int AVLtree::getSize()
{
    return sizetree;
}

//returns the node with the smallest value in the avl tree
node* AVLtree::findMin(node* root)
{
    node* temp = root;

    //we find the node with the smallest value which
    //is the node that is the most left in the avl tree
    while (temp -> left != NULL)
        temp = temp ->left;
    return temp;
}

//we search if number n exists in the avl tree (if it exists
//then we return 'SUCCESS', otherwise 'FAILURE'
string AVLtree::searchNum(int n)
{
    node* temp = root;
    bool flag = false;

    //we iterate through the tree until we reach a leaf or
    //until we find the element
    while (temp != NULL && flag == false)
    {
        if (n < temp -> value)
            temp = temp -> left;
        else if (n > temp -> value)
            temp = temp -> right;
        else
            flag = true;
    }

    if (flag == false)
        return "FAILURE"; //number was NOT found
    else
        return "SUCCESS"; //number was found
}

//this function deletes the node with value n
//from the avl tree, if it exists
node* AVLtree::deleteNum (node* root, int n)
{
    node* temp;
    if (root == NULL)
        return NULL;
    else if (n < root -> value) //node with value n is in the left subtree
        root -> left = deleteNum(root -> left, n);
    else if (n > root -> value) //node with value n is in the right subtree
        root -> right = deleteNum(root -> right, n);
    else // n == root -> value
    {
        if (root -> right == NULL) //root has no subtrees or only a left subtree
        {
            temp = root -> left;
            delete root;
            sizetree--;
            return temp;
        }
        else if (root -> left == NULL) //root only has a right subtree
        {
            temp = root -> right;
            delete root;
            sizetree--;
            return temp;
        }
        else //root has both left and right subtrees
        {
            //we find the node with the smallest value from the root's
            //right subtree and we assign that value to the root
            temp = findMin(root -> right);
            root -> value = temp -> value;
            root -> right = deleteNum (root -> right, temp -> value);
        }
    }

    //check whether or not an imbalance occurred
    int bf = getBalancingFactor(root);

    if (bf > 1 && n < root -> left -> value) //left left case
    {
        return rightRotation(root);
    }
    else if (bf > 1 && n > root -> left -> value) //left right case
    {
        root -> left = leftRotation(root -> left);
        return rightRotation(root);
    }
    else if (bf < -1 && n > root -> right -> value) //right right case
    {
        return leftRotation(root);
    }
    else if (bf < -1 && n < root -> right -> value) //right left case
    {
        root -> right = rightRotation(root -> right);
        return leftRotation(root);
    }

    //return the pointer that points to the root(there is a chance that
    //the root has changed after the rotations)
    return root;
}
