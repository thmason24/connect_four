#include "types.h"

int offensive(state_t *state, int last_move);

void offensive_maximum_stretch(state_t *state,
			       int column,
			       int *stretch,
			       int *num,
			       int *my_stretch,
			       int *my_stretch_num);
