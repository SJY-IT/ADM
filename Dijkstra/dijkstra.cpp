// Code ref: ADM pg. 153
// Node start from 1 for convenience.
// notice MAXV is 1000 but the *edges[] is initialised with 1001 slots
// in initialiseGraph, we initialise the adjacency list from 1 to 1000
#include <iostream>
using namespace std;

#define MAXV 1000           // Maximum number of vertices
int parent[MAXV+1];         // parent vertex, -1 denotes that there is no parent.
int MAXINT = 2147483647;    // Maximum int
int T_prim[MAXV+1];
struct edgeNode {
    int v;                  // adjacency Info
    int weight;             // edge weight, if any
    struct edgeNode *next;  // next edge in list
};
struct graph {
    edgeNode *edges[MAXV+1];    // adjacency info
    int degree[MAXV+1];         // outdegree of each vertex;
    int nVertices;              // number of vertices in graph
    int nEdges;                 // number of edges in graph
    bool directed;              // is the graph directed?
};
/*
A typical graph format consists of an initial line featuring the number 
of vertices and edges in the graph, 
followed by a listing of the edges at one vertex pair per line.
*/
void initialiseGraph (graph *G, bool D) {
    G->nVertices = 0;
    G->nEdges = 0;
    G->directed = D;
    
    for(int i=1; i<=MAXV; i++) G->edges[i] = NULL;
    for(int i=1; i<=MAXV; i++) G->degree[i] = 0;    
}
void insertEdge (graph *G, int x, int y, bool D) {
    edgeNode *P = new edgeNode;     // temporary pointer to new edgeNode
    P->v = y;
    P->weight = 0;
    
    P->next = G->edges[x];          
    G->edges[x] = P;                // insert at head of list
    
    G->degree[x] ++;
    
    if (D == false)
        insertEdge(G, y, x, true);
    else
        G->nEdges ++;       
}
void insertEdge (graph *G, int x, int y, int w, bool D) {
    edgeNode *P = new edgeNode;     // temporary pointer to new edgeNode
    P->v = y;
    P->weight = w;
    
    P->next = G->edges[x];          
    G->edges[x] = P;                // insert at head of list
    
    G->degree[x] ++;
    
    if (D == false)
        insertEdge(G, y, x, w, true);
    else
        G->nEdges ++;       
}
void readGraph (graph *G, bool D) {
    int m;      // number of edges
    int x, y;   // vertices in edge (x,y)

    initialiseGraph(G, D);
    cout << "Enter the number of vertices and edges of the graph (separate each value by space)" << endl;
    cin >> G->nVertices >> m;
    
    for (int i=1; i<=m; i++) {
        cout << "Enter the vertices in edge (x,y) (separate each value by space)" << endl;
        cin >> x >> y;
        insertEdge(G, x, y, D);
    }
}
void readWeightedGraph (graph *G, bool D) {
    int m;      // number of edges
    int x, y;   // vertices in edge (x,y)
    int w;      // weight of the edge
    initialiseGraph(G, D);
    cout << "Enter the number of vertices and edges of the graph (separate each value by space)" << endl;
    cin >> G->nVertices >> m;
    
    for (int i=1; i<=m; i++) {
        cout << "Enter the vertices in edge (x,y) and the weight (separate each value by space)" << endl;
        cin >> x >> y >> w;
        insertEdge(G, x, y, w, D);
    }
}
void printGraph (graph *G) {
    edgeNode *P;    // temporary pointer to edgeNode
    for (int i=1; i<=G->nVertices; i++) {
        cout << "[" << i << "]: ";
        P = G->edges[i];
        while (P != NULL) {
            cout << P->v << "->";
            P = P->next;
        }
        cout << "NULL"; 
        cout << endl;
    }
}
void printPrim (graph *G) {
    for(int i=1; i<=G->nVertices; i++) {
        //cout << T_prim[i] << " ";
        if(parent[ T_prim[i] ] == -1)
            cout << "Starting Point: " << T_prim[i] << endl;
        else
            cout << "Linked " << parent[ T_prim[i] ] << " with " << T_prim[i] << endl; 
    }
    cout << endl;

}
/*
Prim-MST(G)
    1) Select an arbitrary vertex s to start the tree from.
    2) While (there are still nontree vertices)
        2-1. Select the edge of minimum weight between a tree and nontree vertex
        2-2. Add the selected edge and vertex to the tree T-prim.
*/
void prim (graph *G, int startingPoint) {
    int i;  // counter
    int T_prim_i = 1;
    edgeNode *P;    // temporary pointer
    bool intree[MAXV+1];    // is the vertex in the tree yet?
    int distance[MAXV+1];   // cost of adding to tree
    int v;                  // current vertex to process
    int w;                  // candidate of next vertex
    int weight;             // edge weight;
    int dist;               // best current distance from start

    /* 
    @ initialising basic data sets.  
        none of vertex is selected yet, so intree value for all vertices is set to false
        distance (i.e. cost of adding to tree) is set to some arbitrary number (maximum int)
        haven't yet selected/processed any node, so the parents are set to -1 (i.e no parent)
    */
    for (i=1; i<=G->nVertices; i++) {
        intree[i] = false;
        distance[i] = MAXINT;
        parent[i] = -1;

        T_prim[i] = -1;
    }

    distance[startingPoint] = 0;    // cost of adding the vertex to start with to tree is 0. this is obvious
    v = startingPoint;              // current vertex to process is startingPoint.

    while (intree[v] == false) {    // While (the current vertex to process is a nontree vertex)
        intree[v] = true;           // since we are processing this vertex v now, it is in tree
        T_prim[T_prim_i] = v;
        T_prim_i ++;

        P = G->edges[v];            // P now points to vertex v's adjacency list (i.e. outgoing edges from v)
        while (P != NULL) {         // iterating from all of v's adjacent edges
            w = P->v;               
            weight = P->weight;     // P->weight is the weight of vertex v to one of its adjacent edges
            if (distance[w] > (distance[v]+weight)) {
                distance[w] = distance[v]+weight;
                parent[w] = v;
            }
            P = P->next;
        }

        v = 1;
        dist = MAXINT;
        for (i=1; i<=G->nVertices; i++)
            if((intree[i] == false) && (dist > distance[i])) {
                dist = distance[i];
                v = i;
                cout << "going to: " << v << ", the dist is:" << dist << endl;
            }
        
    }
}

void tester () {
    graph *G = new graph;
    bool directed = false;
    char yn;
    cout << "is the graph directed? Enter y / n" << endl;
    cin >> yn;
    initialiseGraph(G, directed);
    readWeightedGraph(G, directed);
    printGraph(G);

    prim(G, 1);
    printPrim(G);
}
int main () {
    char yn = 'y';
    while(yn == 'y') {
        tester();   // user input prompted to create a graph and print the adjacency lists
        cout << "Run again? Enter y / n" << endl;
        cin >> yn;
    }
return 0;
}