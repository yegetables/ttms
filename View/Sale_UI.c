#include "Sale_UI.h"

void Sale_UI_MgtEntry(void)
{
    char choice;
    Pagination_t paging;
    play_list_t list;
dod:
    List_Init(list, play_node_t);
    paging.pageSize = SALESANALYSIS_PAGE_SIZE;
    paging.offset   = 0;

    //获取所有剧目
    paging.totalRecords = Play_Srv_FetchAll(list);
    int play_id;
    do
    {  //
        fflush(stdin);
        choice = getchar();

        switch (choice)
        {
            case 'C':
            case 'c':
                Sale_UI_ShowScheduler(play_id);  //显示演出计划
                List_Destroy(list, play_node_t);
                goto dod;
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
                List_Destroy(list, play_node_t);
                return;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                {
                    Paging_Locate_OffsetPage(list, paging, -1, studio_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging))
                {
                    Paging_Locate_OffsetPage(list, paging, 1, studio_node_t);
                }
                break;
        }
    } while ('E' != choice && 'e' != choice);
}

void Sale_UI_ShowScheduler(int playID)
{
    Play_Srv_FetchByID(playID);
    //失败
    return;
    //成功
    do
    {  //
        fflush(stdin);
        choice = getchar();

        switch (choice)
        {
            case 'T':
            case 't':
                Sale_UI_ShowTicket();
                break;
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
    Schedule_Srv_FetchByID();

    Seat_Srv_FetchByRoomID();
    Ticket_Srv_FetchBySchID();

    // show
    fflush(stdin);
    choice = getchar();

    switch (choice)
    {
        case 'R':
        case 'r':
            return;
        case 'B':
        case 'b':
            Sale_UI_SellTicket();
            Ticket_UI_Print();
            return;
    }
}

int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList)
{
    // TODO:
    return 0;
}

void Sale_UI_RetfundTicket(void)
{
    int ticket_id;
    printf("输入票id\n");
    scanf("%d", &ticket_id);
    Ticket_Srv_FetchByID()
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

void Sale_UI_ShowTicket(int playID);
