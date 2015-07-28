/* read_board.c  read board from text file*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//header files
#include "thmmqc_slot_type.h"

void thmmqc_read_board(slot board[6][7]){
    int i , j ;
	char str[80];
	FILE * bfile;
	
    bfile = fopen("board.txt","r");
//read in board from board.txt	
    for(i=5;i>=0;i--){
	    for(j=0;j<7;j++){
	    fscanf(bfile,"%s ", str );
	    	if (strcmp("x",str)==0){
		    	board[i][j]=own;
	    	}
	    	else if (strcmp("o",str)==0) {
		   	board[i][j]=opp;
	    	}
		else{
			board[i][j]=blank;
		}
    	}
	}
	fclose(bfile);
	
    
}
