#include "Sale_UI.h"

void Sale_UI_MgtEntry(void)
{
    char choice;
    Pagination_t paging;
    play_list_t list;
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
    List_Init(list, play_node_t);

    if (1 != Play_Srv_FetchByID(playID, &list->data))
    {
        List_Destroy(list, play_node_t);
        return;
    }

w:
    Schedule_Srv_FetchByPlay();
    char choice;
    do
    {  //
        fflush(stdin);
        choice = getchar();

        switch (choice)
        {
            case 'T':
            case 't':
                Sale_UI_ShowTicket(playID);
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
    } while ('e' != choice);

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

void Sale_UI_ShowTicket(int playID);
