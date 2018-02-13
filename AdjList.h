// Linked list Interface  from COMP9024 18x1 Lecture Material
// Used to store words and the urls they are in
// Modified by Benny Hwang  Jan 2018

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

typedef struct wordNode *NodeW;
typedef struct WordNodesRep *WordLRep;

NodeW newWordNode(char *, LList);
WordLRep newWordL();
WordLRep appendW(WordLRep, NodeW);
void freeWLL(WordLRep);
NodeW getWHead(WordLRep);
NodeW getWNext(NodeW);
int lenWLL(WordLRep);
void showWLL(WordLRep);
LList getURLists(NodeW);


