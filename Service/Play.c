#include "Play.h"

#include <stdio.h>

#include "../Common/List.h"
#include "../Persistence/Play_Persist.h"

int Play_Srv_FetchAll(play_list_t list) {}

int Play_Srv_Add(play_t *data) {}

int Play_Srv_Modify(const play_t *data) {}

int Play_Srv_DeleteByID(int id) {}

int Play_Srv_FetchByID(int id, play_t *buf) {}
