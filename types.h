#ifndef _TYPES_H_
#define _TYPES_H_

// ------------------------------------------------------------
// possible tiles in game state (content field)

#define EMPTY_TILE   0
#define PLAYER1_TILE 1
#define PLAYER2_TILE 2

// ------------------------------------------------------------
// results of one game simulation

#define PLAYER1_ILLEGAL_MOVE 10
#define PLAYER2_ILLEGAL_MOVE 11
#define PLAYER1_WIN          12
#define PLAYER2_WIN          13
#define PLAYER1_TIME_OUT     14
#define PLAYER2_TIME_OUT     15
#define TIE                  16

// ------------------------------------------------------------
// type for game state (passed to the players as one input)

typedef struct {

  int num_columns;   // number of columns (default is 7)
  int num_rows;      // number of rows (default is 6)

  int **content;     // content of the board
                     // content[row][column]
                     //   row=0..num_rows-1 (0=top)
                     //   column=0..num_columns
                     // each content[row][column] is one of
                     //   PLAYER1_TILE (active player)
                     //   PLAYER2_TILE (other player)
                     //   EMPTY_TILE (empty tile)

  int num_tiles;     // total number of tiles 
                     // (helps determine ties)

} state_t;

// -------------------------------------------------------------
// function for getting next player move type
//    input:  state     = current state (PLAYER1_TILE is
//                        always the active player)
//            last_move = last move of the opponent
//                        (PLAYER2_TILE), is -1 is this is 1st 
//                        move of the game
//    output: move (column number from 0 to num_columns-1)
//
// Notes:
// - If the return value is a full column, the move is illegal
// - The decision making may be limited by time (see rules)
// - Feel free to modify the state (it's going to be a copy)

typedef int (*player_t) (state_t *state, int last_move);

// -------------------------------------------------------------
// statistics for game simulation (on output)

typedef struct {
  
  double overall_time;

  int num_turns;

  int num_games;

} stats_t;

#endif
