#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filtres.h"


void printstr(int num)
{
	int aux, i;
	char *nstr;

        aux = 1;
	nstr = (char *)malloc( 10 );
        for( i = 1; i < num; i*=10 ) aux++;
        nstr = (char *)malloc( aux + 2 );
        sprintf(nstr, "%d ", num);
        write( 1, nstr, strlen( nstr ) );
}

void fs_head( int fd )
{
	int count = 0;
	char c;

	while( read( fd, &c, 1 ) && (count < 3) ){
		write( 1, &c, 1 );
		if ( c == '\n' ) count++;
	}
}

void fs_wc( int fd )
{
	int nl = 0, np = 0, nc = 0, sep = 0;
	char c;
	
	while( read( fd, &c, 1 ) ){
		nc++;
		switch( c ){
			case '\n': nl++;
			case '\t':
			case ' ': if( !sep ) np++; 
				  break;
			default: sep = 0;
		}
	 }
	printstr( nc );
	printstr( np );
	printstr( nl );
	c = 10;
	write( 1, &c, 1 );
}

void fs_nl( int fd )
{
	int nl = 1, new = 1, aux, i;
	char c, *nlstr;

	while( read( fd, &c, 1) ){
		if( new ){
			printstr( nl );
			nl++;
			new = 0;
		}
		if ( c == '\n' ) new = 1;
		write( 1, &c, 1 );		
	}
}

void fs_cut( int fd, int col )
{
	char c;
	int pal = 1, nc = 0;

	while( read( fd, &c, 1 ) ){
		if ( c == '\n' ){
			if(pal >= col) write( 1, &c, 1 );
			pal = 1;
			nc = 0;
		} 
		else if ( pal == col ){ nc++; write( 1, &c, 1 );}
		if (( c == '\t' ) || ( c == ' ' )) pal++;
	}
}

