/* play_piece.c  advance game one move with inputs of the player making the move, 
the column he wishes to play and the current board state*/

#include<stdio.h>
#include<iostream>

//header files
#include "slot_type.h"


void find_streak(slot board[6][7],slot player, int column){

	int i , j , k;
	bool match = true;
	slot streak[4];
	slot winner=blank;
	printf("\ndevelop code to find a streak\n");
	
	//search rows one by one
	
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			streak[0]=board[i][j];
			//streak[1]=streak[0];
			//streak[2]=streak[1];
			//streak[3]=streak[2];
			
			//check if own is winner
			match=true;
			for(k=0;k<4;k++){
				if(streak[k]!=own]{
				match=false;
				}
			}
			if(match=true){
				winner=own;
			}
			
			//check if opp is winner
			match=true;
			for(k=0;k<4;k++){
				if(streak[k]!=opp]{
				match=false;
				}
			}
			if(match=true){
				winner=opp;
			}		
		}
	}
	
	if(winner==owm){
		printf("\n Game over!!!!  winner is OWN")
	}
	else(winner==opp){
		printf("\n Game over!!!!  winner is OPP")
	}
	 
	
	}

	
		
	
	
	
}