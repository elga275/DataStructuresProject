#ifndef NODE_H
#define NODE_H

//we use this "node" class to help
//us build the avl tree
class node
{
    public:
        int value; //value of the node
        node* left; //pointer to the node's left child
        node* right; //pointer to the node's right child

        node(); //default node constructor
        node(int n); //node constructor that sets value equal to n
};

#endif //NODE_H
