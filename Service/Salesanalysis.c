/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : TTMS_UC_11
 * Author:   XUPT
 * Version:  v.1
 */
#include "Salesanalysis.h"

#include "../Common/List.h"
#include "../Service/Play.h"
#include "stdio.h"
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list)
{
    if (list != NULL)
    {
        play_node_t *pos;
        salesanalysis_node_t *newNode;
        play_list_t playList;
        int sold;
        List_Free(list, salesanalysis_node_t);
        List_Init(playList, play_node_t);
        if(Play_Srv_FetchAll(playList) <= 0)
        {
            return 0;
        }
        else
        {
        List_AddTail(playList, newNode);
        List_ForEach(playList, pos)
        {
            newNode->data.sales        = Schedule_Srv_StatRevByPlay(pos->data.id, &sold);
            newNode->data.totaltickets = sold;
        }
        List_Destroy(playList, play_node_t);
        }
    }
    else
    {
        printf("Error!!!");
    }
}