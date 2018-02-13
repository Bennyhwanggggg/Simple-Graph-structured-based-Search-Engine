/*
SearchPagerank.c

Given command line arguments, search for those word in the  collection and output top 30.

By Benny Hwang  Jan 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include <assert.h>
#include "readData.h"
#include "charOp.h"
#include "AdjList.h"

#define MAXLENGTH 10000
#define ASCN 5
#define DSCN 6
#define PRASC 1
#define PRDSC 2

// Adjacency List structure to store a word and its urls.
typedef struct wordNode *NodeW;
typedef struct WordNodesRep *WordLRep;

WordLRep findMatchedUrls(WordLRep, char *q);
void findPagerank(LList);

int main(int argc, char *argv[]){
	if(argc<2){
		// printf("No search term entered.\n");
		return EXIT_FAILURE;
	}
	WordLRep wL = newWordL();
	int i;
	// Get all the urls where the search term appeared
	for(i = 1; i<=argc-1; i++){
		char *query = removeSpace(argv[i]);
		toLower(query);
		removeTrailingPunc(query);
		wL =findMatchedUrls(wL, query);
	}

	if(lenWLL(wL)==0){
		//printf("No words found\n");
		return EXIT_SUCCESS;
	}

	//showWLL(wL);
	
	// Count how many times each search term appeared by going through wL and add each new item to matchedURLSwPR
	LList matchedURLSwPR = newLList();
	NodeW current = getWHead(wL);
	while(current != NULL){
		LList matchURl = getURLists(current);

		NodeT curURlNodes = getHead(matchURl);
		while(curURlNodes != NULL){
			// search for the node in the list
			if(searchNodeID(matchedURLSwPR, getURL(curURlNodes))==-1){
				// set count to 1 and add it to the list
				NodeT new = makeNode(getURL(curURlNodes), 1);
				appendNode(matchedURLSwPR, new);
			} else {
				// Increase the count if it was already in the list
				changeNodeID(matchedURLSwPR, getURL(curURlNodes));
			}
			curURlNodes = getNext(curURlNodes);
		}
		current = getWNext(current);
	}

	// Insert pagerank value and print out top results based on number of search term found and page rank.
	findPagerank(matchedURLSwPR);
	freeLL(matchedURLSwPR);
	freeWLL(wL);
	
	return EXIT_SUCCESS;

}

void findPagerank(LList matchedURLSwPR){
	NodeT current = getHead(matchedURLSwPR);
	double pR;
	char line[MAXLENGTH];
	char strline[MAXLENGTH];

	// Insert pagerank values based on pagerankList.txt
	while(current != NULL){
		FILE *op = fopen("./pagerankList.txt","r");
		if(op == NULL){
			printf("Could not open the file.\n");
			return ;
		}
		// Go through the file unti the url is found
		char *currentURL = getURL(current);
		int reader = 1;
		while(fscanf(op, "%s", line) == 1){

			char *str = removeSpace(line);
			toLower(str);
			removeTrailingPunc(str);

			// Change reader value from 0 if the url is found
			if(reader != 0){
				reader = strcmp(str, currentURL);
			}
			// If url is found, extract its pagerank value
			if (reader == 0){
				fgets(strline, MAXLENGTH, op);
				char *b = strtok(strline, " ");
				char *prev;
				while(b != NULL){
					prev = b;
					b ++;
					b = strtok(NULL, " ");
				}
				char *cleanB = removeSpace(prev);
				toLower(cleanB);
				removeTrailingPunc(cleanB);
				pR = atof(cleanB);
				insertPR(current, pR);
				break;
			}

		}
		current = getNext(current);
		fclose(op);
	}
	
	// Sort by number of search time in the page
	matchedURLSwPR = insertionSort(matchedURLSwPR, DSCN);
	//showLL(matchedURLSwPR);	// testing
	// Output the result by creating a new list and insert based on the required order of number of search termed found first then pagerank
	LList pRLList = newLList();
	current = getHead(matchedURLSwPR);
	NodeT next = getNext(current);
	while(current != NULL){

		// If only one url found, simply add that url to the final output list
		if(next == NULL){
			// If url not already in the list, add it
			if(searchNodeID(pRLList, getURL(current))== -1){
				pRLList = append(pRLList, getURL(current));
				//printf("Next is Null\n");
				break;
			}
			current = next;
		} else {
			// If the pages have the same amount of search term found
			if(getID(current) == getID(next)){
				// create a new list that will contain all the nodes with that same number of search term but this list will be sorted based on pagerank
				LList prSortList = newLList();
				NodeT cpy = copyNode(current);
				prSortList = appendNode(prSortList, cpy);
				// add all nodes with the same number of searchterm
				while(getID(current) == getID(next)){
					cpy = copyNode(next);
					prSortList = appendNode(prSortList, cpy);

					current = next;
					next = getNext(next);
					if(next == NULL){
						break;
					}
				}
				// sort by pagerank
				prSortList = insertionSort(prSortList, PRDSC);

				// add this sorted by pagerank this into the main output list				
				NodeT prSortCurr = getHead(prSortList);
				while(prSortCurr != NULL){
					if(searchNodeID(pRLList, getURL(prSortCurr))== -1){
						pRLList = append(pRLList, getURL(prSortCurr));
					}
					prSortCurr = getNext(prSortCurr);
					
				}
			} else {
				// Otherwise just add and move on to next url with next largest number of search term found
				if(searchNodeID(pRLList, getURL(current))== -1){
					pRLList = append(pRLList, getURL(current));
				}
				current = next;
				next = getNext(next);
			}
		}

	}
	int count = 0;
	// Show top 30 pages
	current = getHead(pRLList);
	while(current != NULL && count < 30){
		printf("%s\n", getURL(current));
		current = getNext(current);
		count ++;
	}
}

WordLRep findMatchedUrls(WordLRep wL, char *queryWord){

	FILE *op = fopen("invertedIndex.txt", "r");
	if(op == NULL){
		printf("Could not open the file.\n");
		return NULL;
	} 
	LList urlList = newLList();
	char line[MAXLENGTH];
	char str[MAXLENGTH];
	int reader = 1;
	NodeW new;
	while(fscanf(op, "%s", line) == 1){
		// change reader if we find the word we want
		if (reader != 0){
			reader = strcmp(line, queryWord);
		}
		// when word is found, add all the url into the word list
		if (reader==0){

			fgets(str, MAXLENGTH, op);

			char *indivURLs = strtok(str, " \n");
			while(indivURLs != NULL){

				append(urlList, indivURLs);
				indivURLs ++;
				indivURLs = strtok(NULL, " \n");
			}
			new = newWordNode(queryWord, urlList);
			break;
		}
			
	}
	fclose(op);
	// add the urls to the main list if any url is found
	if(reader == 0){
		wL = appendW(wL, new);
	}

	return wL;
}