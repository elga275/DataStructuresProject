#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <cstring>

using namespace std;

class Edge
{

    public:
        int dest; //the destination of the certain edge
        int weight; //the weight of the edge
        Edge(); //default edge constructor
        Edge(int dest, int w); //edge constructor that sets values to dest and weight

};

class Vertex
{
    public:
        int id; //the id of the vertex
        Edge* ar; //dynamic array of all the edges that start from a specific vertex
        int v_capacity; //the max capacity of edges that array ar can store at a given moment
        int degree; //the number of edges in array ar currently
        Vertex(); //default vertex constructor
        Vertex(int id); //vertex constructor that sets a value to id

};

class Graph
{
    public:
        Vertex* G; //an array of vertices
        int g_capacity, vertices, edges; //"g_capacity" is the max capacity of vertices that array G
                                         //can store at a given moment, "vertices" is the total amount of
                                         //vertices in the graph currently and "edges" is the total
                                         //amount of edges in the graph currently
        Graph(); //default graph constructor
        void BuildGraph(string s); //reads numbers from a file (id1 id2 weight) and creates the graph
        int* getSizeGraph(); //returns the number of vertices and edges in the graph
        bool v_exists(int id); //checks if vertex with the given id exists in the graph
        int InsertVertex(int id); //inserts vertex with given id in the graph
        bool e_exists(int num1, int num2); //checks if edge num1-num2 exists in the graph
        int InsertEdge(int num1, int num2, int w); //inserts edge num1-num2 with weight w in the graph
        int getNearest(bool v[], int d[]); //returns the nearest unvisited node(we use
                                           //this function in "ComputeShortestPath" function)
        int ComputeShortestPath(int num1, int num2); //computes the shortest path between nodes num1 and num2
                                                     //using Dijkstra's algorithm
        int ComputeSpanningTree(); //computes the minimum spanning tree using Prim's algorithm and returns
                                   //the total weight of the mst
        void DFS(int v , bool visited[]); //this function performs DFS in the graph
        int FindConnectingComponents(); //finds and returns the number of connecting components in the graph
        int DeleteEdge(int num1,int num2); //deletes edge num1-num2 from the graph
};

#endif // GRAPH_H
