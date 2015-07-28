/* play_piece.c  advance game one move with inputs of the player making the move, 
the column he wishes to play and the current board state*/

#include<stdio.h>
#include <stdlib.h>
//header files
#include "thmmqc_slot_type.h"
#include "thmmqc_mode_type.h"
#include "thmmqc_print_board.h"
#include "thmmqc_find_pattern.h"

void thmmqc_find_winner(slot board[6][7]){

	int i , j;
	int pos[2]={0};
	bool full_board = true;
	slot winner=blank;
	slot own_win_pattern[7]={own, own, own, own, blank, blank, blank};
	slot opp_win_pattern[7]={opp, opp, opp, opp, blank, blank, blank};
	
	if (thmmqc_find_pattern(board,own_win_pattern,4,pos,row,1) || \
	    thmmqc_find_pattern(board,own_win_pattern,4,pos,col,1) || \
	    thmmqc_find_pattern(board,own_win_pattern,4,pos,d_bl,1) || \
	    thmmqc_find_pattern(board,own_win_pattern,4,pos,d_tl,1) )
	{winner=own;}

	if (thmmqc_find_pattern(board,opp_win_pattern,4,pos,row,1) || \
	    thmmqc_find_pattern(board,opp_win_pattern,4,pos,col,1) || \
	    thmmqc_find_pattern(board,opp_win_pattern,4,pos,d_bl,1) || \
	    thmmqc_find_pattern(board,opp_win_pattern,4,pos,d_tl,1) )
	{winner=opp;}

    // search for full board
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			if(board[i][j]==blank){
				full_board=false;
			}
		}
	}
		
	if(winner==own){
		thmmqc_print_board(board);
		printf("\n Game over!!!! You lost! \n");
		exit(0);
	}
	else 
	if(winner==opp){
		thmmqc_print_board(board);
		printf("\n Game over!!!! You won!  \n");
		exit(0);
	}
	else 
	if(full_board){
		thmmqc_print_board(board);
		printf("\n Game over!!!! Board is full!  TIE GAME!  \n");
		exit(0);
	}
	
}
