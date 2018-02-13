// readData.c
// Used to:
// 		-get collection of urls
//		-get a graph with urls as nodes
//		-get inverted index
//
// Written By Benny Hwang Jan 2018

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "readData.h"
#include "LinkedList.h"

#define MAXLENGTH 100

LList getCollection(){
	FILE *collection = fopen("./collection.txt", "r");

	char line[MAXLENGTH];
	LList urlList = newLList();
	while(!feof(collection) && (fscanf(collection, "%s", line) == 1)){
		urlList = append(urlList, line);
	}
	fclose(collection);
	
	return urlList;
}


Graph getGraph(LList urlList){
	// find the number of nodes in the graph required and initialise graph
	int nURLS = lenLL(urlList);
	Graph g = newGraph(nURLS);

	// Get the first node to start the loop
	NodeT current = getHead(urlList);
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
		// read while section 1
		while(fscanf(op, "%s", line)==1){
			if(strcmp(line,"#start")==0 || strcmp(line, "Section-1")==0){
				continue;
			}
			if(strcmp(line, "#end")==0){
				break;
			}
			
			insertEdge(g, getURL(current), line);
		}
		current = getNext(current);
		fclose(op);
	}
	return g;
}
