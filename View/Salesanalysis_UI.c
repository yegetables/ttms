/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : TTMS_UC_11
 * Author:   XUPT
 * Version:  v.1
 */
#include "Salesanalysis_UI.h"

void SalesAnalysis_UI_MgtEntry(void)
{
    char choice;
    int i;
    salesanalysis_node_t *newNode;
    salesanalysis_list_t head;
    List_Init(head, salesanalysis_node_t);
    Pagination_t paging;
    paging.pageSize     = SALESANALYSIS_PAGE_SIZE;
    paging.totalRecords = SalesAnalysis_Srv_StaticSale(head);
    SalesAnalysis_Srv_SortBySale(head);
    Paging_Locate_FirstPage(head, paging);
    play_node_t *pos;
    do
    {
        printf(
            "\n================================================================"
            "==\n");
        printf(
            "********************** 剧目票房排行信息 "
            "**********************\n");
        printf("%5s  %18s  %10s  %10s  %10s\n", "剧目名", "剧目区域",
               "剧目上座数量", "剧目票房", "剧目上映日期", "剧目下映日期");
        printf(
            "------------------------------------------------------------------"
            "\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
            printf("%5d  %18s  %10d  %10d  %10d\n", pos->data.name,
                   pos->data.area, newNode->data.totaltickets,
                   newNode->data.sales, pos->data.start_date,
                   pos->data.end_date);
        }

        printf(
            "------- Total Records:%2d ----------------------- Page %2d/%2d "
            "----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));
        printf(
            "******************************************************************"
            "\n");
        printf(
            "[P]revPage|[N]extPage | [A]dd|[D]elete|[U]pdate | [S]eat | "
            "[R]eturn");
        printf(
            "\n================================================================"
            "==\n");
        printf("Your Choice:");
        scanf("%c", &choice);
        switch (choice)
        {
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                {
                    Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging))
                {
                    Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
                }
                break;
            case 'r':
            case 'R':
                break;
            default:
                printf("Input Error,Please Input again\n");
                break;
        }
    } while (1);
    //释放链表空间
    List_Destroy(head, play_node_t);
}