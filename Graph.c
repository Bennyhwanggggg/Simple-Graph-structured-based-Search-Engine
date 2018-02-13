// Graph ADT
// Adjacency Matrix Representation ...
// by Benny Hwang Jan 2018.

#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct GraphRep {
  unsigned char **edges;   // adjacency matrix
  char **vertices;
  int nV;      // vertex number
  int maxV;    // maximum number of vertices
  int nE;      // #edges
} GraphRep;

// Create a new empty graph.
Graph newGraph(int maxV) {
  assert(maxV >= 0);
  int i;

  Graph g = malloc(sizeof(GraphRep));
  assert(g != NULL);
  g->maxV = maxV;
  g->nV = 0;
  g->nE = 0;

  // allocate memory for each row
  g->edges = malloc(maxV * sizeof(unsigned char *));
  assert(g->edges != NULL);
  g->vertices = malloc(maxV * sizeof(char *));
  assert(g->vertices != NULL);
   
  // allocate memory for each column and initialise with 0
  for (i = 0; i < maxV; i++) {
    g->vertices[i] = NULL;
    g->edges[i] = calloc(maxV, sizeof(unsigned char));
    assert(g->edges[i] != NULL);
  }

  return g;
}

// Adds a vertex to a graph
// Input: string, vertexIDs, and index.
// Output: the vertexID (the string's position in the array). Return -1 if exceeding number of vertices
int addVertex(Graph g, char *str, char *vertexIDs[], int vNum) {
  if(vNum>=g->maxV){
    return -1;
  }
  // Copy the string into appointed index in the array.
  vertexIDs[vNum] = strdup(str);
  g->nV ++;
  return vNum;
}

// Find a string's ID in vertexIDs
// Input: string, graph
// Output: integer (vertexID), -1 if string not found.
int findVertexID(Graph g, char *str){//, int N)
  int i;
  for(i=0; i<g->nV; i++){
    if(strcmp(str, g->vertices[i])==0){
      return i;
    }
  }
  return -1;
}  

// check if vertex is valid in a graph
bool validV(Graph g, int v) {
  return (g != NULL && v >= 0 && v < g->maxV);
}

// Insert an edge.
// Input: graph, src (string), dest(string)
// Output: return 1 if insert successful
//         return 0 if insert failed. (e.g loop, edge already in graph, number of vertices exceed maximum allowed)
// void insertEdge(Graph g, Edge e) {
int insertEdge(Graph g, char *src, char *dest) {
  // assert(g != NULL && validV(g,e.v) && validV(g,e.w)); 
  assert(g != NULL); // Possibly add check if vertex is in the graph or max limit? but we add vertex when adding an edge
  // Do not add loops
  if(strcmp(src,dest) == 0){
    return 0;
  }
  // Get the vertexIDs of src and dest. If not located in vertexIDs already, insert it.
  int srcID = findVertexID(g, src);
  int destID = findVertexID(g, dest);
  if(srcID<0){
    srcID = addVertex(g, src, g->vertices, g->nV);
    if(srcID == -1){
      return 0;
    }
  }
  if(destID<0){
    destID = addVertex(g, dest, g->vertices, g->nV);
    if(destID == -1){
      return 0;
    }
  }
  // Add if edge not already in the graph
  if(!g->edges[srcID][destID]){
    g->edges[srcID][destID] = 1;
    g->nE++;
    return 1;
  }
  return 0;
}

// remove an edge
// Input: graph, vertex (from), vertex (to)
void removeEdge(Graph g, char *src, char *dest) {
  assert(g != NULL);
  int v = findVertexID(g, src);
  int w = findVertexID(g, dest);
  if(validV(g,v) && validV(g,w)){
    if (g->edges[v][w]) {   // edge e in graph
      g->edges[v][w] = 0;
      g->nE--;
    }
  }
}

// check if two vertices are connected.
bool adjacent(Graph g, char *src, char *dest) {
  assert(g!=NULL);
  //assert(g != NULL && validV(g,v) && validV(g,w));
  int v = findVertexID(g, src);
  int w = findVertexID(g, dest);
  if(validV(g,v) && validV(g,w) && v!=w){
    return (g->edges[v][w] != 0);
  }
  return false;
}

bool isLinked(Graph g, int v, int w) {
  assert(g!=NULL);
  if(validV(g,v) && validV(g,w) && v!=w){
    return (g->edges[v][w] != 0);
  }
  return false;
}

// show the graph in matrix representation.
void showGraph(Graph g) {
  assert(g != NULL);
  int i, j;

  printf("Number of vertices: %d\n", g->nV);
  printf("Number of edges: %d\n", g->nE);
  putchar('\n');
  for(i = 0; i < g->nV; i++){
    printf("%s:", g->vertices[i]);
    for(j=0; j < g->nV; j++){
      printf(" %d", g->edges[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
  printf("Vertex ID dictionary:\n");
  for(i = 0; i < g->nV; i++){
    printf("%d: %s\n",i , g->vertices[i]);
  }
  /*
  for(i = 0; i < g->nV; i++){
    for (j = i+1; j < g->nV; j++){
    	if (g->edges[i][j]){
      	printf("Edge %s - %s\n", g->vertices[i], g->vertices[j]);
      }
    }
  }
  */
}

// destroys the graph
void freeGraph(Graph g) {
  assert(g != NULL);

  int i;
  for (i = 0; i < g->maxV; i++){
    free(g->edges[i]);
  }
  free(g->edges);
  for (i = 0; i < g->nV; i++)
    free(g->vertices[i]);
  free(g->vertices);
  free(g);
}

// count number of vertices in the graph
int verticesCount(Graph g){
  assert(g != NULL);
  return (g->nV);
}

// find the degree of a vertex.
// Input: graph, vertex
// Output degree
int findDegrees(Graph g, char *v){
  int deg = 0;
  int vID = findVertexID(g,v);
  int i;
  for(i=0; i < g->nV; i++){
    if(g->edges[vID][i]){
      deg ++;
    }
  }
  return deg;
}

// find a vertex's degree using id
int findDegWithID(Graph g, int v){
  int deg = 0;
  int i;
  for(i=0; i < g->nV; i++){
    if(g->edges[v][i]){
      deg ++;
    }
  }
  return deg;
}