#include <stdlib.h>

#include "simple.h"

//#define DEBUG

// ------------------------------------------------------------
// simple player for the connect-4 game
// basic idea:
//   - find the best move for the opponent that will maximize
//     the number of aligned tiles (preference goes to those
//     that combine multiple directions and those that increase
//     current players number of aligned tiles)
//   - if can win right away, do it

int simple(state_t *state, int last_move)
{
  int max_stretch = -1;
  int max_stretch_idx = -1;
  int max_stretch_num = -1;
  int max_stretch_my_stretch = -1;
  int max_my_stretch = -1;
  int max_my_stretch_idx = -1;

#ifdef DEBUG
  printf("\n\n\nSIMPLE PLAYER:\n");
  fprintf_state(stdout,state);
#endif

  for (int i=0; i<state->num_columns; i++)
    if (state->content[0][i]==EMPTY_TILE)
      {
	int this_stretch;
	int this_num;
	int my_stretch;

	// find the maximum number of aligned tiles (I call it stretch) if
	// the opponent were to move into column i (denotes by this_stretch); 
	// also returns the number of occurences of the max stretch for this
	// move (this_num);
	// also returns the max size of our stretch if we were to make this 
	// move
	
	simple_maximum_stretch(state, i, &this_stretch, &this_num, &my_stretch);
	
#ifdef DEBUG
	printf("-> i=%u, this_stretch=%u [%u], my_stretch=%u\n",i,this_stretch,this_num,my_stretch);
#endif
	
	// update the defensive move preference
	// (prevent increasing opponent's stretch, especially
	//  from multiple directions and especially if we benefit 
        //  from it)

	if ((this_stretch>max_stretch)||
	    ((this_stretch==max_stretch)&&
	     (this_num>max_stretch_num)&&
	     (my_stretch>=max_stretch_my_stretch))||
	    ((this_stretch==max_stretch)&&
	     (my_stretch>max_stretch_my_stretch)))
	  {
	    max_stretch=this_stretch;
	    max_stretch_idx=i;
	    max_stretch_num=this_num;
	    max_stretch_my_stretch=my_stretch;
	  }

	// update the offensive move preference
	// (prefer to increase our stretch the most)
	
	if (my_stretch>max_my_stretch)
	  {
	    max_my_stretch=my_stretch;
	    max_my_stretch_idx=i;
	  }
      }

  // the final decision is either a win or a defensive move
  
  if (max_my_stretch>=4)
    return max_my_stretch_idx;
  else
    return max_stretch_idx;  
}

// ------------------------------------------------------------
// compute the maximum stretch for the opponent and also the
// current player for the simple player (that's why it has
// "simple" in its name)

void simple_maximum_stretch(state_t *state,
			    int column,
			    int *stretch,
			    int *num,
			    int *my_stretch)
{
  int row;

  *stretch     = -1;
  *num         = 0;
  *my_stretch  = -1;

  for (row=0; 
       (row<state->num_rows)&&(state->content[row][column]==EMPTY_TILE); 
       row++);
  row--;

  for (int dx=-1; dx<=1; dx++)
    for (int dy=0; dy<=1; dy++)
      if (((dx!=0)||(dy!=0))&&
	  ((dx!=-1)||(dy!=0)))
	{
	  int k;
	  int l;
	  
	  for (k=1;	       
 	       (row+dy*k>=0)&&
		 (row+dy*k<state->num_rows)&&
		 (column+dx*k>=0)&&
		 (column+dx*k<state->num_columns)&&
		 (state->content[row+dy*k][column+dx*k]==PLAYER2_TILE);
	       k++);

	  for (l=1;	       
 	       (row-dy*l>=0)&&
		 (row-dy*l<state->num_rows)&&
		 (column-dx*l>=0)&&
		 (column-dx*l<state->num_columns)&&
		 (state->content[row-dy*l][column-dx*l]==PLAYER2_TILE);
	       l++);
	  
	  if (k+l-1>*stretch)
	    {
	      *stretch=k+l-1;
	      *num=1;
	    }
	  else
	    if (k+l-1==*stretch)
	      (*num)++;

	  for (k=1;	       
 	       (row+dy*k>=0)&&
		 (row+dy*k<state->num_rows)&&
		 (column+dx*k>=0)&&
		 (column+dx*k<state->num_columns)&&
		 (state->content[row+dy*k][column+dx*k]==PLAYER1_TILE);
	       k++);

	  for (l=1;	       
 	       (row-dy*l>=0)&&
		 (row-dy*l<state->num_rows)&&
		 (column-dx*l>=0)&&
		 (column-dx*l<state->num_columns)&&
		 (state->content[row-dy*l][column-dx*l]==PLAYER1_TILE);
	       l++);
	  
	  if (k+l-1>*my_stretch)
	    *my_stretch=k+l-1;
	}
  
#ifdef DEBUG
  printf("-> position %u, %u; max_stretch %u [%u]; my_stretch %u\n",row,column,*stretch,*num,*my_stretch);
#endif
  
}
