#include "state.h"

int simple(state_t *state, int last_move);

void simple_maximum_stretch(state_t *state,
			    int column,
			    int *stretch,
			    int *num,
			    int *my_stretch);
