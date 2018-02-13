/*
inverted.c

-Reads data from a given collection of pages in collection.txt and generate an inverted index that provides a sorted list of urls for every word in a given collection of pages. 
- Normalise each word by removing leading and trailing spaces, and converting all characters to lower case and removing the following punctuation marks: . , ; ?
- No duplicate in each list.

By Benny Hwang Jan 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "readData.h"
#include "BSTree.h"
#include "LinkedList.h"
#include "charOp.h"

#define MAXLENGTH 10000

Tree GetInvertedList(Tree, LList);

int main(void){

	LList urlsList = getCollection();
	Tree urlTree = newTree();
	urlTree = GetInvertedList(urlTree, urlsList);
	FILE *output = fopen("./invertedIndex.txt","w");
	if(output == NULL){
		printf("Could not open the file.");
		return EXIT_FAILURE;
	}
	outPutTree(urlTree, output);
	fclose(output);
	freeLL(urlsList);
	freeTree(urlTree);
	return EXIT_SUCCESS;
}


Tree GetInvertedList(Tree t, LList L){
	if(L==NULL){
		return t;
	}

	// Get the first node to start the loop
	NodeT current = getHead(L);
	while(current != NULL){
		char *urlstr = strdup(getURL(current));
		strcat(urlstr, ".txt");
		// open each individual file
		FILE *op = fopen(urlstr, "r");
		if(op ==NULL){
			printf("Could not open the file %s\n", urlstr);
			return NULL;
		}
		char line[MAXLENGTH];
		int reader = 1;
		// read while section 1
		while(fscanf(op, "%s", line)==1){
			if(reader != 0){
				reader = strcmp(line, "Section-2");
			}
			if(strcmp(line, "#end")==0 && reader == 0){
				break;
			}
			if(reader == 0 && strcmp(line, "Section-2")){
				// normalise the character then add to tree
				char *normLine = removeSpace(line);
				removeTrailingPunc(normLine);
				toLower(normLine);
				if(strlen(normLine)>0){
					t = TreeInsert(t, normLine, getURL(current));
				}
			}
		}
		current  = getNext(current);
		fclose(op);
	}
	return t;
}
