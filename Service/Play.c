#include "Play.h"

int Play_Srv_FetchAll(play_list_t list) { return Play_Perst_SelectAll(list); }

int Play_Srv_Add(play_t *data) { return Play_Perst_Insert(data); }

int Play_Srv_Modify(const play_t *data) { return Play_Perst_Update(data); }

int Play_Srv_DeleteByID(int id) { return Play_Perst_RemByID(id); }

int Play_Srv_FetchByID(int id, play_t *buf)
{
    return Play_Perst_SelectByID(id, buf);
}

int Play_Srv_FetchByName(char *name, play_t *buf)
{
    play_list_t list;
    List_Init(list, play_node_t);
    if (Play_Srv_FetchAll(list) <= 0) return 0;
    play_node_t *curPos;
    List_ForEach(list, curPos)
    {
        if (strcmp(curPos->data.name, name) == 0)
        {
            buf = &(curPos->data);
            return 1;
        }
    }
    return 0;
}
