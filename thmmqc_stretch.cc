#include <stdlib.h>

#include "thmmqc_slot_type.h"
#include "thmmqc_mode_type.h"
#include "thmmqc_stretch.h"
#include "thmmqc_count_pattern.h"
//#define DEBUG


// ------------------------------------------------------------
// compute the maximum stretch for the opponent and also the
// current player for the simple player (that's why it has
// "simple" in its name)

void thmmqc_stretch(slot board[6][7], slot player,int  *count_2,int  *count_3)
{

slot pattern_2[6][7] = 
{
	{blank , blank  , player , player , blank, blank, blank },
	{blank , player , blank  , player , blank, blank, blank },
	{player, blank  , blank  , player , blank, blank, blank },
	{player, blank  , player , blank  , blank, blank, blank },
	{blank , player , player , blank  , blank, blank, blank },
	{player, player , blank  , blank  , blank, blank, blank },
};


slot pattern_3[4][7] = 
{
	{blank , player , player , player , blank, blank, blank },
	{player, blank  , player , player , blank, blank, blank },
	{player, player , blank  , player , blank, blank, blank },
	{player, player , player , blank  , blank, blank, blank },
};





int pos[2];
int i;

// search for streaks of 2 and three
// think about taking the POS vector and creating a weight with regards to center of the bottom
*count_2=0;
*count_3=0;

for(i=0;i<4;i++){

*count_3 = *count_3 + thmmqc_count_pattern(board, pattern_3[i], 4, pos, row) + 
thmmqc_count_pattern(board, pattern_3[i], 4, pos, col) +
thmmqc_count_pattern(board, pattern_3[i], 4, pos, d_bl) +
thmmqc_count_pattern(board, pattern_3[i], 4, pos, d_tl); 

}

for(i=0;i<6;i++) {
	
*count_2 = *count_2 + thmmqc_count_pattern(board, pattern_2[i], 4, pos, row) + 
thmmqc_count_pattern(board, pattern_2[i], 4, pos, col) +
thmmqc_count_pattern(board, pattern_2[i], 4, pos, d_bl) +
thmmqc_count_pattern(board, pattern_2[i], 4, pos, d_tl); 

}

//*count_2 = thmmqc_count_pattern(board, pattern, 2, pos, d_tl); 

//  *stretch     = -1;
//  *num         = 0;
//  *my_stretch  = -1;

#ifdef DEBUG
  printf("-> position %u, %u; max_stretch %u [%u]; my_stretch %u\n",row,column,*stretch,*num,*my_stretch);
#endif
  
}
