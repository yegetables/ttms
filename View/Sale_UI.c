#include "Sale_UI.h"

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
        List_Destroy(list, play_node_t);
        return;
    }

w:
    Schedule_Srv_FetchByPlay(sch_list, playID);  //获取演出计划
    char choice = 0;
    do
    {
        printf("\n=========================================================\n");
        printf("**************** SALE  System ****************\n");
        printf("[T]显示演出票\n");
        printf(
            "\n=======|[P]revPage|[N]extPage|[E]xist|[R]eturn=============\n");
        printf("Please input your choice:");
        scanf("%c", &choice);

        switch (choice)
        {
            case 'T':
            case 't':
                // MARK:Sale_UI_ShowTicket
                Sale_UI_ShowTicket(sch_list, list->data);
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
    ret     = Seat_Srv_FindByRC(hang, lie);

    Ticket_Srv_FetchByID(ret);
    //未找到return -1;
    Ticket_Srv_Modify();

    sale_t sale;
    {
        sale.id        = ;
        sale.user_id   = ;
        sale.ticket_id = ;
        sale.date      = ;
        sale.time      = ;
        sale.value     = ;
        sale.type      = SALE_SELL;
    }

    //票已售

    Sale_Srv_Add(&sale);

    return ret;
}

void Sale_UI_RetfundTicket(void)
{
    int ticket_id;
    printf("输入票id\n");
    scanf("%d", &ticket_id);
    Ticket_Srv_FetchByID();
    //票id->判断票存在
    //不存在
    return;

    //判断已售?
    //未售
    {
        printf("票未售出\n");
        return;
    }

    Ticket_Srv_Modify();
    sale_t refound;
    {
        refound.id        = ;
        refound.user_id   = ;
        refound.ticket_id = ;
        refound.date      = ;
        refound.time      = ;
        refound.value     = ;
        refound.type      = SALE_REFOUND;
    }

    Sale_Srv_Add();
    return;
}

void Sale_UI_ShowTicket(void)
{
    //    Schedule_Srv_FetchByID();
    Schedule_Srv_FetchByPlay();
    Seat_Srv_FetchByRoomID();
    Ticket_Srv_FetchBySchID();

    char choice = 0;
    do
    {
        printf("\n=========================================================\n");
        printf("**************** SALE  System ****************\n");
        printf("[B]uy购买票\n");
        printf("\n=======[E]xist|[R]eturn=============\n");
        printf("Please input your choice:");
        scanf("%c", &choice);

        switch (choice)
        {
            case 'B':
            case 'b':
                Sale_UI_SellTicket();
                Ticket_UI_Print();
                break;
            case 'R':
            case 'r':
                goto w;
            default:
                choice = 'e';
        }
    } while ('e' != choice && choice != 'E');

    return;
}