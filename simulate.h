#include "types.h"
#include "get_player.h"

int simulate_game(player_t player1, 
		  player_t player2, 
		  stats_t *player1_stats,
		  stats_t *player2_stats,
		  double max_time,
		  int quiet);

void simulate_tournament(char **names, 
			 int num,
			 double max_time);

int simulate_one_turn(state_t *state, 
		      state_t *orig_state,
		      player_t player,
		      stats_t *player_stats,
		      int *last_move,
		      int player_id,
		      double max_time);

void print_tournament_results(player_info_t *player_list,
			      int *points,
			      int *wins,
			      int *losses,
			      int *ties,
			      stats_t *player_stats,
			      int num);
