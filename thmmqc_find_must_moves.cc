/* find_must_moves.c  Find spots that either must be played or opp will win or else own can win
returns true if must_move found, false otherwise
*/

#include<stdio.h>
#include <stdlib.h>
//header files
#include "thmmqc_slot_type.h"
#include "thmmqc_mode_type.h"
#include "thmmqc_find_pattern.h"

/* must win patterns
own own own blank
blank own own own
own blank own own
own own blank own
*/

bool thmmqc_find_must_moves(slot board[6][7], slot player, int must_move_pos[2]){
	int i;
	int pattern_number;
	int pos[2]={0};
	
	slot pattern[4][7]=
	{
		{blank, player, player, player, blank, blank, blank},
		{player, blank, player, player, blank, blank, blank},
		{player, player, blank, player, blank, blank, blank},
		{player, player, player, blank, blank, blank, blank},
	};
	//cycle through each pattern for must wins,  any wins must be played ( or blocked if searching opponents) 
	//before returning check to see if its immediately playable (position below must not be blank)
	//make sure you check for wins first!!! hmmmm!!!!

	
		// search rows
	for(i=0;i<4;i++) {
		pattern_number=1;	
		while (thmmqc_find_pattern(board,pattern[i],4,pos,row,pattern_number) ){
			must_move_pos[0]=pos[0];
			must_move_pos[1]=pos[1]+i;
			if (board[must_move_pos[0]-1][must_move_pos[1]] != blank || must_move_pos[0] == 0  ){
				return true;
			}
			else{pattern_number++;}
		}
	}
	// search columns
	for(i=0;i<4;i++) {	
		if (thmmqc_find_pattern(board,pattern[i],4,pos,col,1) ){
			must_move_pos[0]=pos[0]+i;
			must_move_pos[1]=pos[1];
// no need to check playability for column wins
				return true;
		}
	}
	//  search diag bl
	for(i=0;i<4;i++) {	
		pattern_number=1;
		while (thmmqc_find_pattern(board,pattern[i],4,pos,d_bl,pattern_number) ){
			must_move_pos[0]=pos[0]+i;
			must_move_pos[1]=pos[1]+i;
			if (board[must_move_pos[0]-1][must_move_pos[1]] != blank || must_move_pos[0] == 0 ){
				return true;
			}
			else{pattern_number++;}
		}
	}
	//   search diag tl
	for(i=0;i<4;i++) {	
		pattern_number=1;
		while (thmmqc_find_pattern(board,pattern[i],4,pos,d_tl,pattern_number) ){
			must_move_pos[0]=pos[0]-i;
			must_move_pos[1]=pos[1]+i;
			if (board[must_move_pos[0]-1][must_move_pos[1]] != blank || must_move_pos[0] == 0 ){
				return true;
			}
			else{pattern_number++;}
		}
	}	
	//return false if no must_move found
	return false;
		
}
