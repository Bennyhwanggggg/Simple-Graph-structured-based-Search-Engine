/* pagerank.c
Reads data from a given collection of pages in the file collection.txt and builds a graph structure using Adjacency Matrix.
Use a simplfied page rank algorithm to calculate page rank for every URL in the file collection.txt.
In collection.txt, every urls are separated by one or more spaces or new line character.

By Benny Hwang Jan 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "LinkedList.h"
#include "readData.h"
#include <math.h>
#include <stdbool.h>

#define ASC 1
#define DSC 2

double innerDiff(double a[], double b[], int n);
void PageRank(double d, double diffPR, int maxIterations);

int main(int argc, char *argv[]){
	if(argc != 4){
		printf("Input invalid\n");
		return EXIT_FAILURE;
	}
	// parameters setup.
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);
	int maxIterations = atoi(argv[3]);
	PageRank(d, diffPR, maxIterations);

	return EXIT_SUCCESS;
}


void PageRank(double d, double diffPR, int maxIterations){
	LList urlsList = getCollection();
	/*
	printf("URL linked list:\n");

	showLL(urlsList);
	printf("\nNOTE: Linked List ID will be different from Graph Vertex IDs\n");
	putchar('\n');

	printf("URL Graph:\n");
	*/
	Graph urlsGraph = getGraph(urlsList);
	//showGraph(urlsGraph);
	//putchar('\n');
	
	int nURLS = lenLL(urlsList);
	double N = (double) nURLS;	// convert nURLS to double for calculation purpose.
	
	// Initialize array to store PR of previous iteration and new iteration.
	double prevPR[nURLS];
	double newPR[nURLS];

	int i, j; // intergers used for loops.
	// For each url in the collection, set PR to 1/N.
	for(i=0; i<nURLS; i++){
		prevPR[i]=1/N;
		newPR[i] = 0;
	}

	int iteration = 0;
	double diff = diffPR;
	double constant = (1.0-d)/N;

	while(iteration < maxIterations && diff >= diffPR){
		iteration++;
		// For each node, find all the PR of connected node and sum those pR and divide it by the outdegree of that node.
		for(i=0; i<nURLS; i++){

			for(j=0; j<nURLS; j++){
				if(isLinked(urlsGraph, j, i)){
					newPR[i] += prevPR[j]/findDegWithID(urlsGraph,j);
				}
			}
			newPR[i] = constant + d*newPR[i];
		}
		diff = innerDiff(newPR, prevPR, nURLS);

		// setup newPR and prevPR
		NodeT current = getHead(urlsList);
		for(i=0; i<nURLS; i++){
			//insertPR(current, newPR[i]);
			prevPR[i] = newPR[i];
			newPR[i] = 0;
			current = getNext(current);
		}
	}


	// insert each page's PR into their respective nodes.
	NodeT curr_node = getHead(urlsList);
	while(curr_node != NULL){
		// insert page ranking into linked list, need to match the graph's id with linked lists' id.
		insertPR(curr_node, prevPR[findVertexID(urlsGraph,getURL(curr_node))]);
		curr_node = getNext(curr_node);
	}
	
	// sort the linked list in descending order
	LList sortedList = insertionSort(urlsList, DSC);

	// Create pagerankList.txt output file and put required info in there.
	FILE *output = fopen("./pagerankList.txt", "w");
	curr_node = getHead(sortedList);
	while(curr_node != NULL){
		fprintf(output, "%s, %d, %.7f\n", getURL(curr_node), findDegrees(urlsGraph, getURL(curr_node)), getPR(curr_node));
		curr_node = getNext(curr_node);
	}
	fclose(output);

	// destroy everything
	freeLL(urlsList);
	freeLL(sortedList);
	freeGraph(urlsGraph);
}



// sum the difference between every element in two arrays
double innerDiff(double a[], double b[], int n){
	int i;
	double sums = 0;
	for(i=0; i<n; i++){
		sums += fabs(a[i]-b[i]);
	}
	return sums;
}
