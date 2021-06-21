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
int max(int a, int b) { return a > b ? a : b; }
int _strcmp(char *s1, char *s2)
{
    int dp[100][100] = {0};
    int len1, len2;
    len1 = strlen(s1), len2 = strlen(s2);
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[len1][len2];
}

int Play_Srv_FilterByName(play_list_t list, char *key)
{
    int recCount = 0;
    play_list_t headStr;
    List_Init(headStr, play_node_t);
    if (Play_Srv_FetchAll(headStr) <= 0) return recCount;
    play_node_t *curPos;
    List_ForEach(headStr, curPos)
    {
        if (_strcmp(curPos->data.name, key) >= 1)
        {
            List_AddTail(list, curPos);
            recCount++;
        }
    }
    return recCount;
}