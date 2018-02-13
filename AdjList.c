/*
Linked list Implementation

Used to store words and the urls they are in

by Benny Hwang  Jan 2018
*/

#include "AdjList.h"
#include "LinkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// A word node will contain its word and urls it is found in
struct wordNode {
	char *word;
	LList urls;
	NodeW next;
};

struct WordNodesRep{
	NodeW head;
	NodeW tail;
	int nitems;
};

// create new word node
NodeW newWordNode(char *newWord, LList urlList){
	NodeW new = malloc(sizeof(struct wordNode));
	assert(new != NULL);
	new->word = strdup(newWord);
	new->urls = urlList;
	new->next = NULL;
	return new;
}

// create new word list
WordLRep newWordL(){
	WordLRep new = malloc(sizeof(struct WordNodesRep));
	assert(new != NULL);
	new->head = NULL;
	new->nitems = 0;
	return new;
}

// Add new word to linked list
WordLRep appendW(WordLRep L, NodeW new){
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

void showWLL(WordLRep L){
	assert(L != NULL);
	NodeW current = L->head;
	while(current != NULL){
		printf("%s - ", current->word);
		showLL(current->urls);
		current = current->next;
	}
}

// free the whole linked list from memory
void freeWLL(WordLRep L){
	assert(L != NULL);

	NodeW current = L->head;
	NodeW temp;
	while(current!=NULL){
		temp = current->next;
		free(current);
		current = temp;
	}
	free(L);
}

NodeW getWHead(WordLRep L){
	return (L->head);
}

NodeW getWNext(NodeW n){
	return (n->next);
}

// count numbe rof nodes in the list
int lenWLL(WordLRep L){
	return (L->nitems);
}

LList getURLists(NodeW node){
	return (node->urls);
}