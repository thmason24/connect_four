/* Connect 4 main program */

#include<stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

//hfiles
#include "thmmqc_circle.h"
#include "thmmqc_slot_type.h"
#include "thmmqc_mode_type.h"
#include "thmmqc_print_board.h"
#include "thmmqc_play_piece.h"
#include "thmmqc_find_winner.h"
#include "thmmqc_find_pattern.h"
#include "thmmqc_read_board.h"
#include "thmmqc_find_must_moves.h"
#include "thmmqc_count_death_spots.h"
#include "thmmqc_stretch.h"


void thmmqc_reload_board_c(slot board[6][7], slot test_board[6][7])
{
int i,j ;
for(i=0;i<6;i++){
	for(j=0;j<7;j++){
      		test_board[i][j]=board[i][j];
	}
}
}


int circle(state_t *state, int last_move)
{

slot board[6][7] = {{blank}};
slot testboard[6][7] = {{blank}};
int  pos[2]      =  {blank};
int i,j;
int net_DS[7],max_net_DS;
bool play[7],auto_lose[7];


// load board state into board

for (i=0;i<6;i++){
	for (j=0;j<7;j++){
		if (state->content[i][j]==PLAYER1_TILE){
			board[5-i][j]=own;
		}
		else if (state->content[i][j]==PLAYER2_TILE){
			board[5-i][j]=opp;
		}
		else{
			board[5-i][j]=blank;
		}
	}
}

//thmmqc_read_board(board);	
//thmmqc_print_board(board);



// look for must_moves for own to win
if(thmmqc_find_must_moves(board,own,pos)){
	return pos[1];
}
// look for must block to prevent player from winning
else if(thmmqc_find_must_moves(board,opp,pos)){
	return pos[1];
}

// now play each position and play one that maximizes death spot difference
else {
	max_net_DS = -10;
	for(i=0;i<7;i++){
		thmmqc_reload_board_c(board, testboard);
		thmmqc_play_piece(testboard,own,i);
// make sure move doesn't cause a win opportunity
		auto_lose[i]=thmmqc_find_must_moves(testboard,opp,pos);
// calculate own DS - opp DS
		net_DS[i] = thmmqc_count_death_spots(testboard,own)-thmmqc_count_death_spots(testboard,opp);
                if(net_DS[i] > max_net_DS) {
			max_net_DS = net_DS[i]; 
		} 
	}
	
//  find all plays with max death spots that do not cause win situations for opponent
	for(i=0;i<7;i++){
		if (net_DS[i]==max_net_DS && !auto_lose[i]) {play[i]=true;}
		else{   play[i]=false;}
	}
/*
for(i=0;i<7;i++){
	printf(" %d ", net_DS[i]);
}
printf("\n");


for(i=0;i<7;i++){
	printf(" %d ", play[i]);
}
printf("\n");

*/

	for (i=0;i<6;i++){
		for (j=0;j<7;j++){
//			printf(" %d %d \n", i , j ); 
			if (board[i][j]==blank && play[j]){
//				printf("Play = %d\n", j);
			        return j;	
			}
		}
	}
}
	
return 0; 
}

