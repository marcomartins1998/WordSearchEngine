/*
 * split.c
 *
 *  Created on: Nov 15, 2019
 *      Author: isel
 */

#include <string.h>
#include "split.h"

char *splitStart(char *line){
	return strtok(line, " ");
}

char *splitNext(void){
	return strtok(NULL, " ");
}

void splitEnd(void){
	//TODO o que fazer aqui?
}
