// Graph ADT interface ... COMP9024 18x1
// Modified by Benny Hwang Jan 2018.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct GraphRep *Graph;

Graph newGraph(int);
int insertEdge(Graph, char *, char *);
int addVertex(Graph, char *, char **, int);
void removeEdge(Graph, char *, char *);
int findVertexID(Graph, char *);
bool validV(Graph, int);
bool adjacent(Graph, char *, char *);
bool isLinked(Graph, int, int);
int verticesCount(Graph);
int findDegrees(Graph, char *);
int findDegWithID(Graph, int);
void  showGraph(Graph);
void  freeGraph(Graph);

#endif