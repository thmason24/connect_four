#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "state.h"
#include "get_player.h"
#include "simulate.h"
#include "human.h"

// ------------------------------------------------------------
// simulates one game for given players
//   player1:       first player's function
//   player2:       second player's function
//   player1_stats: stat structure for player1
//   player2_stats: stat structure for player2
//   max_time:      maximum time per turn for nonhuman players 
//                  (in seconds)
//   quiet:         quiet mode flag (set to 1 for tournaments)
//
// returns the final game status out of
//   PLAYER1_ILLEGAL_MOVE 10
//   PLAYER2_ILLEGAL_MOVE 11
//   PLAYER1_WIN          12
//   PLAYER2_WIN          13
//   PLAYER1_TIME_OUT     14
//   PLAYER2_TIME_OUT     15
//   TIE                  16
// 
// also sets the stat structures

int simulate_game(player_t player1, 
		  player_t player2, 
		  stats_t *player1_stats,
		  stats_t *player2_stats,
		  double max_time,
		  int quiet)
{
  int num_rows    = 6;
  int num_columns = 7;

  state_t state;
  state_t aux_state;

  int termination_state_reached = 0;

  int last_move = -1;

  allocate_state(&state,
		 num_rows,
		 num_columns);
  
  allocate_state(&aux_state,
		 num_rows,
		 num_columns);
  
  reset_to_initial_state(&state);

  do {
    
    if (!quiet)
      {
	fprintf_state(stdout, &state);
	printf("-> player O's turn\n");
      }

    // move of the first player

    copy_state(&aux_state,&state);

    termination_state_reached = simulate_one_turn(&aux_state,
						  &state,
						  player1,
						  player1_stats,
						  &last_move,
						  PLAYER1_TILE,
						  max_time);
    
    // if not terminated, move of the second player

    if (termination_state_reached==0)
      {
	if (!quiet)
	  {
	    fprintf_state(stdout, &state);
	    printf("-> player X's turn...\n");
	  }	

	invert_state(&aux_state,&state);

	termination_state_reached = simulate_one_turn(&aux_state,
						      &state,
						      player2,
						      player2_stats,
						      &last_move,
						      PLAYER2_TILE,
						      max_time);
      }
    
  } while (!termination_state_reached);

  player1_stats->num_games++;
  player2_stats->num_games++;

  if (!quiet)
    fprintf_state(stdout, &state);

  if (!quiet)
    {
      if (termination_state_reached==PLAYER1_WIN)
	printf("Player 1 won!\n");
      else
	{
	  if (termination_state_reached==PLAYER2_WIN)
	    printf("Player 2 won!\n");
	  else
	    {
	      if (termination_state_reached==PLAYER1_ILLEGAL_MOVE)
		printf("Player 1 disqualified due to illegal move!\n");
	      else
		if (termination_state_reached==PLAYER2_ILLEGAL_MOVE)
		  printf("Player 2 disqualified due to illegal move!\n");
	    }
	}
    }

  free_state(&state);
  free_state(&aux_state);

  return termination_state_reached;
}

// ------------------------------------------------------------
// simulates a tournament for players with given names

void simulate_tournament(char **names, 
			 int num, 
			 double max_time)
{
  int num_matches=100;
  player_info_t *player_list = new player_info_t [num];
  
  int *points = new int[num];

  int *wins = new int[num];
  int *losses = new int[num];
  int *ties = new int[num];

  stats_t *player_stats = new stats_t[num];

  for (int i=0; i<num; i++)
    {
      if (get_player_info(names[i], &player_list[i])==0)
	{
	  printf("ERROR: Cannot find player %s!\n",names[i]);
	  exit(-1);
	}

      points[i] = 0;
      wins[i] = 0;
      ties[i] = 0;
      losses[i] = 0;

      player_stats[i].overall_time=0;
      player_stats[i].num_turns=0;
      player_stats[i].num_games=0;
    }
  
  for (int i=0; i<num; i++)
    for (int j=0; j<num; j++)
      if (i!=j)
	for (int k=0; k<num_matches; k++)
	  {
	    int result = simulate_game(player_list[i].player_function,
				       player_list[j].player_function,
				       &player_stats[i],
				       &player_stats[j],
				       max_time,
				       0);

	    if ((result==PLAYER1_WIN)||
		(result==PLAYER2_ILLEGAL_MOVE)||
		(result==PLAYER2_TIME_OUT))
	      {
		points[i]+=2;
		wins[i]++;
		losses[j]++;
	      }
	    else
	      if ((result==PLAYER2_WIN)||
		  (result==PLAYER1_ILLEGAL_MOVE)||
		  (result==PLAYER1_TIME_OUT))
		{
		  points[j]+=2;
		  wins[j]++;
		  losses[i]++;
		}
	      else
		if (result==TIE)
		  {
		    points[i]+=1;
		    points[j]+=1;
		    ties[i]++;
		    ties[j]++;
		  }
		else
		  {
		    printf("ERROR: What just happened?\n");
		    exit(-1);
		  }
	  }

  print_tournament_results(player_list,
			   points,
			   wins,
			   losses,
			   ties,
			   player_stats,
			   num);

  delete[] player_list;
  delete[] points;
  delete[] wins;
  delete[] losses;
  delete[] ties;
  delete[] player_stats;
}

// ------------------------------------------------------------
// simulates one turn of a given player

int simulate_one_turn(state_t *aux_state, 
		      state_t *orig_state,
		      player_t player,
		      stats_t *player_stats,
		      int *last_move,
		      int player_id,
		      double max_time)
{
  clock_t start_time, end_time;
  double my_time;
  int move;
  int termination_state_reached;

  start_time = clock();
  
  move = (*player)(aux_state, *last_move);
  
  end_time = clock();
  
  player_stats->num_turns++;
  
  my_time  = (double) ((end_time-start_time)/((long double)CLOCKS_PER_SEC));
  
  player_stats->overall_time += my_time;
  
  if ((my_time>max_time)&&(player!=human))
    termination_state_reached = 
      (player_id==PLAYER1_TILE)? PLAYER1_TIME_OUT:PLAYER2_TIME_OUT;
  else
    termination_state_reached = 
      execute_move(orig_state, move, player_id);

  *last_move = move;

  return termination_state_reached;
}

// ------------------------------------------------------------
// prints out tournament results

void print_tournament_results(player_info_t *player_list,
			      int *points,
			      int *wins,
			      int *losses,
			      int *ties,
			      stats_t *player_stats,
			      int num)
{
  printf("TOURNAMENT RESULTS:\n");
  printf("----------------------------------------------------------------------------\n");
  printf("%-20s   %-6s   %-4s  %-6s  %-4s   %-8s  %-5s\n",
	 "name",
	 "points",
	 "wins",
	 "losses",
	 "ties",
	 "time/turn",
	 "turns/game");
  printf("----------------------------------------------------------------------------\n");
  for (int i=0; i<num; i++)
    printf("%-20s   %6u   %4u  %6u  %4u   %8.6f  %5.1f\n",
	   player_list[i].name,
	   points[i],
	   wins[i],
	   losses[i],
	   ties[i],
	   player_stats[i].overall_time/player_stats[i].num_turns,
	   ((double)player_stats[i].num_turns)/player_stats[i].num_games);
  printf("----------------------------------------------------------------------------\n");
}
