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
        printf("  %10s  %10s  %10s  %10s %10s %10s \n", "剧目名", "剧目区域",
               "剧目上座数量", "剧目票房", "剧目上映日期", "剧目下映日期");
        printf(
            "------------------------------------------------------------------"
            "\n");
        //显示数据
        char sho1[50] = {0};
        char sho2[50] = {0};
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
            memset(sho1, 0, sizeof(sho1));
            memset(sho2, 0, sizeof(sho2));
            sprintf(sho1, "%d-%d-%d", pos->data.start_date.year,
                    pos->data.start_date.month, pos->data.start_date.day);
            sprintf(sho2, "%d-%d-%d", pos->data.end_date.year,
                    pos->data.end_date.month, pos->data.end_date.day);
            printf("%10s  %10s  %10ld  %10ld  %10s %10s\n", pos->data.name,
                   pos->data.area, newNode->data.totaltickets,
                   newNode->data.sales, sho1, sho2);
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
            "[P]revPage|[N]extPage"
            "[R]eturn");
        printf(
            "\n================================================================"
            "==\n");
        printf("Your Choice:");
        fflush(stdin);
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
    } while ('E' != choice && 'e' != choice);
    //释放链表空间
    List_Destroy(head, play_node_t);
}