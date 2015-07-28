#include <stdlib.h>

#include "random.h"

// ------------------------------------------------------------
// fully random player for the connect-4 game
// basic idea:
//   - just make a random legal move, no thinking involved

int random(state_t *state, int last_move)
{
  int result;

  do {
    result = (int) (drand48()*state->num_columns);
  } while (state->content[0][result]!=EMPTY_TILE);

  return result;
}
