// Singly Linked List ADT Interface
// Written By Benny Hwang Jan 2018

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>

typedef struct LListRep *LList;

typedef struct node *NodeT;

NodeT makeNode(char *, int);
LList newLList();
void freeLL(LList);
void showLL(LList);
LList append(LList, char *);
LList appendNode(LList, NodeT);
LList deleteHead(LList);
LList deleteTail(LList);
LList deleteByID(LList, int);
int searchNodeID(LList, char *);
char *searchNodeURL(LList, int);
int lenLL(LList);
void changeNodeID(LList, char *);

int getID(NodeT);
NodeT getHead(LList);
NodeT getNext(NodeT);
NodeT getTail(LList);
char *getURL(NodeT);
void insertPR(NodeT, double);
double getPR(NodeT);
NodeT copyNode(NodeT);

void swapNodes(LList, NodeT, NodeT);
void sortedInsert(LList, NodeT, int);
LList insertionSort(LList, int);

#endif