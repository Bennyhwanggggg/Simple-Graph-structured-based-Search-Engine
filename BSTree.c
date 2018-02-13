// Binary Search Tree ADT implementation ... COMP9024 18x1 Lecture Material (Week 6)
// Modified by Benny Hwang Jan 2018.

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BSTree.h"
#include "LinkedList.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

#define ASC 3
#define DSC 4

typedef struct Node {
   char  *data;
   LList url;
   Tree left, right;
} Node;

// make a new node containing data
Tree newNode(char *word, char *newURL) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   data(new) = strdup(word);
   new->url = newLList();
   append(new->url, newURL);
   left(new) = right(new) = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      freeLL(t->url);
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++){
         putchar('\t');            // TAB character
         printf("%s\n", data(t));
         showTreeR(left(t), depth+1);
         showLL(t->url);
      }
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}

void outPutTree(Tree t, FILE *f){
   if(t==NULL){
      return;
   }
   outPutTree(left(t), f);
   fprintf(f, "%s ", t->data);
   LList sortedURLS = insertionSort(t->url, ASC);
   NodeT current = getHead(sortedURLS);
   while(current != NULL){
      fprintf(f, " %s", getURL(current));
      current = getNext(current);
   }
   fprintf(f, "\n");
   outPutTree(right(t), f);
}

// count #nodes in Tree
int TreeNumNodes(Tree t) {
   if (t == NULL)
      return 0;
   else
      return 1 + TreeNumNodes(left(t)) + TreeNumNodes(right(t));
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, char *str) {
   if (t == NULL)
      return false;
   else if (strcmp(str, data(t)) < 0){
      return TreeSearch(left(t), str);
   } else if (strcmp(str, data(t)) > 0){
      return TreeSearch(right(t), str);
   } else {                                 // it == data(t)
      return true;
   }
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, char *str, char *URL) {
   if (t == NULL)
      t = newNode(str, URL);
   else if (strcmp(str, data(t)) < 0){
      left(t) = TreeInsert(left(t), str, URL);
   } else if (strcmp(str, data(t)) > 0){
      right(t) = TreeInsert(right(t), str, URL);
   } else {
      // Don't allow duplicated URL to be inserted.
      if (searchNodeID(t->url, URL)== -1){
         append(t->url, URL);
      }
   }
   return t;
}

Tree joinTrees(Tree t1, Tree t2) {
   if (t1 == NULL){
      return t1;
   } else if (t2 == NULL){
      return t2;
   }
   else {
      Tree curr = t2;
      Tree parent = NULL;
      while (left(curr) != NULL) {    // find min element in t2
	     parent = curr;
	     curr = left(curr);
      }
      if (parent != NULL) {
	     left(parent) = right(curr);  // unlink min element from parent
	     right(curr) = t2;
      }
      left(curr) = t1;
      return curr;                    // min element is new root
   }
}

// delete an item from a Tree
Tree TreeDelete(Tree t, char *str){
   if(t != NULL){
      // Move left or right until we find what we want to delete
      if(strcmp(str, data(t)) < 0){
         left(t) = TreeDelete(left(t), str);
      } else if(strcmp(str, data(t))){
         right(t) = TreeDelete(right(t),str);
      } else { 
         // When we want to delete a node
         Tree new;
         if(left(t) == NULL && right(t)== NULL){
            new = NULL;
         } else if(left(t) == NULL){
            new = right(t);
         } else if(right(t) == NULL){
            new = left(t);
         } else {
            new = joinTrees(left(t), right(t));
            t = new;
         }
      }
   }
   return t;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

Tree partition(Tree t, int i) {
   if (t != NULL) {
      assert(0 <= i && i < TreeNumNodes(t));
      int m = TreeNumNodes(left(t));
      if (i < m) {
	     left(t) = partition(left(t), i);
	     t = rotateRight(t);
      } else if (i > m) {
	     right(t) = partition(right(t), i-m-1);
	     t = rotateLeft(t);
      }
   }
   return t;
}

Tree rebalance(Tree t) {
   int n = TreeNumNodes(t);
   if (n >= 3) {
      t = partition(t, n/2);           // put node with median key at root
      left(t) = rebalance(left(t));    // then rebalance each subtree
      right(t) = rebalance(right(t));
   }
   return t;
}
