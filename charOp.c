/*
charOp.c 
Provides function to normalise a string

Written by Benny Hwang Jan 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "charOp.h"

// remove trailing and leading space in a string
char *removeSpace(char *str){
	// remove leading space
	while(isspace(*str)){
		str ++;
	}

	// if all white space
	if(*str == '\0'){
		return str;
	}

	char *end = str + strlen(str) - 1;
	while(isspace(*end)){
		end --;
	}
	*(end+1) = '\0';
	return str;
}

// Convert a string to all lower case
void toLower(char *str){
	int i;
	for(i=0; str[i] != '\0'; i++){
		str[i] = tolower(str[i]);
	}
}

void removeTrailingPunc(char *str){
	char *end = str + strlen(str) - 1;
	// if the trailing character is either of these, removed it by changing end position
	while(*end == '.' || *end == ',' || *end == ';' || *end == '?'){
		end --;
	}
	*(end+1) = '\0';

}
