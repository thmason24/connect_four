#include <string.h>

#include "simple.h"
#include "human.h"
#include "random.h"
#include "better_random.h"
#include "offensive.h"
#include "thmmqc_main.h"
#include "thmmqc_circle.h"
#include "get_player.h"

// ------------------------------------------------------------
// returns a structure with the player name and function
// notes:
//   - you should add your player or players here to test them

int get_player_info(const char *name, player_info_t *player)
{
  player_info_t player_info[] = {
    { "simple", simple },
    { "human",  human },
    { "random", random },
    { "better_random", better_random},
    { "offensive", offensive },
    { "thmmqc", thmmqc},
    { "circle", circle}
  };

  int num_players = sizeof(player_info)/sizeof(player_info[0]);

  for (int i=0; i<num_players; i++)
    if (strcmp(name,player_info[i].name)==0)
      {
	strcpy(player->name,player_info[i].name);
	player->player_function = player_info[i].player_function;

	return 1;
      }

  return 0;
}
