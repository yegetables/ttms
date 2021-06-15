#include "Ticket_UI.h"

// void Queries_Menu(void) {}

// void Sale_UI_MgtEntry(void);

void Ticket_UI_MgtEntry(int schedule_id)
{
    schedule_t *buf = (schedule_t *)malloc(sizeof(schedule_t));
    //获取演出计划信息
    if (1 != Schedule_Srv_FetchByID(schedule_id, buf))
    {
        printf("error : Schedule_Srv_FetchByID %s %d!\n", __FILE__, __LINE__);
        exit(1);
    }
    //用剧目id作为参数 ,获取剧目信息
    // TODO:
    Play_Srv_FetchByID(play_id);
//显示剧目名称,演出厅编号,演出日期演出时间

//接受输入,
reshow:
    int witch = -1;
    //选择 生成还是重新生成 还是返回上一层
    scanf("%d", &which);
    switch (which)
    {
        case 2:
            //重新生成票
            Ticket_Srv_DeleteBatch();
        case 1:
            //?生成票?
            Ticket_Srv_GenBatch();
            // 跳转步骤e
            return;
        case 0:
            //返回上一层,步骤e
            return;
        default:
            //提示错误
            break;
    }
    goto reshow;
}

void Sale_UI_MgtEntry(void)
{
    char choice;
    Pagination_t paging;

    List_Init(head, play_list_t);
    paging.pageSize = SALESANALYSIS_PAGE_SIZE;
    paging.offset   = 0;
    //获取所有剧目
    paging.totalRecords = Play_Srv_FetchALL();

    do
    {  //
        fflush(stdin);
        choice = getchar();

        switch (choice)
        {
            case 'C':
            case 'c':
                Sale_UI_ShowScheduler();  //显示演出计划
                break;
            case 'S':
            case 's':
                Play_UI_FetchByName();
                break;
            case 'F':
            case 'f':
                Play_Srv_FilterByName();
                break;
            case 'R':
            case 'r':
                return;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                {
                    Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging))
                {
                    Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
                }
                break;
        }
    } while ('E' != choice && 'e' != choice);
}