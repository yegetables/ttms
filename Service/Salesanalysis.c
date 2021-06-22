/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : TTMS_UC_11
 * Author:   XUPT
 * Version:  v.1
 */
#include "Salesanalysis.h"

int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list)
{
    int a = 0;
    if (list != NULL)
    {
        play_node_t *pos;
        salesanalysis_node_t *newNode =
            (salesanalysis_node_t *)malloc(sizeof(salesanalysis_node_t));
        play_list_t playList;
        int sold;
        List_Free(list, salesanalysis_node_t);
        List_Init(playList, play_node_t);
        if (Play_Srv_FetchAll(playList) <= 0)
        {
            return 0;
        }
        else
        {
            List_ForEach(playList, pos)
            {
                newNode->data.sales =
                    Schedule_Srv_StatRevByPlay(pos->data.id, &sold);
                newNode->data.totaltickets = sold;
                strcpy(newNode->data.area, pos->data.area);
                strcpy(newNode->data.name, pos->data.name);
                newNode->data.start_date = pos->data.start_date;
                newNode->data.end_date   = pos->data.end_date;
                List_AddTail(list, newNode);
                a++;
            }
            List_Destroy(playList, play_node_t);
        }
    }
    else
    {
        printf("Error!!!\n");
        return 0;
    }
    return a;
}

void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list)
{
    // 请补充完整
    if (List_IsEmpty(list))
    {
        return;
    }
    list->prev->next              = NULL;
    salesanalysis_list_t listLeft = list->next;
    list->next = list->prev = list;
    while (1)
    {
        if (listLeft == NULL)
        {
            return;
        }
        salesanalysis_list_t p = listLeft;
        listLeft               = listLeft->next;
        SalesAnalysis_Srv_AddToSoftedList(list, p);
    }
}
void SalesAnalysis_Srv_AddToSoftedList(salesanalysis_list_t list,
                                       salesanalysis_node_t *node)
{
    // 请补充完整
    if List_IsEmpty (list)
    {
        List_AddTail(list, node);
        return;
    }
    salesanalysis_list_t curPos;
    List_ForEach(list, curPos)
    {  //大到小
        if (!(curPos != list && curPos->data.sales > node->data.sales))
        {
            List_InsertBefore(curPos, node);
            return;
        }
    }
    List_AddTail(list, node);
}