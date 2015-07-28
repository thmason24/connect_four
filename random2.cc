#include <stdlib.h>

#include "random.h"

// ------------------------------------------------------------
// another random player for the connect-4 game
// basic idea:
//   - just make a random legal move, with preference to
//     neighboring tiles of the last move
//   - slightly better than the pure random move, but not much

int random2(state_t *state, int last_move)
{
  int result;

  int can_left;
  int can_right;
  int can_middle;

  double r = drand48();

  can_left = ((last_move>0)&&
	      (state->content[0][last_move-1]==EMPTY_TILE));
  can_right = ((last_move<state->num_columns-1)&&
	       (state->content[0][last_move+1]==EMPTY_TILE));
  can_middle = ((last_move>=0)&&
		(last_move<state->num_columns)&&
		(state->content[0][last_move]==EMPTY_TILE));
		
  if ((can_left)&&(can_right)&&(can_middle))
    {
      if (r<0.4)
	result = last_move-1;
      else
	if (r<0.8)
	  result = last_move+1;
	else
	  result = last_move;
    }
  else
    if ((can_left)&&(can_right))
      {
	if (r<0.5)
	  result = last_move-1;
	else
	  result = last_move+1;
      }
    else
      if ((can_left)&&(can_middle))
	{
	  if (r<0.666)
	    result = last_move-1;
	  else
	    result = last_move;
	}
      else
	if ((can_right)&&(can_middle))
	  {
	    if (r<0.666)
	      result = last_move+1;
	    else
	      result = last_move;
	  }
	else
	  if (can_left)
	    result = last_move-1;
	  else
	    if (can_right)
	      result = last_move+1;
	    else
	      if (can_middle)
		result = last_move;
	      else
		{
		  do {
		    result = (int) (drand48()*state->num_columns);
		  } while (state->content[0][result]!=EMPTY_TILE);		  
		};
		
  return result;
}
