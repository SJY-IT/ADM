// Code ref: ADM pg. 153
// Node start from 1 for convenience.
// notice MAXV is 1000 but the *edges[] is initialised with 1001 slots
// in initialiseGraph, we initialise the adjacency list from 1 to 1000
#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define MAXV 1000           // Maximum number of vertices
bool discovered[MAXV+1];
bool processed[MAXV+1];
int parent[MAXV+1];
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
void insertEdge (graph *G, int u, int v, bool D) {
    edgeNode *P = new edgeNode;     // temporary pointer to new edgeNode
    P->v = v;
    P->weight = 0;
    
    P->next = G->edges[u];          
    G->edges[u] = P;                // insert at head of list
    
    G->degree[u] ++;
    
    if (D == false)
        insertEdge(G, v, u, true);
    else
        G->nEdges ++;       
}
void readGraph (graph *G, bool D) {
    int m;      // number of edges
    int u, v;   // vertices in edge (u,v)

    initialiseGraph(G, D);
    cout << "Enter the number of vertices and edges of the graph (separate each value by space)" << endl;
    cin >> G->nVertices >> m;
    
    for (int i=1; i<=m; i++) {
        cout << "Enter the vertices in edge (u,v) (separate each value by space)" << endl;
        cin >> u >> v;
        insertEdge(G, u, v, D);
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
void initialiseSearch (graph*G) {
    // initialise every vertex to be marked as undiscovered and not processed
    // initialise every vertex with no parent to start with
    for (int i=1; i<=G->nVertices; i++) {
        discovered[i] = processed[i] = false;
        parent[i] = -1;
    }
}
void findPath(int start, int end, int parent[]) {
    if( (start == end) || (end == -1) )
        cout << start << endl;
    else {
        findPath(start, parent[end], parent);
        cout << end << endl;
    }
}
void processVertexLate (int u) {
}
void processVertexEarly (int u) {
    //cout << "processed vertex " << u << endl;
    cout << u << " ";
}
void processEdge(int u, int v) {
    //cout << "processed edge (" << u << "," << v << ")" << endl;
}
void BFS (graph *G, int start) {
    queue <int> Q;      // a queue of vertices to be processed
    int u;              // current vertex, becomes the parent of v
    int v;              // next vertex, this would be Adj[u]
    edgeNode *p;        // temporary pointer
    
    Q.push(start);
    discovered[start] = true;
    while(!Q.empty()) {
        //cout << "dequeue: " << Q.front() << endl;
        u = Q.front();
        Q.pop();

        processVertexEarly(u);
        processed[u] = true;
        
        p = G->edges[u];    // G->edges[u] is Adj[u]
        while(p != NULL) {
            v = p->v;
            if ( (processed[v] == false) || G->directed)
                processEdge(u,v);
            if (discovered[v] == false) {
                //cout << "enqueue: " << v << endl;
                Q.push(v);
                discovered[v] = true;
                parent[v] = u;
            }
            p = p->next;
        }
        processVertexLate(u);
    }
}/*
void connectedComponents (graph *G) {
    int c = 0;  // component number
    initialiseSearch(G);
    for (int i=1; i<=G->nVertices; i++) {
        if (discovered[i] == false) {
            c++;
            cout << "Component" << c << ":";
            BFS(G, i);
            cout << endl;
        }
    }
}
*/
void tester () {
    graph *G = new graph;
    bool directed = false;
    char yn;
    cout << "is the graph directed? Enter y / n" << endl;
    cin >> yn;
    initialiseGraph(G, directed);
    readGraph(G, directed);
    printGraph(G);

    initialiseSearch (G);
    BFS(G, 1);
    cout << endl;
    //connectedComponents(G);
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