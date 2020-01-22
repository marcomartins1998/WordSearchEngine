/*
 * wts.c
 *
 *  Created on: Nov 15, 2019
 *      Author: isel
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "search.h"

int main(int argc, char * argv[]) {
	char * word = malloc(20);
	searchStart(argc, (const char**) argv);
	printf("Leitura completa!\n");
	while(scanf("%s", word) != EOF){
		searchWord(word);
	}
	searchEnd();
	free(word);
	return 0;
}
