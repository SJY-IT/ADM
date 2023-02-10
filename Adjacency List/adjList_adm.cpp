// Code ref: ADM pg. 153
// Node start from 1 for convenience.
// notice MAXV is 1000 but the *edges[] is initialised with 1001 slots
// in initialiseGraph, we initialise the adjacency list from 1 to 1000
#include <iostream>
using namespace std;

#define MAXV 1000           // Maximum number of vertices

struct edgeNode {
    int y;                  // adjacency Info
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
    P->y = y;
    P->weight = 0;
    
    P->next = G->edges[x];          
    G->edges[x] = P;                // insert at head of list
    
    G->degree[x] ++;
    
    if (D == false)
        insertEdge(G, y, x, true);
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
void printGraph (graph *G) {
    edgeNode *P;    // temporary pointer to edgeNode
    for (int i=1; i<=G->nVertices; i++) {
        cout << "[" << i << "]: ";
        P = G->edges[i];
        while (P != NULL) {
            cout << P->y << "->";
            P = P->next;
        }
        cout << "NULL"; 
        cout << endl;
    }
}
void tester () {
    graph *G = new graph;
    bool directed = false;
    char yn;
    cout << "is the graph directed? Enter y / n" << endl;
    cin >> yn;
    initialiseGraph(G, directed);
    readGraph(G, directed);
    printGraph(G);
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