#include <iostream>
#include <fstream>
#include <ctime>
#include "Graph.h"

#define INF 999 //set infinity to 999

using namespace std;

Edge::Edge() //default edge constructor
{
    dest = -1;
    weight = -1;
}

Edge::Edge(int dest, int w) //edge constructor that assigns given destination
{                           //vertex and edge weight
    this -> dest = dest;
    weight = w;
}

Vertex::Vertex() // default constructor for vertex
{
    id = -1;
    degree = 0;
    v_capacity = 10;
    ar = new Edge[v_capacity];
    for (int i = 0; i < v_capacity; i++)
        ar[i] = Edge();
}

Vertex::Vertex(int id) //vertex constructor that creates a new vertex with
{                      //given id, sets its degree(number of neighbors) to 0
    this->id = id;     //and creates a dynamic array of edges with a max capacity
    degree = 0;        //of 10 edges for each vertex
    v_capacity = 10;
    ar = new Edge[v_capacity];
    for (int i = 0; i < v_capacity; i++)
        ar[i] = Edge();
}

Graph::Graph()      //graph constructor that sets total sum of vertices and
{                   //edges to 0 and creates a dynamic array of vertices with a max
    vertices = 0;   //capacity of 20 vertices
    edges = 0;
    g_capacity = 20;
    G = new Vertex[g_capacity];
}


int* Graph::getSizeGraph() //creates and returns an array that has
{                          //the number of vertices of the graph in
    int* r = new int [2];  //the first element and the number of
    r[0] = vertices;       //edges in the second element
    r[1] = edges;
    return r;
}

bool Graph::v_exists(int k)
{
    int i;
    for (i = 0; i < vertices; i++)  //we iterate through all the vertices
    {                               //of the graph to check if the vertex
        if (G[i].id == k)           //with the id of k exists
            return true;
    }
    return false;
}

int Graph::InsertVertex(int id)
{
    //if vertex with given id exists the function will
    //return true, otherwise it will return false
    bool flag = v_exists(id);
    if (flag == true)
    {
        return -1; //Vertex already exists
    }
    else
    {
        //we check whether or not the G array has reached its full capacity
        //(if it has, then we have to request more space)
        if (vertices == g_capacity)
        {
            //the G array HAS reached its full capacity, so we create
            //a new one and we increase the "g_capacity" by 20
            int i,j;
            Vertex* temp;
            temp = new Vertex[g_capacity];
            for(i = 0; i < g_capacity; i++)
            {
                temp[i].id = G[i].id;
                temp[i].degree = G[i].degree;
                temp[i].v_capacity = G[i].v_capacity;
                temp[i].ar = new Edge[temp[i].v_capacity];
                for(j = 0; j < G[i].v_capacity; j++)
                {
                    temp[i].ar[j] = G[i].ar[j];
                }
            }
            delete [] G;
            g_capacity += 20;
            G = new Vertex[g_capacity];
            for(i = 0; i < g_capacity - 20; i++)
            {
                G[i].id = temp[i].id;
                G[i].degree = temp[i].degree;
                G[i].v_capacity = temp[i].v_capacity;
                G[i].ar = new Edge[G[i].v_capacity];
                for(j = 0; j < temp[i].v_capacity; j++)
                {
                    G[i].ar[j] = temp[i].ar[j];
                }
            }
            delete [] temp;
        }
        //after having increased g_capacity of the graph(if needed),
        //we insert vertex with given id to the graph and we increase
        //the total amount of vertices in the graph by one
        G[vertices] = Vertex(id);
        vertices++;
        return 1; //Vertex was added successfully in the graph
    }
}

