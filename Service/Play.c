#include "Play.h"

#include <stdio.h>

#include "../Common/List.h"
#include "../Persistence/Play_Persist.h"

int Play_Srv_FetchAll(play_list_t list) {}

int Play_Srv_Add(play_t *data) {}

int Play_Srv_Modify(const play_t *data) {}

int Play_Srv_DeleteByID(int id) {}

int Play_Srv_FetchByID(int id, play_t *buf)
{
    play_list_t list;
    List_Init(list, play_node_t);
    if (Play_Srv_FetchAll(list) < 0) return -1;
    play_list_t cur;
    List_ForEach(list, cur)
    {
        if (cur->data.id == id)
        {
            buf = &(cur->data);
            return 1;
        }
    }
    return -1;
}

int Play_Srv_FetchByName(char *name, play_t *buf)
{
    play_list_t list;
    List_Init(list, play_node_t);
    if (Play_Srv_FetchAll(list) < 0) return -1;
    play_list_t cur;
    List_ForEach(list, cur)
    {
        if (strcmp(cur->data.name, name) == 0)
        {
            buf = &(cur->data);
            return 1;
        }
    }
    return -1;
}
