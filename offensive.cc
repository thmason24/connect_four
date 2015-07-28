#include <stdlib.h>
#include <stdio.h>

#include "offensive.h"

// ------------------------------------------------------------
// offensive player for the connect-4 game, similar
// to the "simple" player just lot less defensive
// basic idea:
//   - if opponent can win in 1 move and we can prevent it, 
//     do it
//   - otherwise, maximize the number of alined tiles for us,
//     preferring those that capture multiple directions

//#define DEBUG

int offensive(state_t *state, int last_move)
{
  int max_stretch = -1;
  int max_stretch_idx = -1;
  int max_stretch_num = -1;
  int max_stretch_my_stretch = -1;
  int max_my_stretch = -1;
  int max_my_stretch_idx = -1;
  int max_my_stretch_num = -1;

#ifdef DEBUG
  printf("\n\n\nOFFENSIVE PLAYER:\n");
  fprintf_state(stdout,state);
#endif

  for (int i=0; i<state->num_columns; i++)
    {
      int this_stretch;
      int this_num;
      int my_stretch;
      int my_stretch_num;
      
	// find the maximum number of aligned tiles (I call it stretch) if
	// the opponent were to move into column i (denotes by this_stretch); 
	// also returns the number of occurences of the max stretch for this
	// move (this_num);
	// also returns the max size of our stretch if we were to make this 
	// move (and the corresponding number for different directions)

      offensive_maximum_stretch(state, i, &this_stretch, &this_num, &my_stretch, &my_stretch_num);

#ifdef DEBUG      
      printf("-> i=%u, this_stretch=%u [%u], my_stretch=%u\n",i,this_stretch,this_num,my_stretch);
#endif

      // update info on the "best" defensive move

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

      // update info on the "best" offensive move

      if ((my_stretch>max_my_stretch)||
	  ((my_stretch==max_my_stretch)&&
	   (my_stretch_num>max_my_stretch_num)))
	{
	  max_my_stretch=my_stretch;
	  max_my_stretch_idx=i;
	  max_my_stretch_num=my_stretch_num;
	}
    }

  // if we can win, let's do it

  if (max_my_stretch>=4)
    return max_my_stretch_idx;

  // if opponent can win in 1 move and we can prevent it,
  // do it

  if (max_stretch>=4)
    return max_stretch_idx;

  // otherwise, go for offense (increase our stretch size)

  return max_my_stretch_idx;
}

// ------------------------------------------------------------
// compute the maximum stretch for the opponent and also the
// current player for the offensive player (that's why it has
// "offensive" in its name); similar to the function in
// the simple player (just small changes)

void offensive_maximum_stretch(state_t *state,
			       int column,
			       int *stretch,
			       int *num,
			       int *my_stretch,
			       int *my_stretch_num)
{
  int row;

  *stretch        = -1;
  *num            = 0;
  *my_stretch     = -1;
  *my_stretch_num = 0;

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
	    {
	      (*my_stretch)=k+l-1;
	      (*my_stretch_num)=1;
	    }
	  else
	    if (k+l-1==*my_stretch)
	      (*my_stretch_num)++;
	}
  
#ifdef DEBUG
  printf("-> position %u, %u; max_stretch %u [%u]; my_stretch %u\n",row,column,*stretch,*num,*my_stretch);
#endif
  
}