//the function returns true if edge num1-num2 exists, otherwise
//it returns false
bool Graph::e_exists(int num1, int num2)
{
    int pos, i;
    bool flag1, flag2;
    flag1 = v_exists(num1);
    flag2 = v_exists(num2);
    if (flag1 && flag2)
    {
        for (i = 0; i < vertices; i++)
        {
            //we find the index of node num1 and store it
            //in pos variable
            if (G[i].id == num1)
            {
                pos = i;
                break;
            }
        }

        //we iterate through all of num1's edges to check
        //if edge num1-num2 exists or not.(if num1-num2 exists,
        //them num2-num1 will also exist)
        for (i = 0; i < G[pos].degree; i++)
        {
            if (G[pos].ar[i].dest == num2)
                return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

//this function inserts edge num1-num2 with weight w in the graph
int Graph::InsertEdge(int num1, int num2, int w)
{
    bool flag1 = v_exists(num1);
    bool flag2 = v_exists(num2);
    bool flag3 = e_exists(num1, num2);

    if (flag1 == true && flag2 == true)
    {
        if (flag3 == true)
        {
            return -1; //edge already exists
        }
        else
        {
            int j;
            for (int i = 0; i < vertices; i++)
            {
                //we iterate through all the vertices in the graph until
                //we find the one with with id equal to num1(source of the
                //edge we want to add)
                if (G[i].id == num1)
                {
                    //we check whether or not the edge capacity for vertex num1
                    //is at max capacity. If it is, then we request more space
                    //and then we add the edge with destination num2, otherwise
                    //(if there is space at "ar" array of vertex num1) we add the
                    //edge immediately
                    if (G[i].degree == G[i].v_capacity)
                    {
                        Edge* temp;
                        temp = new Edge [G[i].degree];
                        for (j = 0; j < G[i].degree; j++)
                        {
                            temp[j] = G[i].ar[j];
                        }
                        delete [] G[i].ar;
                        G[i].v_capacity += 10;
                        G[i].ar = new Edge [G[i].v_capacity];
                        for (j = 0; j < G[i].degree; j++)
                        {
                            G[i].ar[j] = temp[j];
                        }
                        delete [] temp;
                        G[i].ar[G[i].degree].dest = num2;
                        G[i].ar[G[i].degree].weight = w;
                    }
                    else //the "ar" array of vertex num1 has available space
                    {    //so we add the edge immediately
                        G[i].ar[G[i].degree].dest = num2;
                        G[i].ar[G[i].degree].weight = w;
                    }
                    //we increase by one the degree of vertex num1
                    G[i].degree++;
                }


                //we iterate through all the vertices in the graph until
                //we find the one with with id equal to num2 (source of the
                //edge we want to add)
                else if (G[i].id == num2)
                {
                    //we check whether or not the edge capacity for vertex num2
                    //is at max capacity. If it is, then we request more space
                    //and then we add the edge with destination num1, otherwise
                    //(if there is space at "ar" array of vertex num2) we add the
                    //edge immediately
                    if (G[i].degree == G[i].v_capacity)
                    {
                        Edge* temp;
                        temp = new Edge [G[i].degree];
                        for (j = 0; j < G[i].degree; j++)
                        {
                            temp[j] = G[i].ar[j];
                        }
                        delete [] G[i].ar;
                        G[i].v_capacity += 10;
                        G[i].ar = new Edge [G[i].v_capacity];
                        for (j = 0; j < G[i].degree; j++)
                        {
                            G[i].ar[j] = temp[j];
                        }
                        delete [] temp;
                        G[i].ar[G[i].degree].dest = num1;
                        G[i].ar[G[i].degree].weight = w;
                    }
                    else  //the "ar" array of vertex num2 has available space
                    {     //so we add the edge immediately
                        G[i].ar[G[i].degree].dest = num1;
                        G[i].ar[G[i].degree].weight = w;
                    }
                    //we increase by one the degree of vertex num2
                    G[i].degree++;
                }
            }
            edges++; //we increase by one the total amount of edges in the graph

            return 1; //edge added successfully in the graph
        }
    }
    else
    {
        //one or both of the vertices don't exist in the graph
        if (flag1 == false && flag2 == true)
        {
            InsertVertex(num1);
            InsertEdge(num1, num2, w);
            return 1; //Edge added successfully
        }
        else if (flag1 == true && flag2 == false)
        {
            InsertVertex(num2);
            InsertEdge(num1, num2, w);
            return 1; //Edge added successfully
        }
        else if (flag1 == false && flag2 == false)
        {
            InsertVertex(num1);
            InsertVertex(num2);
            InsertEdge(num1, num2, w);
            return 1; //Edge added successfully
        }
    }
    return -2;
}

void Graph::BuildGraph(string s)
{
    //we open the input file s which contains the edges
    //we want to add in the graph (the numbers in each line will be
    //as follows: id1 id2 weight). We read every line(each line
    //contains one edge) until the end of the file and we add
    //the vertices and then the edges using the functions we
    //previously implemented (InsertEdge and InsertVertex)
    ifstream f;
    f.open(s, ios::in);
    if (!f.is_open())
    {
        cerr << "Could not open input file."<< endl;
        return;
    }
    else
    {
        char a, b, c;
        while (f >> a >> b >> c)
        {
            InsertVertex(a - '0');
            InsertVertex(b - '0');
            InsertEdge(a - '0', b - '0', c - '0');
        }
    }
    f.close(); //close input file s
    return;
}

int Graph::getNearest(bool v[], int d[])
{
    //this function returns the index of the vertex in the
    //graph that is marked as unvisited AND which is closest
    //to the source node so far
    int nearest_val = INF; //INF is set to 999
    int nearest_pos = 0;
    for (int i = 0; i < vertices; i++)
    {
        if (!v[i] && d[i] < nearest_val)
        {
            nearest_val = d[i];
            nearest_pos = i;
        }
    }
    return nearest_pos;
}

int Graph::ComputeShortestPath(int num1, int num2) //we use Dijkstra's algorithm
{
    int dist[vertices]; //array that keeps track of the nearest distances
                        //of each vertex from the source node
    bool visited[vertices]; //boolean array that keeps track of whether or not
                            //a vertex has been included in the shortest path
    int src = num1, dest = num2; //source node and destination node
    int src_pos, dest_pos;
    int i, adj;

    //we iterate through all the vertices until we find the id
    //of the source and the destination node and then we store
    //the indexes to src_pos and dest_pos respectively
    for (i = 0; i < vertices; i++)
    {
        if (G[i].id == src)
            src_pos = i;
        if (G[i].id == dest)
            dest_pos = i;
    }

    //we initialize every element in the "dist" array to infinity,
    //except for the distance of the source node which equals to 0
    for (i = 0; i < vertices; i++)
        dist[i] = INF;
    dist[src_pos] = 0;

    //we initialize every element of the "visited" array to false
    //since none of the vertices are included in the shortest path
    //initially
    for (i = 0; i < vertices; i++)
        visited[i] = false;

    //we repeat the same process for all the vertices, so that they
    //are all included in the shortest path. In every repetition, we get
    //the node that is nearest to the source node (using getNearest function)
    //and we mark it as visited. After we include said node in the path,
    //we check the distances to all its adjacent nodes and update the
    //distance array accordingly, if necessary
    int k;
    for (i = 0; i < vertices; i++)
    {
        int nearest = getNearest(visited, dist);
        visited[nearest] = true;
        for (adj = 0; adj < G[nearest].degree; adj++)
        {
            k = -1;
            for (int j = 0; j < vertices; j++)
            {
                if (G[j].id == G[nearest].ar[adj].dest)
                {
                    k = j;
                    break;
                }
            }
            if (k!=-1 && dist[k] > dist[nearest] + G[nearest].ar[adj].weight)
            {
                dist[k] = dist[nearest] + G[nearest].ar[adj].weight;
            }
        }
    }
    //in the end we return the total cost to travel from source node
    //num1 to destination node num2
    return dist[dest_pos];
}


int Graph::ComputeSpanningTree() //we use Prim's algorithm
{
    int dist = 0; //the total cost of the minimum spanning tree (mst)
    bool visited[vertices]; //boolean array that keeps track of whether or not
                            //a vertex has been included in the mst
    int key[vertices]; //the "key" array keeps track of the smallest weights of
                       //all the edges that are connecting the mst to other vertices
    int i, j, k, adj, dest_pos, fmin, min_pos;

    //we initialize every element of the "visited" array to false
    //since none of the vertices are included in the mst initially,
    //except for the first vertex in the graph,from which we start
    //calculating the mst
    for (i = 1; i < vertices; i++)
        visited[i] = false;
    visited[0] = true;

    //we initialize every element of the "key" array to INF (999)
    //since none of the vertices have been included in the mst so far,
    //except for the first vertex, so we initialize its key to 0
    //since there is no edge that is connecting the vertex to
    //itself in a loop
    for (i = 1; i < vertices; i++)
        key[i] = INF;
    key[0] = 0;

    //we start by including any one of the vertices in the mst. In this
    //case, we include the first vertex. Then for every adjacent vertex
    //of the min vertex, we check the weights of every edge and if we find a
    //weight that is smaller than the one at "key" array, we update it
    //accordingly. Next, we find the edge with the smallest weight that
    //connects the existing mst to other unvisited vertices (using the "key"
    //and "visited" arrays),we store the position it has in the G array
    //in the "min_pos" variable and we mark it as visited. We repeat the
    //same process for all the vertices in the graph
    for (i = 0; i < vertices; i++)
    {
        //if we are in the first repetition, then we initialize
        //"min_pos" to 0
        if (i == 0)
            min_pos = 0;

        for (adj = 0; adj < G[min_pos].degree; adj++)
        {
            for (j = 0; j < vertices; j++)
                if (G[min_pos].ar[adj].dest == G[j].id)
                    dest_pos = j; //we find the index of the destination vertex
                                  //of each adjacent vertex of the min vertex

            //we check the weights to all the adjacent vertices and if
            //we find a weight that is smaller that the one on the "key"
            //array, we update it accordingly
            if (G[min_pos].ar[adj].weight < key[dest_pos] && visited[dest_pos] == false)
                key[dest_pos] = G[min_pos].ar[adj].weight;
        }

        //below, we find the edge with the smallest weight that connects
        //the existing mst to the other vertices that are not yet included
        //in the mst. So, for all the vertices that exist in the mst so far,
        //we check every single one of their adjacent vertices until we find
        //the edge with the smallest weight. Then, after we find it, we
        //mark it as visited
        fmin = INF;
        min_pos = -1;
        for (k = 0; k < vertices; k++)
        {
            if (visited[k] == true)
            {
                for (adj = 0; adj < G[k].degree; adj++)
                {
                    for (j = 0; j < vertices; j++)
                        if (G[k].ar[adj].dest == G[j].id)
                            dest_pos = j;

                    if (key[dest_pos] < fmin && visited[dest_pos] == false)
                    {
                        fmin = key[dest_pos];
                        min_pos = dest_pos;
                    }
                }
            }
        }
        visited[min_pos] = true;
    }

    //lastly, to calculate the cost of the mst, we add all
    //the edge weights that are stored in the "key" array
    //in the "dist" variable and then we return it to main
    //through the function
    for (i = 0; i < vertices; i++)
        dist += key[i];

    return dist;
}

void Graph::DFS(int v, bool visited[])
{
    int adj, adj_pos;
    visited[v] = true;
    for (int i=0; i < G[v].degree; i++)
    {
        adj = G[v].ar[i].dest;
        adj_pos = -1;
        for (int j = 0; j < vertices; j++)
            if (G[j].id == adj)
            {
                adj_pos = j;
                break;
            }
        if (adj_pos != -1 && !visited[adj_pos])
            DFS(adj_pos, visited);
    }
}

int Graph::FindConnectingComponents()
{
    int i;
    int components=0;
    bool visited[vertices]; //We create a bool array of size equal to vertices to
                            //keep track of which vertices are visited

    for(i = 0; i < vertices; i++)   //We initialize "visited" array
        visited [i] = false;        //to have all its values set to false

    for(i = 0; i < vertices; i++)
    {
        if (!visited[i])      //For every unvisited vertex in the graph we execute a depth-first
        {                     //search, starting from this particular vertex, that finds the whole
            DFS (i, visited); //connected component and marks all its vertices as visited.
            components ++;    //Then we increase the value of the "components" counter by one.
        }
    }

    return components;
}

int Graph::DeleteEdge(int num1, int num2)
{
    int adj, pos;
    bool check = e_exists(num1, num2); //we check if edge num1-num2 exists or not
    if (check == false)
    {
        return -1; //Edge between the 2 vertices does not exist
    }
    else
    {
        //we iterate through all the vertices until we find vertex num1
        //and vertex num2
        for (int i = 0; i < vertices; i++)
        {
            //if we find vertex num1, then we search through all its
            //adjacent vertices until we find the edge with destination
            //num2. After that, we move all the edges that are stored on the right of edge num2-w
            //one position to the left and we decrease the "degree" of num1 by one and "edges"
            //by one
            if (G[i].id == num1)
            {
                for (adj = 0; adj < G[i].degree; adj++)
                {
                    if (G[i].ar[adj].dest == num2)
                    {
                        pos = adj;
                        break;
                    }
                }
                for (adj = pos; adj < G[i].degree - 1; adj++)
                {
                    G[i].ar[adj] = G[i].ar[adj + 1];
                }
                G[i].degree--;
                edges--;
            }

            //if we find vertex num2, then we search through all its
            //adjacent vertices until we find the edge with destination
            //num1. After that, we move all the edges that are stored on the right of edge num1-w
            //one position to the left and we decrease the "degree" of num2 by one and "edges"
            //by one
            if (G[i].id == num2)
            {
                for (adj = 0; adj < G[i].degree; adj++)
                {
                    if (G[i].ar[adj].dest == num1)
                    {
                        pos = adj;
                        break;
                    }
                }
                for (adj = pos; adj < G[i].degree - 1; adj++)
                {
                    G[i].ar[adj] = G[i].ar[adj + 1];
                }
                G[i].degree--;
                edges--;
            }
        }
        return 1; //Edge between the two vertices has been successfully deleted
    }
}
