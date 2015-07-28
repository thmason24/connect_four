#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "state.h"

//#define DEBUG

// ------------------------------------------------------------
// prints out state into a file stream 
// (use stdout as f for screen)

void fprintf_state(FILE *f, state_t *state)
{
  for (int j=0; j<state->num_columns; j++)
    fprintf(f," %u ",j);
  fprintf(f,"\n");

  for (int i=0; i<state->num_rows; i++)
    {
      for (int j=0; j<state->num_columns; j++)
	{
	  switch (state->content[i][j]) 
	    {
	    case EMPTY_TILE:
	      fprintf(f," - ");
	      break;
	    case PLAYER1_TILE:
	      fprintf(f," O ");
	      break;
	    case PLAYER2_TILE:
	      fprintf(f," X ");
	      break;
	    default:
	      printf("ERROR: Unknown tile!\n");
	      exit(-1);
	    }
	}
      fprintf(f,"\n");
    }

  for (int j=0; j<state->num_columns; j++)
    fprintf(f,"---");
  fprintf(f,"\n");
}

// ------------------------------------------------------------
// allocates a game state and sets it to the initial game 
// state

void allocate_state(state_t *state, 
		    int num_rows, 
		    int num_columns)
{
  state->num_rows = num_rows;
  state->num_columns = num_columns;
  state->content = new int* [num_rows];

  for (int i=0; i<num_rows; i++)
    {
      state->content[i] = new int[state->num_columns];
      
      for (int j=0; j<state->num_columns; j++)
	state->content[i][j] = EMPTY_TILE;
    }

  state->num_tiles = 0;
}

// ------------------------------------------------------------
// frees up memory used by a game state

void free_state(state_t *state)
{
  if (state->content!=NULL)
    {
      for (int i=0; i<state->num_rows; i++)
	delete[] state->content[i];
    
      delete[] state->content;

      state->content = NULL;
    }
}

// ------------------------------------------------------------
// resets a game state to the initial state (empty board);
// the state must have been allocated already

void reset_to_initial_state(state_t *state)
{
  for (int i=0; i<state->num_rows; i++)
    for (int j=0; j<state->num_columns; j++)
      state->content[i][j] = EMPTY_TILE;

  state->num_tiles = 0;
}

// ------------------------------------------------------------
// check for terminal state (given last move's column);
// 2 possible outcomes
//    0 - no 4 in line have been created with the last move
//    1 - 4 in line have been created, so it's a win (of the 
//        last player to move)

int terminal_state(state_t *state, int last_row, int last_column)
{
  int max_stretch = 1;
  int last_player = state->content[last_row][last_column];

  for (int dx=-1; dx<=1; dx++)
    for (int dy=-1; dy<=1; dy++)
      if ((dx!=0)||(dy!=0))
	{
	  int k;
	  int l;

	  for (k=1;	       
 	       (last_row+dy*k>=0)&&
		 (last_row+dy*k<state->num_rows)&&
		 (last_column+dx*k>=0)&&
		 (last_column+dx*k<state->num_columns)&&
		 (state->content[last_row+dy*k][last_column+dx*k]==last_player);
	       k++);

	  for (l=1;	       
 	       (last_row-dy*l>=0)&&
		 (last_row-dy*l<state->num_rows)&&
		 (last_column-dx*l>=0)&&
		 (last_column-dx*l<state->num_columns)&&
		 (state->content[last_row-dy*l][last_column-dx*l]==last_player);
	       l++);
	  
	  if (k+l-1>max_stretch)
	    max_stretch=k+l-1;

#ifdef DEBUG
	  printf("dx=%u dy=%u k=%u l=%u\n",dx,dy,k,l);
#endif
	}

#ifdef DEBUG
  printf("max_stretch (%u,%u)=%u\n",last_row,last_column,max_stretch);
#endif  

  if (max_stretch>=4)
    return 1;
  else
    return 0;
}

// ------------------------------------------------------------
// copies "source" state into "target" state;
// both states must have been allocated and of the same size

void copy_state(state_t *target, state_t *source)
{
  if ((target->num_columns!=source->num_columns)||
      (target->num_rows!=source->num_rows))
    {
      printf("ERROR: States in copy_state do not match in size!\n");
      exit(-1);
    }

  for (int i=0; i<source->num_rows; i++)
    memcpy(target->content[i], 
	   source->content[i], 
	   sizeof(source->content[i][0])*source->num_columns);
  
  target->num_tiles = source->num_tiles;
}

// ------------------------------------------------------------
// invert the two players in the "source" state, and put the 
// result into the "target" state;
// both states must have been allocated and of the same size

void invert_state(state_t *target, state_t *source)
{
  if ((target->num_columns!=source->num_columns)||
      (target->num_rows!=source->num_rows))
    {
      printf("ERROR: States in invert_state do not match in size!\n");
      exit(-1);
    }

  for (int i=0; i<source->num_rows; i++)
    for (int j=0; j<source->num_columns; j++)
      if (source->content[i][j]==EMPTY_TILE)
	target->content[i][j]=EMPTY_TILE;
      else
	if (source->content[i][j]==PLAYER1_TILE)
	  target->content[i][j]=PLAYER2_TILE;
	else
	  target->content[i][j]=PLAYER1_TILE;

  target->num_tiles = source->num_tiles;
}

// ------------------------------------------------------------
// executed a given move of a given player on a given state;
// 5 possible outcomes:
//    PLAYER1_ILLEGAL_MOVE: player 1 made illegal move 
//                          (player 2 wins as a result)
//    PLAYER2_ILLEGAL_MOVE: player 2 made illegal move 
//                          (player 1 wins as a result)
//    PLAYER1_WIN:          player 1 wins due to 4-in-line
//    PLAYER2_WIN:          player 2 wins due to 4-in-line
//    TIE:                  board is full, noone wins, 
//                          the game ends with a tie (draw)

int execute_move(state_t *state, int move, int player)
{
  int i;

  if ((move<0)||(move>=state->num_columns))
    return ((player==PLAYER1_TILE)? PLAYER1_ILLEGAL_MOVE:PLAYER2_ILLEGAL_MOVE);
  
  if (state->content[0][move]!=EMPTY_TILE)
    return ((player==PLAYER1_TILE)? PLAYER1_ILLEGAL_MOVE:PLAYER2_ILLEGAL_MOVE);

  state->num_tiles++;
  
  for (i=0; (i<state->num_rows)&&(state->content[i][move]==EMPTY_TILE); i++);
 
  state->content[i-1][move]=player;
  
  if (terminal_state(state,i-1,move))
    {
      if (player==PLAYER1_TILE)
	return PLAYER1_WIN;
      else
	return PLAYER2_WIN;
    }

  if (state->num_tiles==state->num_rows*state->num_columns)
    return TIE;

  return 0;
}
