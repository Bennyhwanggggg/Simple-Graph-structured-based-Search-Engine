// Binary Search Tree ADT interface ... COMP9024 18x1 Lecture Material (Week 6)
#ifndef BSTREE_H
#define BSTREE_H
#include <stdbool.h>
#include <stdio.h>

typedef struct Node *Tree;

Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree
void showTree(Tree);   // display a Tree (sideways)
void outPutTree(Tree, FILE *); // output tree to a file

bool TreeSearch(Tree, char *);   // check whether an item is in a Tree
int  TreeNumNodes(Tree);       // count #nodes in Tree
Tree TreeInsert(Tree, char *, char *);   // insert a new item into a Tree
Tree TreeDelete(Tree, char *);   // delete an item from a Tree

// internal functions made visible for testing
Tree rotateRight(Tree);
Tree rotateLeft(Tree);
Tree partition(Tree, int);
Tree rebalance(Tree);

#endif