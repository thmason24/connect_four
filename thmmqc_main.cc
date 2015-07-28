/* Connect 4 main program */

#include<stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

//hfiles
#include "thmmqc_main.h"
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


void thmmqc_reload_board(slot board[6][7], slot test_board[6][7])
{
int i,j ;
for(i=0;i<6;i++){
	for(j=0;j<7;j++){
      		test_board[i][j]=board[i][j];
	}
}
}

void thmmqc_print_int_vector(int vector[7])
{
int i;
for(i=0;i<7;i++){printf(" %d",vector[i]);}
printf("\n");
}

void thmmqc_print_vector(bool vector[7])
{
int i;
for(i=0;i<7;i++){printf(" %d",vector[i]);}
printf("\n");
}

int thmmqc(state_t *state, int last_move)
{

slot board[6][7] = {{blank}};
slot testboard[6][7] = {{blank}};
slot testboard_2[6][7] = {{blank}};
int  pos[2]      =  {blank};
int i,j;
int net_DS[7],opp_DS[7];
int own_3stretch, opp_3stretch[7];
int own_2stretch, opp_2stretch[7];
int net_2stretch[7];
int net_3stretch[7];
int max_net_DS, own_DS, max_opp_DS;
int max_opp_3stretch, max_opp_2stretch;
int max_net_3stretch, max_net_2stretch;
bool play[7];
bool auto_lose[7];
int count_2, count_3;

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
//thmmqc_stretch(board,opp, &count_2, &count_3);
//printf("\nopp Stretch2 %d stretch3 %d", count_2, count_3);

//thmmqc_stretch(board,own, &count_2, &count_3);
//printf("\nown Stretch2 %d stretch3 %d \n\n", count_2, count_3);


//initialize play vector to all true (start assuming all plays are viable, then we eliminate bad ones)
std::fill_n(play, 7, true); 
printf("init\n");
thmmqc_print_vector(play);


// look for must_moves for own to win
if(thmmqc_find_must_moves(board,own,pos)){
	return pos[1];
}
// look for must block to prevent player from winning
else if(thmmqc_find_must_moves(board,opp,pos)){
	return pos[1];
}



else {

// first set play to false for full columns
	for(i=0;i<7;i++){
		if(board[5][i] != blank){
			play[i]=false;
		}
	}
printf("init\n");
thmmqc_print_vector(play);

// now play each position and play one that maximizes death spot difference
	max_net_DS = -1000;
	for(i=0;i<7;i++){
		if(play[i]==true){
			thmmqc_reload_board(board, testboard);
			thmmqc_play_piece(testboard,own,i);
			// make sure move doesn't cause a win opportunity
			auto_lose[i]=thmmqc_find_must_moves(testboard,opp,pos);
			// calculate own DS 
			own_DS = thmmqc_count_death_spots(testboard,own);
			//calculate own stretches
			thmmqc_stretch(testboard,own,&count_2,&count_3);
			own_3stretch=count_3;
			own_2stretch=count_2;
		
			//for each position, calculate the best move the opponent can make and report metrics assuming best move is made
			// this is counted as opp stretch

			max_opp_DS = -1000;
			max_opp_2stretch = -1000;
			max_opp_3stretch = -1000;
			for(j=0;j<7;j++){
				if(play[j]==true){
					
					thmmqc_reload_board(testboard,testboard_2);
					thmmqc_play_piece(testboard_2,opp,j);

					opp_DS[j] = thmmqc_count_death_spots(testboard_2,opp);
					if (opp_DS[j] > max_opp_DS){
						max_opp_DS = opp_DS[j];
					}		

					thmmqc_stretch(testboard_2,opp,&count_2,&count_3);
					opp_3stretch[j]=count_3;
					opp_2stretch[j]=count_2;
						
					if (opp_3stretch[j] > max_opp_3stretch){
						max_opp_3stretch = opp_3stretch[j];
					}	
					if (opp_2stretch[j] > max_opp_2stretch){
						max_opp_2stretch = opp_2stretch[j];
					}		


				}
			}
			net_DS[i]=own_DS-max_opp_DS;
			net_2stretch[i]= own_3stretch - max_opp_3stretch;
			net_3stretch[i]= own_2stretch - max_opp_2stretch;
		}	 
        }
	
//  remove all autowins from play vector
	for(i=0;i<7;i++){
		if(play[i]){
			if (!auto_lose[i]) {}
			else{   play[i]=false;}
		}
	}
printf("after autowin\n");
thmmqc_print_vector(play);



//  calculate max DS within allowable range
	for(i=0;i<7;i++){
		if(play[i]){
	               	if(net_DS[i] > max_net_DS) {
				max_net_DS = net_DS[i]; 
			}
		}
	}
	


//  find all plays with max death spots that do not cause win situations for opponent
	for(i=0;i<7;i++){
		if(play[i]){
			if (net_DS[i]==max_net_DS) {}
			else{   play[i]=false;}
		}
	}
printf("after DS\n");
thmmqc_print_int_vector(net_DS);
thmmqc_print_vector(play);


//   for plays that DS logic has not eliminated, calculate 2 and 3 stretches 
	max_net_3stretch=-1000;
	for(i=0;i<7;i++){
		if (play[i]==true){
			if(net_3stretch[i] > max_net_3stretch) {
				max_net_3stretch = net_3stretch[i]; 
			}
		}
	}

//   for plays that DS logic has not eliminated,  choose the one's with the best connect 3 values then do the same for 2 values
	
	for(i=0;i<7;i++){
		if (play[i]==true){
			if (net_3stretch[i]==max_net_3stretch) {}
			else{   play[i]=false;}
		}
	}
printf("after 3stretch\n");
thmmqc_print_int_vector(net_3stretch);
thmmqc_print_vector(play);

	//must first calculate 2streakmax here
	max_net_2stretch=-1000;
	for(i=0;i<7;i++){
		if (play[i]==true){
			if(net_2stretch[i] > max_net_2stretch) {
				max_net_2stretch = net_2stretch[i]; 
			}
		}
	}

	for(i=0;i<7;i++){
		if (play[i]==true){
			if (net_2stretch[i]==max_net_2stretch) {}
			else{   play[i]=false;}
		}
	}

printf("after 2stretch\n");
thmmqc_print_vector(play);
	

//for(i=0;i<7;i++){
//	printf(" %d ", net_DS[i]);
//}

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

