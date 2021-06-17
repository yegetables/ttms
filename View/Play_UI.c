#include "Play_UI.h"

#include <stdio.h>
#include <string.h>

#include "../Common/List.h"
#include "../Service/Play.h"
#include "Schedule_UI.h"
static const int PLAY_PAGE_SIZE = 5;

void Play_UI_MgtEntry()
{
    int i, id;
    char choice;

    play_list_t head;
    play_node_t *pos;
    Pagination_t paging;

    List_Init(head, play_node_t);
    paging.offset   = 0;
    paging.pageSize = PLAY_PAGE_SIZE;

    //载入数据
    paging.totalRecords = Play_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head, paging);

    do
    {
        printf(
            "\n================================================================"
            "==\n");
        printf(
            "********************** 剧目信息管理界面 "
            "**********************\n");
        printf("%5s  %18s  %5s  %10s  %5s  %5s  %11s  %11s  %5s\n", "剧目ID",
               "剧目名称", "剧目类型", "剧目出品地区", "剧目等级", "时长(分钟)",
               "开始放映日期", "结束放映日期", "票价(元)");
        printf(
            "------------------------------------------------------------------"
            "\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
            printf(
                "%5d  %18s  %5d  %10s  %5d  %5d  %4d年%2d月%2d日  "
                "%4d年%2d月%2d日  %5s\n",
                pos->data.id, pos->data.name, pos->data.type, pos->data.area,
                pos->data.rating, pos->data.duration, pos->data.start_date.year,
                pos->data.start_date.month, pos->data.start_date.month,
                pos->data.end_date.year, pos->data.end_date.month,
                pos->data.end_date.day, pos->data.price);
        }
        printf(
            "------- 总页数:%2d ----------------------- Page "
            "%2d/%2d "
            "----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));
        printf(
            "******************************************************************"
            "\n");
        printf(
            "[P]上一页\n"
            "[N]下一页\n"
            "[A]增加新剧目\n"
            "[D]删除剧目\n"
            "[U]修改剧目\n"
            "[Q]查询剧目\n"
            "[S]安排演出\n"
            "[R]返回\n");
        printf(
            "\n================================================================"
            "==\n");
        printf("输入选项:");
        scanf("%c", &choice);
        switch (choice)
        {
            case 'a':
            case 'A':
                if (Play_UI_Add())  //新添加成功，跳到最后一页显示
                {
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, play_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("I输入删除剧目id:");
                scanf("%d", &id);
                if (Play_UI_Delete(id))
                {  //从新载入数据
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    List_Paging(head, paging, play_node_t);
                }
                break;
            case 'u':
            case 'U':
                printf("输入需要修改的剧目id:");
                scanf("%d", &id);
                if (Play_UI_Modify(id))
                {  //从新载入数据
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    List_Paging(head, paging, play_node_t);
                }
                break;
            case 's':
            case 'S':
                printf("输入需要安排演出的放映厅id");
                scanf("%d", &id);
                Schedule_UI_MgtEntry(id);
                paging.totalRecords = Play_Srv_FetchAll(head);
                List_Paging(head, paging, play_node_t);
                break;
            case 'q':
            case 'Q':
                printf("输入需要查询的剧目id\n");
                scanf("%d", &id);
                Play_UI_Query(id);
                break;
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
                return;
                break;
            default:
                printf("输入有误,请重新输入\n");
                break;
        }
    } while (1);
    //释放链表空间
    List_Destroy(head, play_node_t);
}
int Play_UI_Add() { return 1; }
int Play_UI_Modify(int id) { return 1; }
int Play_UI_Delete(int id) { return 1; }

int Play_UI_Query(int id) { return 1; }

// Play_UI_FetchByName();