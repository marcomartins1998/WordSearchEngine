/*
 * search2.c
 *
 *  Created on: Nov 21, 2019
 *      Author: isel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "translate.h"
#include "split.h"
#include "textread.h"
#include "index.h"

int cmpOcurrencesByFileNum(const void * elem1, const void * elem2);

int numFiles;
char **fileNames;

int searchStart(int numOfFiles, const char *fileNamesArr[]){
	numFiles = numOfFiles;
	fileNames = (char**) fileNamesArr;
	indexStart();
	int i;
	for(i = 1; i < numFiles; i++){
		textStart(fileNames[i]);
		char * str;
		char * dst = malloc(4000);
		long offset = 0;
		int line = 1;
		while((str = textLine(&offset)) != NULL){
			printf("File: %d, LineCount: %d\n", i, line);
			translate_string(str, dst);
			char * token = splitStart(dst);
			while(token != NULL){
				indexAddWord(token, i, line, offset);
				token = splitNext();
			}
			splitEnd();
			line++;
		}
		free(str);
		free(dst);
		textEnd();
	}
	return numFiles;
}

char *searchWord(char *word){
	Word* w = indexFindWord(word);
	if(w != NULL){
		printf("Occurences of '%s': %d\n", word, w->count);
		int i, fileidx = -1;
		//qsort(w->occur, w->count, sizeof(Occurence), cmpOcurrencesByFileNum);
		for(i = 0; i < w->count; i++){
			if(fileidx != w->occur[i].fileIdx){
				fileidx = w->occur[i].fileIdx;
				textEnd();
				textStart(fileNames[fileidx]);
				printf("File name: %s\nLine number: %d\nOriginal text: %s\n", fileNames[fileidx], w->occur[i].line, textLocatedLine(w->occur[i].offset));
			} else {
				printf("Line number: %d\nOriginal text: %s\n", w->occur[i].line, textLocatedLine(w->occur[i].offset));
			}
		}
		textEnd();
	}
	return word;
}

void searchEnd(void){
	//TODO Adicionar proteção se o user usar searchStart enquanto que o search anterior ainda não acabou??
	indexEnd();
	numFiles = 0;
	fileNames = NULL;
}

int cmpOcurrencesByFileNum(const void * elem1, const void * elem2){
	return ((Occurence *) elem1)->fileIdx - ((Occurence *) elem2)->fileIdx;
}

