#include "Sale_UI.h"
extern account_t gl_CurUser;
void Sale_UI_MgtEntry(void)
{
    char choice;
    Pagination_t paging;
    play_list_t list;
    play_node_t* tmp = list;
dod:
    List_Init(list, play_node_t);
    paging.pageSize     = SALESANALYSIS_PAGE_SIZE;
    paging.offset       = 0;
    paging.totalRecords = Play_Srv_FetchAll(list);
    Paging_Locate_FirstPage(list, paging);

    int play_id;
    do
    {
        printf("\n=========================================================\n");
        printf("**************** SALE  System ****************\n");
        printf("[C]显示演出计划\n");
        printf("[S]查询剧目名字\n");
        printf("[F]根据名称筛选剧目\n");
        printf("[R]eturn\n");
        printf("[E]xist.\n");
        printf("\n=======|[P]revPage|[N]extPage|=============\n");
        printf("Please input your choice:");
        scanf("%c", &choice);
        switch (choice)
        {
            case 'C':
            case 'c':
                List_ForEach(list, tmp)
                    Sale_UI_ShowScheduler(tmp->data.id);  //显示演出计划
                List_Destroy(list, play_node_t);
                goto dod;
                break;
            case 'S':
            case 's':
                printf("输入剧目名称\n");
                char name[256] = {0};
                scanf("%s", name);
                Play_Srv_FetchByName(name, );
                break;
            case 'F':
            case 'f':
                Play_Srv_FilterByName();
                break;
            case 'R':
            case 'r':
                List_Destroy(list, play_node_t);
                return;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                {
                    Paging_Locate_OffsetPage(list, paging, -1, play_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging))
                {
                    Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
                }
                break;
        }
    } while ('E' != choice && 'e' != choice);
}

void Sale_UI_ShowScheduler(int playID)
{
    Pagination_t paging;
    paging.pageSize = SALESANALYSIS_PAGE_SIZE;
    paging.offset   = 0;
    play_list_t list;
    schedule_list_t sch_list;

    List_Init(list, play_node_t);

    if (1 != Play_Srv_FetchByID(playID, &list->data))  //获取剧目
    {
        printf("获取剧目失败\n");
        List_Destroy(list, play_node_t);
        return;
    }

w:
    if (Schedule_Srv_FetchByPlay(sch_list, playID) == 0)  //获取演出计划
    {
        printf("获取演出计划失败\n");
        return;
    }
    char choice = 0;
    do
    {
        printf("\n=========================================================\n");
        printf("**************** SALE  System ****************\n");
        int i;
        // Paging_ViewPage_ForEach(sch_list, paging, play_node_t, pos, i)
        // {
        //     printf("%10d  %10d  %10d  %10d  %d--%d--%d--%d--%d--%d\n",
        //            pos->data.play_id, pos->data.id, pos->data.studio_id,
        //            pos->data.seat_count, pos->data.date.year,
        //            pos->data.date.month, pos->data.date.day,
        //            pos->data.time.hour, pos->data.time.minute,
        //            pos->data.time.second);
        // }
        printf("[T]显示演出票\n");
        printf(
            "\n=======|[P]revPage|[N]extPage|[E]xist|[R]eturn=============\n");
        printf("Please input your choice:");
        scanf("%c", &choice);

        switch (choice)
        {
            case 'T':
            case 't':
                Sale_UI_ShowTicket(&list->data);
                break;
            case 'R':
            case 'r':
                goto w;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                {
                    Paging_Locate_OffsetPage(list, paging, -1, play_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging))
                {
                    Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
                }
                break;
            default:
                choice = 'e';
        }
    } while ('e' != choice && choice != 'E');

    List_Destroy(list, play_node_t);
    return;
}

int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList)
{
    printf("输入位置行和列\n");
    int hang, lie;
    scanf("%d %d", &hang, &lie);

    int ret = 0;
    seat_node_t* seat_node;
    seat_node = Seat_Srv_FindByRowCol(seatList, hang, lie);
    if (seat_node == NULL)
    {
        printf("未找到座位信息\n");
        return -1;
    }
    ticket_node_t* tick_node =
        Ticket_Srv_FetchBySeatID(tickList, seat_node->data.id);
    if (tick_node == NULL)
    {
        printf("未找到票信息\n");
        return -1;
    }
    if (tick_node->data.status == TICKET_SOLD)
    {
        printf("票已售出\n");
        return -1;
    }
    tick_node->data.status = TICKET_SOLD;
    if (Ticket_Srv_Modify(&tick_node->data))
    {
        printf("修改票信息成功\n");
        return -1;
    }

    user_date_t curDate = DateNow();
    user_time_t curTime = TimeNow();
    sale_t sale;
    {
        sale.user_id   = gl_CurUser.id;
        sale.ticket_id = tick_node->data.id;
        sale.date      = curDate;
        sale.time      = curTime;
        sale.value     = 0 - tick_node->data.price;
        sale.type      = SALE_SELL;
    }

    if (Sale_Srv_Add(&sale))
    {
        printf("加入销售记录失败\n");
        return -1;
    }
    return sale.ticket_id;
}

void Sale_UI_RetfundTicket(void)
{
    int ticket_id;
    printf("输入票id\n");
    scanf("%d", &ticket_id);
    ticket_t buf;
    //票存在
    if (Ticket_Srv_FetchByID(ticket_id, &buf) != 1)
    {
        printf("票不存在\n");
        return;
    }

    //票未售出
    if (buf.status == 0)  //待售
    {
        printf("票未售出\n");
        return;
    }

    buf.status = TICKET_AVL;
    Ticket_Srv_Modify(&buf);
    user_date_t curDate = DateNow();
    user_time_t curTime = TimeNow();
    sale_t refound;
    {
        refound.user_id   = gl_CurUser.id;
        refound.ticket_id = ticket_id;
        refound.date      = curDate;
        refound.time      = curTime;
        refound.value     = 0 - buf.price;
        refound.type      = SALE_REFOUND;
    }

    Sale_Srv_Add(&refound);
    printf("退票成功\n");
    return;
}
