/*
 * index4.c
 *
 *  Created on: Dec 30, 2019
 *      Author: isel
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

static Word * hlFind(Hlnode *node, Word word);
static void hlInsert(Hlnode **previous, Word word);
static int cmpWordByValue(const void * elem1, const void * elem2);

Hashtable ht;

void indexStart( void ){
	ht = (Hashtable){ 2000, malloc(2000 * sizeof(Hlnode*)) };
}

void indexAddOccur( Word *w, int fileIdx, int line, long offset ){
	Occurence occur = { fileIdx, line, offset };
	int add = 1;
	int i;
	for(i = 0; i < w->count; i++){
		if(w->occur[i].fileIdx == occur.fileIdx && w->occur[i].line == occur.line) add = 0;
	}
	if(add == 1){
		w->count++;
		w->occur = realloc(w->occur, w->count * sizeof(Occurence));
		w->occur[w->count - 1] = occur;
	}
}

Word * indexFindWord( char *data ){
	Word word = { data, 0, malloc(0) };
	int i, sum = 0;
	for(i = 0; i < strlen(data); i++)
		sum += (int)data[i];
	int idx = abs(sum) % ht.size;
	return hlFind(ht.node[idx], word);
}

void indexAddWord( char *data, int fileIdx, int line, long offset ){
	Word* w = indexFindWord(data);
	if(w != NULL) {
		indexAddOccur(w, fileIdx, line, offset);
	}
	else {
		char* newData = malloc(strlen(data));
		strcpy(newData, data);
		Occurence occur = { fileIdx, line, offset };
		Occurence * occurarr = malloc(sizeof(Occurence));
		occurarr[0] = occur;
		Word newWord = { newData, 1, occurarr };
		int i, sum = 0;
		for(i = 0; i < strlen(data); i++)
			sum += (int)data[i];
		int idx = abs(sum) % ht.size;
		hlInsert(&ht.node[idx], newWord);
	}
}

static void auxClearSpace(Hlnode *node){
	if(node != NULL){
		free(node->word.word);
		free(node->word.occur);
		auxClearSpace(node->next);
		free(node);
	}
}

void indexEnd( void ){
	int i;
	for(i = 0; i < ht.size; i++){
		auxClearSpace(ht.node[i]);
	}
	free(ht.node);
}

static Word* hlFind(Hlnode *node, Word word){
	if(node == NULL) return NULL;
	int i = cmpWordByValue((const void*) &word, (const void*) &(node)->word);
	if(i == 0) return &(node)->word;
	else if(i > 0) return hlFind(node->next, word);
	else return NULL;
}

static void hlInsert(Hlnode **previous, Word word){
	if(*previous == NULL){
		Hlnode *newNode = malloc(sizeof(Hlnode));
		*newNode = (Hlnode) { word, NULL };
		*previous = newNode;
	} else if(cmpWordByValue((const void*) &word, (const void*) &(*previous)->word) < 0){
		Hlnode *aux = *previous;
		Hlnode *newNode = malloc(sizeof(Hlnode));
		*newNode = (Hlnode) { word, aux };
		*previous = newNode;
	} else {
		hlInsert(&(*previous)->next, word);
	}
}

static int cmpWordByValue(const void * elem1, const void * elem2){
	return strcmp(((Word *) elem1)->word, ((Word *) elem2)->word);
}

