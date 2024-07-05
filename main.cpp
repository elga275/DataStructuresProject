#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <ctime>

#include "MinHeap.h"
#include "MaxHeap.h"
#include "Node.h"
#include "AVLtree.h"
#include "HashTable.h"
#include "Graph.h"

using namespace std;

int main()
{
    int ds_size, ds_min, ds_max, graph_cost;
    node* min_node;
    node* avl_node;
    int* graph_size;

    string s, s1, s2, s3;
    int n1, n2, w;
    int components;
    int result;
    clock_t time_req;

    MinHeap minh;
    MaxHeap maxh;
    AVLtree avl;
    HashTable h;
    Graph g;

    ifstream co;
    ofstream out;
    out.open("output.txt");
    co.open("commands.txt");

    if(!co.is_open() || !out.is_open())
        cerr << "Could not open commands.txt file." << endl;
    else
    {
        while (getline(co, s))
        {
            if (s.empty())
                continue;

            istringstream iss(s);
            iss >> s1 >> s2;

            if (s1=="BUILD" && s2=="MINHEAP")
            {
                iss >> s3; //we read the name of the input file
                time_req = clock();
                minh.BuildMinHeap(s3); //we read the numbers from input file s3 and we create the min heap
                time_req = clock() - time_req;
                out << "(BUILD MINHEAP) Min Heap has been built in " << (float)time_req / CLOCKS_PER_SEC << " seconds." << endl;
            }
            else if (s1=="GETSIZE" && s2=="MINHEAP")
            {
                time_req = clock();
                ds_size = minh.getSize(); //returns the size of min heap
                time_req = clock() - time_req;
                out << "(GETSIZE MINHEAP) Size of Min Heap is: " << ds_size
                << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="FINDMIN" && s2=="MINHEAP")
            {
                time_req = clock();
                ds_min = minh.findMin(); //returns the min of min heap (the element at the root)
                time_req = clock() - time_req;
                if (ds_min == -1)
                    out << "(MINDMIN MINHEAP) Min Heap is empty (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else
                    out << "(FINDMIN MINHEAP)Min of Min Heap is: " << ds_min << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="INSERT" && s2=="MINHEAP")
            {
                iss >> n1; //read the number that we want to insert in the min heap
                time_req = clock();
                minh.insertNumber(n1); //we insert the number in min heap
                time_req = clock() - time_req;
                out << "(INSERT MINHEAP) Number " << n1 << " successfully added in Min Heap!" << " ("
                << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="DELETEMIN" && s2=="MINHEAP")
            {
                time_req = clock();
                result = minh.deleteMin(); //we delete the min from min heap (the element at the root)
                time_req = clock() - time_req;
                if (result == 1)
                    out << "(DELETEMIN MINHEAP) Min deleted successfully from Min Heap! (" <<
                    (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else
                    out << "(DELETEMIN MINHEAP) Min Heap is empty." << endl;
            }
            else if (s1=="BUILD" && s2=="MAXHEAP")
            {
                iss >> s3; //we read the name of the input file
                time_req = clock();
                maxh.BuildMaxHeap(s3); //we read the numbers from input file s3 and we create the max heap
                time_req = clock() - time_req;
                out << "(BUILD MAXHEAP) Max Heap has been built in " << (float)time_req / CLOCKS_PER_SEC << " seconds." << endl;
            }
            else if (s1=="GETSIZE" && s2=="MAXHEAP")
            {
                time_req = clock();
                ds_size = maxh.getSize(); //returns the size of max heap
                time_req = clock() - time_req;
                out << "(GETSIZE MAXHEAP) Size of Max Heap is: " << ds_size
                << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="FINDMAX" && s2=="MAXHEAP")
            {
                time_req = clock();
                ds_max = maxh.findMax(); //returns the max of max heap(the element at the root)
                time_req = clock() - time_req;
                if (ds_max == -1)
                    out << "(FINDMAX MAXHEAP) Max Heap is empty (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else
                    out << "(FINDMAX MAXHEAP) Max of Max Heap is: " << ds_max << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="INSERT" && s2=="MAXHEAP")
            {
                iss >> n1; // read the number that we want to insert in the max heap
                time_req = clock();
                maxh.insertNumber(n1); //we insert number n1 in max heap
                time_req = clock() - time_req;
                out << "(INSERT MAXHEAP) Number " << n1 << " successfully added in Max Heap!" << " ("
                << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="DELETEMAX" && s2=="MAXHEAP")
            {
                time_req = clock();
                result = maxh.deleteMax(); //we delete the max from max heap (the element at the root)
                time_req = clock() - time_req;
                if (result == 1)
                    out << "(DELETEMAX MAXHEAP) Max deleted successfully from Max Heap! (" <<
                    (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else
                    out << "(DELETEMAX MAXHEAP) Max Heap is empty." << endl;
            }
            else if (s1=="BUILD" && s2=="AVLTREE")
            {
                iss >> s3; //we read the name of the input file
                time_req = clock();
                avl.BuildAVLtree(s3); //we build the avl tree using the numbers from input file s3
                time_req = clock() - time_req;
                out << "(BUILD AVLTREE) AVL tree has been built in " << (float)time_req / CLOCKS_PER_SEC << " seconds." << endl;
            }
            else if (s1=="GETSIZE" && s2=="AVLTREE")
            {
                time_req = clock();
                ds_size = avl.getSize(); //returns the size of the avl tree
                time_req = clock() - time_req;
                out << "(GETSIZE AVLTREE) Size of AVL tree is: " << ds_size
                << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="FINDMIN" && s2=="AVLTREE")
            {
                time_req = clock();
                min_node = avl.findMin(avl.getRoot()); //returns the min node of the avl tree (the node
                                                       //that is the most left in the avl tree)
                time_req = clock() - time_req;
                out << "(FINDMIN AVLTREE) Min of AVL tree is: " << min_node -> value
                << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;

            }
            else if (s1=="SEARCH" && s2=="AVLTREE")
            {
                time_req = clock();
                iss >> n1; //we read the number we want to search in the avl tree
                s = avl.searchNum(n1); //we search if node with value n1 exists in the avl tree
                time_req = clock() - time_req;
                if (s=="FAILURE")
                    out << "(SEARCH AVLTREE) Number " << n1 << " was not found in AVL tree"
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else
                    out << "(SEARCH AVLTREE) Number " << n1 << " was found in AVL tree"
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="INSERT" && s2=="AVLTREE")
            {
                time_req = clock();
                iss >> n1; //we read the number we want to insert in the avl tree
                s = avl.searchNum(n1); //we check if node with value n1 already exists in the avl tree
                if (s == "FAILURE") //if it doesn't exist, then we add it
                {
                    avl.insertNum(avl.getRoot(), n1); //we insert number n1 in the avl tree
                    time_req = clock() - time_req;
                    out << "(INSERT AVLTREE) Number " << n1 << " successfully added in AVL Tree!" << " ("
                    << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                }
                else //if it does exist then we do nothing
                {
                    time_req = clock() - time_req;
                    out << "(INSERT AVLTREE) Node with value " << n1 << " already exists in the AVL tree..."
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                }

            }
            else if (s1=="DELETE" && s2=="AVLTREE")
            {
                time_req = clock();
                iss >> n1; //we read the number we want to delete from the avl tree
                s = avl.searchNum(n1); //we search if node with value n1 exists in the tree
                if (s == "FAILURE") //if it does not exist then we can't delete it
                {
                    time_req = clock() - time_req;
                    out << "(DELETE AVLTREE) Node with value " << n1 << " does not exist in the AVL tree..."
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                }
                else //if it exists then we delete it
                {
                    avl.deleteNum(avl.getRoot(), n1); //we delete number n1 from the avl tree
                    time_req = clock() - time_req;
                    out << "(DELETE AVLTREE) Number " << n1 << " successfully deleted from AVL Tree!"
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                }
            }
            else if (s1=="BUILD" && s2=="HASHTABLE")
            {
                iss >> s3; //we read the name of input file
                time_req = clock();
                h.BuildHashTable(s3); //we create the hash table by reading the numbers from input file s3
                time_req = clock() - time_req;
                out << "(BUILD HASHTABLE) Hash Table has been built in " << (float)time_req / CLOCKS_PER_SEC << " seconds." << endl;
            }
            else if (s1=="GETSIZE" && s2=="HASHTABLE")
            {
                time_req = clock();
                ds_size = h.getSize(); //returns the size of hashtable
                time_req = clock() - time_req;
                out << "(GETSIZE HASHTABLE) Size of Hash Table is: " << ds_size << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="SEARCH" && s2=="HASHTABLE")
            {
                iss >> n1; //we read the number we want to search in the hash table
                time_req = clock();
                s = h.searchNum(n1); //we search if number n1 exists in the hash table
                time_req = clock() - time_req;
                if (s=="FAILURE")
                    out << "(SEARCH HASHTABLE) Number " << n1 << " was not found in Hash Table"
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else
                    out << "(SEARCH HASHTABLE) Number " << n1 << " was found in Hash Table"
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="INSERT" && s2=="HASHTABLE")
            {
                iss >> n1; //we read the number we want to insert in the hash table
                time_req = clock();
                s = h.searchNum(n1); //we search if number n1 exists in the hash table
                if (s == "SUCCESS") //number already exists in the hash table
                {
                    out << "(INSERT HASHTABLE) Number " << n1 << " already exists in Hash Table..." <<
                    " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                }
                else if (s == "FAILURE")
                {
                    h.Insert(n1); //we insert number n1 in the hash table
                    time_req = clock() - time_req;
                    out << "(INSERT HASHTABLE) Number " << n1 << " successfully added in Hash Table!"
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                }
            }
            else if (s1=="BUILD" && s2=="GRAPH")
            {
                iss >> s3; //we read the name of the input file
                time_req = clock();
                g.BuildGraph(s3); //we create the graph by reading the numbers from input file s3
                time_req = clock() - time_req;
                out << "(BUILD GRAPH) Graph has been built in " << (float)time_req / CLOCKS_PER_SEC << " seconds." << endl;
            }
            else if (s1=="GETSIZE" && s2=="GRAPH")
            {
                graph_size = new int [2];
                time_req = clock();
                graph_size = g.getSizeGraph(); //returns the number of vertices and edges in the graph
                time_req = clock() - time_req;
                out<<"(GETSIZE GRAPH) Number of vertices in the graph: "<<graph_size[0]
                <<" and Number of edges in the graph: "<<graph_size[1]
                <<" ("<<(float)time_req/CLOCKS_PER_SEC<<" seconds)"<<endl;
            }
            else if (s1=="COMPUTESHORTESTPATH" && s2=="GRAPH")
            {
                iss >> n1 >> n2; //we read the 2 numbers (source and destination)
                time_req = clock();
                graph_cost = g.ComputeShortestPath(n1, n2); //we compute the shortest path from n1 to n2
                                                            //and we return the cost of that path
                time_req = clock() - time_req;
                if (graph_cost != 999)
                    out << "(COMPUTESHORTESTPATH GRAPH) The cost of the shortest path between the 2 nodes is: " << graph_cost
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else //if the cost is 999 then there is no path that connects the 2 nodes
                    out << "(COMPUTESHORTESTPATH GRAPH) There is no path that connects the 2 nodes"
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="COMPUTESPANNINGTREE" && s2=="GRAPH")
            {
                if (g.FindConnectingComponents() != 1)
                    out << "(COMPUTESPANNINGTREE GRAPH) There are more than one components in the graph, so Prim's algorithm can't be performed" << endl;
                else
                {
                    //we compute the minimum spanning tree only if there is 1 connecting component in the graph
                    time_req = clock();
                    graph_cost = g.ComputeSpanningTree(); //we compute the mst
                    time_req = clock() - time_req;
                    out << "(COMPUTESPANNINGTREE GRAPH) The cost of the minimum spanning tree is: " << graph_cost
                    << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                }
            }
            else if (s1=="FINDCONNECTEDCOMPONENTS" && s2=="GRAPH")
            {
                time_req = clock();
                components = g.FindConnectingComponents(); //we find the number of connected components in the graph
                time_req = clock() - time_req;
                out << "(FINDCONNECTEDCOMPONENTS GRAPH) There are " << components << " connected components in the graph"
                << " (" << (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="INSERT"&& s2=="GRAPH")
            {
                iss >> n1 >> n2 >> w; //we read the source, the destination and the weight of the edge we want to add
                time_req = clock();
                result = g.InsertEdge(n1, n2, w); //we insert the edge
                time_req = clock() - time_req;
                if (result == -1)
                    out << "(INSERT GRAPH) Edge " << n1 << "-" << n2 << " already exists in the graph (" <<
                    (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else if (result == 1)
                    out << "(INSERT GRAPH) Edge " << n1 << "-" << n2 << " added successfully in the graph (" <<
                    (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
            else if (s1=="DELETE" && s2=="GRAPH")
            {
                iss >> n1 >> n2; //we read the source and the destination of the edge we want to delete
                time_req = clock();
                result = g.DeleteEdge(n1, n2); //we delete the edge
                time_req = clock() - time_req;
                if (result == -1)
                    out << "(DELETE GRAPH) Edge " << n1 << "-" << n2 << " does not exist in the graph (" <<
                    (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
                else if (result == 1)
                    out << "(DELETE GRAPH) Edge " << n1 << "-" << n2 << " successfully deleted from the graph (" <<
                    (float)time_req / CLOCKS_PER_SEC << " seconds)" << endl;
            }
        }
    }
    return 0;
}
