/*
 * textread.c
 *
 *  Created on: Nov 15, 2019
 *      Author: isel
 */

#include <stdio.h>
#include <stdlib.h>
#include "textread.h"

FILE * f = NULL;
char a[4000];
int started = 0;

int textStart( char *fileName ){
	f = fopen(fileName, "r");
	if(f == NULL) return 0;
	else {
		started = 1;
		return 1;
	}
}

char *textLine( long *storeOffset ){
	if(storeOffset != NULL) *storeOffset = ftell(f);
	if(fgets(a, 4000, f) != NULL) return a;
	else return NULL;
}

char *textLocatedLine( long offset ){
	fseek(f, offset, SEEK_SET);
	if(fgets(a, 4000, f) != NULL) return a;
	else return NULL;
}

void textEnd( void ){
	if(started == 1){
		fclose(f);
		started = 0;
	}
}
