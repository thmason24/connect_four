/* play_piece.c  advance game one move with inputs of the player making the move, 
the column he wishes to play and the current board state*/

#include<stdio.h>
#include<iostream>

//header files
#include "thmmqc_slot_type.h"


void thmmqc_play_piece(slot board[6][7],slot player,int column)
{

// check if move is legal
if (board[5][column]!=blank) {
}


	
// make play	
	int i;	
    for(i=0;i<7;i++)
    {
	    if(board[i][column]==blank)
	    {
		    board[i][column]=player;
		    break;
	    }
    }
    
    
    
    	
    //int var = **board
    
	
	
//return board;
  
}

