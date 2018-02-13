/*
Singly Linked List Implementation

by Benny Hwang Jan 2018
*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"


// Initialise a self-referential type for the linked list structure
//typedef struct node{
struct node{
	int id;
	char *url;
	NodeT next;
	double prVal;
};

// Linked list representaiton.
//typedef struct LListRep {
struct LListRep {
	int nitems;		// count of items in list
	NodeT head;	// head node
	NodeT tail;	// last node
} LListRep;

// Create a node
NodeT makeNode(char *str, int val){
	NodeT new = malloc(sizeof(struct node));
	assert(new!=NULL);
	new->id = val;
	new->url = strdup(str);
	new->next = NULL;
	new->prVal = 0;
	return new;
}

// Create a new empty LList.
LList newLList(){
	LList new = malloc(sizeof(struct LListRep));
	assert(new != NULL);
	new->nitems = 0;
	new->head = NULL;
	new->tail = NULL;
	return new;
}

// free the whole linked list from memory
void freeLL(LList L){
	assert(L != NULL);

	NodeT current = L->head;
	NodeT temp;
	while(current!=NULL){
		temp = current->next;
		free(current);
		current = temp;
	}
	free(L);
}

// show the whole linked list
void showLL(LList L){
	if(L == NULL){
		return;
	}
	NodeT curr;
	for(curr = L->head; curr != NULL; curr = curr->next){
		printf("%d: %s - %.7f", curr->id, curr->url, curr->prVal);
		if(curr->next != NULL){
			printf(" -> ");
		}
	}
	putchar('\n');
}

// Append a url to the end of the linked list by creating a new node and appending that node.
// Input: Linked list, url string.
LList append(LList L, char *urlstr){
	NodeT new = makeNode(urlstr, L->nitems);	// give new node ID of the last number
	assert(new != NULL);
	if(L->head == NULL){ // If the linked list is currently empty, new node becomes head and only item
		L->head = new;
		L->tail = new;
		L->nitems++;
	} else { // Otherwise, add to end of the list and set new tail.
		L->tail->next = new;
		L->tail = new;
		L->nitems++;
	}
	return L;
}

// Apend a node to end of the list. Node need to be already created.
LList appendNode(LList L, NodeT new){
	if(new == NULL){
		return L;
	}
	if(L->head == NULL){ // If the linked list is currently empty, new node becomes head and only item
		L->head = new;
		L->tail = new;
		L->nitems++;
	} else { // Otherwise, add to end of the list and set new tail.
		L->tail->next = new;
		L->tail = new;
		L->nitems++;
	}
	return L;
}

// Delete the first node.
LList deleteHead(LList L){
	if(L->head == NULL){
		return L;
	}
	NodeT first = L->head;
	L->head = first->next;
	free(first);
	L->nitems --;
	return L;
}

LList deleteTail(LList L){
	if(L->tail == NULL){
		return L;
	}
	NodeT current = L->head;
	// If only one element
	if(current == L->tail){
		free(current);
	} else {
		NodeT previousToTail, last;
		// move to the second last element
		while(current->next != L->tail){
			current = current->next;
		}
		previousToTail = current;
		last = current->next;
		free(last);
		L->tail = previousToTail;
	}
	L->nitems --;
	return L;
}

LList deleteByID(LList L, int d){
	if(L==NULL){
		return L;
	} 
	NodeT current = L->head;
	NodeT prev;
	// Traverse through the list and find the id
	while(current->id != d && current->next != NULL){
		prev = current;
		current = current->next;
	}
	// if deleting at the start
	if(current == L->head){
		// If only element in the list and the ID doesn't match, just return L
		if(current->id != d){
			return L;
		} else {
			deleteHead(L);
		}
	}

	// if reached the end of the list
	if(current == L->tail){
		// If id not found
		if(current->id != d){
			return L;
		} else {
			return deleteTail(L);
		}
	}

	// if found the ID somwhere in the middle of the list
	prev->next = current->next;
	free(current);
	L->nitems --;
	return L;
}

// Find a url in the list and return its ID.
int searchNodeID(LList L, char *str){
	// if L is empty
	if(L==NULL){
		return -1;
	}
	NodeT current = L->head;
	while(current != NULL && strcmp(current->url,str)){
		current = current->next;
	}
	// if node not found
	if(current == NULL){
		return -1;
	}
	return (current->id);
}

// Find a ID in the list and return its url.
char *searchNodeURL(LList L, int d){
	// if L is empty
	if(L==NULL){
		return NULL;
	}
	NodeT current = L->head;
	while(current != NULL && current->id != d){
		current = current->next;
	}
	if(current == NULL){
		return NULL;
	}
	return (current->url);
}

int getID(NodeT n){
	return(n->id);
}

// find a node by its url and change its ID by 1
void changeNodeID(LList L, char *str){
	if(L==NULL){
		return;
	}
	NodeT current = L->head;
	while(current != NULL && strcmp(current->url,str)){
		current = current->next;
	}
	// if node not found
	if(current == NULL){
		return;
	}
	current->id ++;
}

// count numbe rof nodes in the list
int lenLL(LList L){
	return (L->nitems);
}

NodeT copyNode(NodeT toCopy){
	NodeT new = malloc(sizeof(struct node));
	assert(new!=NULL);
	new->id = toCopy->id;
	new->url = strdup(toCopy->url);
	new->next = NULL;
	new->prVal = toCopy->prVal;
	return new;
}

// return a list's head node
NodeT getHead(LList L){
	return (L->head);
}

NodeT getNext(NodeT n){
	return (n->next);
}

// return a list's tail node
NodeT getTail(LList L){
	return (L->tail);
}

char *getURL(NodeT n){
	assert(n != NULL);
	return (n->url);
}

// Insert page rank to a node
void insertPR(NodeT n, double val){
	n->prVal = val;
}

// retrieve the page rank of a node
double getPR(NodeT n){
	return (n->prVal);
}

// swap two nodes in a singly linked list.
void swapNodes(LList L, NodeT n1, NodeT n2){
	if(n1 == n2){
		return;
	}

	// Traverse through the list and find the first node while storing the previous node.
	NodeT prev1, current1 = L->head;
	while(current1 != NULL && current1 != n1){
		prev1 = current1;
		current1 = current1->next;
	}

	// Do the same for the second node
	NodeT prev2, current2 = L->head;
	while(current2 != NULL && current2 != n2){
		prev2 = current2;
		current2 = current2->next;
	}

	// If not both not found, we cannot swap.
	if(current1 == NULL || current2 == NULL){
		return;
	}

	// switch previous nodes link
	// When the node to swap is the head, make it the head. Otherwise, swap normally.
	if(prev1 == NULL){
		L->head = current2;
	} else { 
		prev1->next = current2;
	}

	if(prev2 == NULL){
		L->head = current1;
	} else {
		prev2->next = current1;
	}
	// switch next node link
	NodeT temp = current2->next;
	current2->next = current1->next;
	current1->next = temp;
}

// insert a node at appropriate location based on its PR, url or by id then PR
void sortedInsert(LList L, NodeT new, int mode){
	NodeT current = L->head;
	if(mode == 1 || mode == 2){
		// If inserting at the start of the list
		if(L->head == NULL || (current->prVal >= new->prVal && mode == 1) || (current->prVal <= new->prVal && mode == 2)){
			new->next = L->head;
			L->head = new;
		} else {
			// move to the node before location of insert so we can insert new node after it.
			if(mode == 1){
				while(current->next != NULL && current->next->prVal < new->prVal){
					current = current->next;
				}
			} else if(mode == 2){
				while(current->next != NULL && current->next->prVal > new->prVal){
					current = current->next;
				}
			}
			new->next = current->next;
			current->next = new;
		}
	} else if(mode == 3 || mode == 4){
		// 3 or 4 for sorting by URL, 3 for ascending, 4 for descendin
		if(L->head == NULL || (strcmp(current->url, new->url) > 0 && mode == 3) || (strcmp(current->url, new->url) < 0 && mode == 4)){
			new->next = L->head;
			L->head = new;
		} else {
			// move to the node before location of insert so we can insert new node after it.
			if(mode == 3){
				while(current->next != NULL && strcmp(current->next->url, new->url) < 0){
					current = current->next;
				}
			} else if(mode == 4){
				while(current->next != NULL && strcmp(current->next->url, new->url) > 0){
					current = current->next;
				}
			}
			new->next = current->next;
			current->next = new;
		}
	} else if (mode == 5 || mode == 6){
		// 5 or 6 for sorting by id, 5 for ascending, 6 for descending
		if(L->head == NULL || (current->id >= new->id && mode == 5) || (current->id <= new->id && mode == 6)){
			new->next = L->head;
			L->head = new;
		} else {
			// move to the node before location of insert so we can insert new node after it.
			if(mode == 5){
				while(current->next != NULL && current->next->id < new->id){
					current = current->next;
				}
			} else if(mode == 6){
				while(current->next != NULL && current->next->id > new->id){
					current = current->next;
				}
			}
			new->next = current->next;
			current->next = new;
		}
	}
}

// Use insertion sort to sort a singly linked list. Will modify the original.
// mode 1 = ascending order, mode 2 = descending order
LList insertionSort(LList L, int mode){
	assert(L != NULL);
	// Create a new list to put the sorted list in.
	LList sortedList = newLList();
	NodeT current = L->head;
	while(current != NULL){
		NodeT currNext = current->next;	// store next node
		// insert current node into sortedlist
		sortedInsert(sortedList, current, mode);
		current = currNext; // set next node.
	}
	return sortedList;
}


