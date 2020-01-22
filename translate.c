/*
 * translate.c
 *
 *  Created on: Nov 15, 2019
 *      Author: isel
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "translate.h"

static int count_higher_ones(unsigned char value){
	unsigned char div = (unsigned char) pow(2, CHAR_BIT-1);
	int num = 0;
	while(value != 0){
		if(value/div >= 1 && (value = value%div) >= 0){ num++; div /= 2;}
		else break;
	}
	return num;
}

static char lookup_c3_range[] = {
		'a',
		'a',
		'a',
		'a',
		'a',
		'a',
		' ',
		'c',
		'e',
		'e',
		'e',
		'e',
		'i',
		'i',
		'i',
		'i',
		'd',
		'n',
		'o',
		'o',
		'o',
		'o',
		'o',
		' ',
		'o',
		'u',
		'u',
		'u',
		'u',
		'y',
		' ',
		' ',
		'a',
		'a',
		'a',
		'a',
		'a',
		'a',
		' ',
		'c',
		'e',
		'e',
		'e',
		'e',
		'i',
		'i',
		'i',
		'i',
		' ',
		'n',
		'o',
		'o',
		'o',
		'o',
		'o',
		' ',
		'o',
		'u',
		'u',
		'u',
		'u',
		'y',
		' ',
		'y'
};

static int translate(char sym[], char *res){
	unsigned char c = (unsigned char) sym[0];
	if(c == 0xc3) *res = lookup_c3_range[(unsigned char) sym[1] - 0x80];
	else if(c >= 0x41 && c <= 0x5a) *res = c + 0x20;
	else if((c >= 0x30 && c <= 0x39) || (c >= 0x61 && c <= 0x7a)) *res = c;
	else *res = ' ';
	return (count_higher_ones(sym[0]) >= 2) ? count_higher_ones(sym[0]) : 1;
}

void translate_string(char src[], char dst[]){
	int i = 0, j = 0;
	while(src[i] != 0){
		char * ptr = malloc(sizeof(*src));
		i += translate(&src[i], ptr);
		dst[j] = *ptr;
		j++;
	}
	dst[j] = 0x00;
}


