# Simple-Graph-structured-based-Search-Engine
A search engine using a simplified version of Google's page rank algorithm

You need to modify the makefile for each section accordingly to compile.

Part-A: Calculate PageRanks
Using the the page rank algorithm described in https://en.wikipedia.org/wiki/PageRank, calculate PageRank for every url in the file collection.txt and output the result into pagerankeList.txt. 

Part-B: Inverted Index
inverted.c will read data from a given collection of pages in collection.txt and generates an "inverted index" that provides a sorted list (set) of urls for every word in a given collection of pages. Before inserting words into index, they are "normalised" by,
removing leading and trailing spaces, converting all characters to lowercase, remove the following punctuation marks, if they appear at the end of a word:
'.' (dot), ',' (comma), ';' (semicolon), ? (question mark)
In each sorted list (set), duplicate urls are not allowed. Your program should output this "inverted index" to a file named invertedIndex.txt. One line per word, words should be alphabetically ordered, using ascending order. Each list of urls (for a single word) should be alphabetically ordered, using ascending order.

Part-C: Search Engine
A simple search engine using searchPagerank.c that given search terms (words) as
commandline arguments, finds pages with one or more search terms and outputs (to stdout) top 30
pages in descending order of number of search terms found and then within each group, descending
order of PageRank. If number of matches are less than 30, output all of them.
The program must use data available in two files invertedIndex.txt and pagerankList.txt, and
must derive result from them.
