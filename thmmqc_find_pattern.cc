/* find_pattern.c  find a generic pattern on the board input*/
#include <stdlib.h>
#include<stdio.h>

//header files
#include "thmmqc_slot_type.h"
#include "thmmqc_mode_type.h"

bool thmmqc_find_pattern(slot board[6][7], slot pattern[7],int length, int pos[2],mode mode,int pattern_number){

	int i , j , k;
	int patterns_found=0;
	bool match;
	//  do the search "pattern_number" times and return the "pattern_numberth" position
	
	if(mode==row){
	// search rows
		for(i=0;i<6;i++){
			for(j=0;j<(8-length);j++){
				match=true;
				for(k=0;k<length;k++){
					if(board[i][j+k]!=pattern[k]){
						match=false;
					}
				}
				if(match){
					pos[0]=i;
					pos[1]=j;
					patterns_found++;
					if((patterns_found==pattern_number)){
						return true;
					}
				}        
			}
		}
	}
	else if(mode==col){
		//search columns
			for(i=0;i<(7-length);i++){
				for(j=0;j<7;j++){			
					match=true;
					for(k=0;k<length;k++){
						if(board[i+k][j]!=pattern[k]){
							match=false;
						}
					}
					if(match){
						pos[0]=i;
						pos[1]=j;
						patterns_found++;
						if((patterns_found==pattern_number)){
							return true;
						}
					}
				}
			}
		}
	else if(mode==d_bl){
			for(i=0;i<(7-length);i++){
				for(j=0;j<(8-length);j++){			
					match=true;
					for(k=0;k<length;k++){
						if(board[i+k][j+k]!=pattern[k]){
							match=false;
						}
					}
					if(match){
						pos[0]=i;
						pos[1]=j;
						patterns_found++;
						if((patterns_found==pattern_number)){
							return true;
						}
					}
				}
			}
		}
	else if(mode==d_tl){
			for(i=length-1;i<6;i++){
				for(j=0;j<(8-length);j++){			
					match=true;
					for(k=0;k<length;k++){
						if(board[i-k][j+k]!=pattern[k]){
							match=false;
						}
					}
					if(match){
						pos[0]=i;
						pos[1]=j;
						patterns_found++;
						if((patterns_found==pattern_number)){
							return true;
						}
					}
				}
			}
		}
return false;
}
