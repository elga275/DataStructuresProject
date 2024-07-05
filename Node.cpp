#include <iostream>
#include "Node.h"

using namespace std;

node::node()
{
    value = 0;
    left = NULL;
    right = NULL;
}

node::node(int n)
{
    value = n;
    left = NULL;
    right = NULL;
}
