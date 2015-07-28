#include <stdlib.h>
#include <stdio.h>

#include "types.h"

// basic idea:
// asks the user to provide a move

int human(state_t *state, int last_move)
{
  char s[100];
  int result;
  
  do {

    printf("type the columm number for your move:\n");

    fgets(s,100,stdin);

    result = atoi(s);

  } while ((result<0)||(result>=state->num_columns));
  
  return result;
}
