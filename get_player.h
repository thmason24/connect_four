#ifndef _GET_PLAYER_H_
#define _GET_PLAYER_H_

#include "types.h"

typedef struct {

  char name[50];

  player_t player_function;

} player_info_t;

int get_player_info(const char *name, player_info_t *player);

#endif
