/* count_death_spots.c 
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

int thmmqc_count_death_spots(slot board[6][7], slot player){

	int i;
	int pos[2],DS_pos[2];
	int pattern_number; // deterines whether we are searching for the first pattern...or second...etc
	int count=0;
	int row_count=0;
	int diag_tl_count=0;
	int diag_bl_count=0;	
	slot pattern[4][7]=
	{
		{blank, player, player, player, blank, blank, blank},
		{player, blank, player, player, blank, blank, blank},
		{player, player, blank, player, blank, blank, blank},
		{player, player, player, blank, blank, blank, blank},
	};
	//cycle through each pattern searching for death_spots and count

	
	// search rows
	for(i=0;i<4;i++) {
		pattern_number=1;	
		while (thmmqc_find_pattern(board,pattern[i],4,pos,row,pattern_number) ){
                                DS_pos[0]=pos[0];
                                DS_pos[1]=pos[1]+i;
                                pattern_number++;
                                if (board[DS_pos[0]-1][DS_pos[1]] == blank){
                                count++;
                                row_count++;
                                }
		}
	}
	// search columns (no such thing as colum's death spot)
	//  search diag bl
	for(i=0;i<4;i++) {	
		pattern_number=1;
		while (thmmqc_find_pattern(board,pattern[i],4,pos,d_bl,pattern_number) ){
                                DS_pos[0]=pos[0]+i;
                                DS_pos[1]=pos[1]+i;
                                pattern_number++;
                                if (board[DS_pos[0]-1][DS_pos[1]] == blank){
                                count++;
                                diag_bl_count++;
                                }
		}
	}
	//   search diag tl
	for(i=0;i<4;i++) {	
		pattern_number=1;
		while (thmmqc_find_pattern(board,pattern[i],4,pos,d_tl,pattern_number) ){
				DS_pos[0]=pos[0]-i;
				DS_pos[1]=pos[1]+i;
			        pattern_number++;
				if (board[DS_pos[0]-1][DS_pos[1]] == blank){
				count++;
				diag_tl_count++;
                                
                        	}	
				
				
		}
	}	
	//return total deathspots
//	printf("\n DS row %d col %d bl %d tl %d\n" , row_count, col_count, diag_bl_count, diag_tl_count);

	return count;
		
}
