/*
 * textread.h
 *
 *  Created on: Nov 15, 2019
 *      Author: isel
 */

#ifndef TEXTREAD_H_
#define TEXTREAD_H_

int textStart( char *fileName );
char *textLine( long *storeOffset );
char *textLocatedLine( long offset );
void textEnd( void );

#endif /* TEXTREAD_H_ */
