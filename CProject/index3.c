/*
 * index3.c
 *
 *  Created on: Dec 12, 2019
 *      Author: isel
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

static void tInsert(Tnode **rp, Word word);
static Word* tFind(Tnode **rp, Word word);
static Word* privateIndexFindWord(char *data);
static int cmpWordByValue(const void * elem1, const void * elem2);
static Tnode* treeToSortedList(Tnode *r, Tnode *link);
static Tnode* sortedListToBalancedTree(Tnode **listRoot, int n);

Index idx;
int shouldOrder;
int wordCount = 0;

void indexStart( void ){
	idx = (Index) { NULL };
	shouldOrder = 1;
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

static Word * privateIndexFindWord( char *data ){
	Word word = { data, 0, malloc(0) };
	return tFind(&(idx.root), word);
}

Word * indexFindWord( char *data ){
	if(shouldOrder == 1){
		Tnode * t1 = treeToSortedList(idx.root, NULL);
		idx.root = sortedListToBalancedTree(&t1, wordCount);
		shouldOrder = 0;
	}
	return privateIndexFindWord(data);
}

void indexAddWord( char *data, int fileIdx, int line, long offset ){
	Word* w = privateIndexFindWord(data);
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
		tInsert(&idx.root, newWord);
	}
}

static void auxClearSpace(Tnode *link){
	if(link != NULL){
		free(link->word.occur);
		auxClearSpace(link->left);
		auxClearSpace(link->right);
		free(link);
	}
}

void indexEnd( void ){
	auxClearSpace(idx.root);
}

static void tInsert(Tnode **rp, Word word){
	if(*rp == NULL){
		Tnode * newNode = malloc(sizeof(Tnode));
		*newNode = (Tnode) { word, NULL, NULL };
		*rp = newNode;
	} else if(cmpWordByValue((const void*) &word, (const void*) &(*rp)->word) < 0){
		tInsert(&(*rp)->left, word);
	} else {
		tInsert(&(*rp)->right, word);
	}
}

static Word* tFind(Tnode **rp, Word word){
	if(*rp == NULL) return NULL;
	int i = cmpWordByValue((const void*) &word, (const void*) &(*rp)->word);
	if(i == 0) return &(*rp)->word;
	else if(i > 0) return tFind(&(*rp)->right, word);
	else return tFind(&(*rp)->left, word);
}

static int cmpWordByValue(const void * elem1, const void * elem2){
	return strcmp(((Word *) elem1)->word, ((Word *) elem2)->word);
}

static Tnode *treeToSortedList( Tnode *r, Tnode *link ){
	Tnode * p;
	if( r == NULL ) return link;
	wordCount++;
	p = treeToSortedList( r->left, r );
	r->left = NULL;
	r->right = treeToSortedList( r->right, link );
	return p;
}

static Tnode* sortedListToBalancedTree( Tnode **listRoot, int n ) {
	if( n == 0 )
	return NULL;
	Tnode *leftChild = sortedListToBalancedTree( listRoot, n/2 );
	Tnode *parent = *listRoot;
	parent->left = leftChild;
	*listRoot = (*listRoot)->right;
	parent->right = sortedListToBalancedTree( listRoot, n - ( n / 2 + 1 ) );
	return parent;
}
