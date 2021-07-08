#include "Sale_UI.h"
extern account_t gl_CurUser;
void Sale_UI_MgtEntry(void)
{
    char choice;
    Pagination_t paging;
    play_list_t list;
    play_list_t newlist;
    play_node_t* tmp = NULL;
dod:
    List_Init(list, play_node_t);
    List_Init(newlist, play_node_t);
    paging.pageSize     = SALESANALYSIS_PAGE_SIZE;
    paging.offset       = 0;
    paging.totalRecords = Play_Srv_FetchAll(list);
    // printf("paging.totalRecords:%d\n", paging.totalRecords);
    Paging_Locate_FirstPage(list, paging);

    // int play_id = 0;
    do
    {
        printf("\n=========================================================\n");
        printf("**************** 售票系统 ****************\n");
        printf("[C]显示演出计划\n");
        printf("[S]查询剧目名字\n");
        printf("[F]根据名称筛选剧目\n");
        printf("[R]返回\n");
        printf("[E]退出.\n");
        printf("\n=======|[P]上一页|[N]下一页|=============\n");
        printf("Please input your choice:");
        scanf("%c", &choice);
        getchar();
        switch (choice)
        {
            case 'C':
            case 'c':
                List_ForEach(list, tmp)
                    Sale_UI_ShowScheduler(tmp->data.id);  //显示演出计划
                List_Destroy(list, play_node_t);
                printf("显示完毕\n");
                goto dod;
                break;
            case 'S':
            case 's':
                printf("输入剧目名称\n");
                char name1[256] = {0};
                scanf("%s", name1);
                play_t buf;
                if (1 != Play_Srv_FetchByName(name1, &buf))
                    printf("未找到剧目信息\n");
                else
                    printf("剧目id:%d\n剧目名称:%s\n", buf.id, buf.name);
                break;
            case 'F':
            case 'f':
                printf("输入剧目名称\n");
                char name2[256] = {0};
                scanf("%s", name2);

                int num = Play_Srv_FilterByName(newlist, name2);
                if (num == 0)
                {
                    printf("未找到剧目信息\n");
                    break;
                }
                List_ForEach(newlist, tmp)
                {
                    printf("剧目id:%d\n剧目名称:%s\n", tmp->data.id,
                           tmp->data.name);
                }
                List_Destroy(list, play_node_t);

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
    printf("退出程序\n");
    exit(0);
}

void Sale_UI_ShowScheduler(int playID)
{
    Pagination_t paging;
    paging.pageSize = SALESANALYSIS_PAGE_SIZE;
    paging.offset   = 0;
    play_list_t list;
    schedule_list_t sch_list;

    List_Init(list, play_node_t);
    List_Init(sch_list, schedule_node_t);

    if (1 != Play_Srv_FetchByID(playID, &list->data))  //获取剧目
    {
        printf("获取剧目失败\n");
        List_Destroy(list, play_node_t);
        return;
    }
    schedule_list_t tmp;
w:
    if (Schedule_Srv_FetchByPlay(sch_list, playID) <= 0)  //获取演出计划
    {
        printf("获取演出计划失败\n");
        return;
    }
    char choice = 0;
    do
    {
        printf("\n=========================================================\n");
        printf("**************** 售票系统 ****************\n");
        // int i;
        printf("演出计划id||剧目ID||演出厅ID||座位数\n");

        List_ForEach(sch_list, tmp)
            printf("%10d %6d %8d %6d\n", tmp->data.id, tmp->data.play_id,
                   tmp->data.studio_id, tmp->data.seat_count);
        printf("--------------------------------\n");
        printf("[T]显示演出票\n");
        printf("\n=======|[P]上一页|[N]下一页|[E]退出|[R]返回=============\n");
        printf("Please input your choice:");
        scanf("%c", &choice);

        switch (choice)
        {
            case 'T':
            case 't':
                Sale_UI_ShowTicket(list->data);
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
    // printf("%d %d \n\n", hang, lie);

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

void Sale_UI_ShowTicket(play_t p_t)
{
    printf(
        "\n========================================================="
        "\n");
    printf("**************** 售票系统 ****************\n");
    //    Schedule_Srv_FetchByID();
    schedule_list_t sch_t_head;  //演出计划
    schedule_node_t* sch_t;
    List_Init(sch_t_head, schedule_node_t);
    Schedule_Srv_FetchByPlay(sch_t_head, p_t.id);
    // printf("asda\n");
    seat_list_t seat_t_head;
    // seat_node_t* seat_sch;

    ticket_list_t ticket_t_head, ticket_tmp;
    ticket_node_t* ticket_sch;
    List_Init(ticket_t_head, ticket_node_t);
    List_Init(seat_t_head, seat_node_t);
    List_ForEach(sch_t_head, sch_t)  // plan
    {                                //遍历演出计划
        // printf("asdafa\n\n");

        // printf("sfafafada\n");
        int count =
            Ticket_Srv_FetchBySchID(sch_t->data.id, ticket_t_head);  // piao
        printf("ticket num %d\n", count);
        count =
            Seat_Srv_FetchByRoomID(seat_t_head, sch_t->data.studio_id);  // seat
        //  printf("111\n");
        printf("studio num %d\n", count);
        // for (ticket_sch = (ticket_t_head)->next, seat_sch =
        // (seat_t_head)->next;
        //      ticket_sch != ticket_t_head, seat_sch != seat_t_head;
        //      ticket_sch = ticket_sch->next, seat_sch = seat_sch->next);
        printf("%10s  %10s  %10s  %15s  %10s  %10s  %10s  %30s  %15s\n",
               "ticket_id", "seat_id", "price", "ticket_status_t", "room_id",
               "row", "column", "show time", "seat_ticket_status");
        List_ForEach(ticket_t_head, ticket_tmp)
        {
            // ticket_node_t* ticnod = Ticket_Srv_FetchBySeatID(
            //     ticket_t_head, ticket_tmp->data.seat_id);

            // piao   座位id   行列
            // printf("sddafafafaf?\n");
            seat_t ss;
            Seat_Srv_FetchByID(ticket_tmp->data.seat_id, &ss);
            // printf("saout ???\n");

            printf(
                "%10d  %10d  %10d  %15d  %10d  %10d  %10d "
                "%d-%d-%d-%d-%d-%d  "
                "%10d\n",
                ticket_tmp->data.id, ticket_tmp->data.seat_id,
                ticket_tmp->data.price, ticket_tmp->data.status,
                sch_t->data.studio_id, ss.row, ss.column, sch_t->data.date.year,
                sch_t->data.date.month, sch_t->data.date.day,
                sch_t->data.time.hour, sch_t->data.time.minute,
                sch_t->data.time.second, ticket_tmp->data.status);
            // printf("asfffffffffff\n");
        }
        // printf("33333\n");
    }

    char choice = 0;
    do
    {
        printf("[B]uy购买票\n");
        printf("\n=======[E]xist|[R]eturn=============\n");
        printf("Please input your choice:");
        getchar();
        scanf("%c", &choice);
        getchar();
        switch (choice)
        {
            case 'B':
            case 'b':
                Sale_UI_SellTicket(ticket_t_head, seat_t_head);
                // Ticket_UI_Print();
                break;
            case 'R':
            case 'r':
            default:
                choice = 'e';
        }
    } while ('e' != choice && choice != 'E');
    List_Free(ticket_t_head, ticket_node_t);
    List_Free(seat_t_head, seat_node_t);

    return;
}
