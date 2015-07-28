#include <stdio.h>

#include "types.h"

void fprintf_state(FILE *f, state_t *state);

void allocate_state(state_t *state, int num_rows, int num_columns);

void free_state(state_t *state);

void reset_to_initial_state(state_t *state);

int terminal_state(state_t *state, int last_row, int last_column);

void copy_state(state_t *target, state_t *source);

void invert_state(state_t *target, state_t *source);

int execute_move(state_t *state, int move, int player);


