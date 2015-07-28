#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "simulate.h"
#include "human.h"
#include "random.h"
#include "simple.h"

int main(int argc, char **argv)
{
  double max_time = 10;

  srand48(time(NULL));

  if (argc>2)
    simulate_tournament(argv+1, argc-1, max_time);
  else
    if (argc<=2)
      {
	player_info_t ai_player;
	stats_t ai_stats;
	stats_t human_stats;

	if (argc==2)
	  get_player_info(argv[1],&ai_player);
	else
	  get_player_info("simple",&ai_player);

	printf("Going to simulate an individual game\n");

	simulate_game(human, 
		      ai_player.player_function, 
		      &human_stats,
		      &ai_stats,
		      max_time,
		      0);
      }

  return 0;
}
