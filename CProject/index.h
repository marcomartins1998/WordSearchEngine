/*
 * index.h
 *
 *  Created on: Nov 21, 2019
 *      Author: isel
 */

#ifndef INDEX_H_
#define INDEX_H_

typedef struct{
	int fileIdx;
	int line;
	long offset;
} Occurence;

typedef struct{
	char *word;
	int count;
	Occurence *occur;
} Word;

typedef struct tnode{
	Word word;
	struct tnode *left;
	struct tnode *right;
} Tnode;

typedef struct{
	Tnode *root;
} Index;

typedef struct hlnode{
	Word word;
	struct hlnode *next;
} Hlnode;

typedef struct hashtable{
	int size;
	Hlnode **node;
} Hashtable;

void indexStart( void );
void indexAddOccur( Word *w, int fileIdx, int line, long offset );
Word *indexFindWord( char *data );
void indexAddWord( char *data, int fileIdx, int line, long offset );
void indexEnd( void );

#endif /* INDEX_H_ */
