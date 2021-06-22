#include "Schedule_UI.h"


#include "./Schedule_UI.h"

#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Ticket.h"
#include "../Service/Play.h"
#include "../Common/TimeLegal.h"
#include"../Common/Common.h"
#include"../Service/Schedule_Qry.h"
static const int SCHEDULE_PAGE_SIZE = 5;
void Schedule_UI_MgtEntry(int play_id)
{
    char choice;
    int id;
    int i;
    schedule_list_t head;
    schedule_node_t *pos;
    Pagination_t paging;

    List_Init(head, studio_node_t);
    paging.offset   = 0;
    paging.pageSize = SCHEDULE_PAGE_SIZE;

    paging.totalRecords = Schedule_Srv_FetchByPlay(head, play_id);
    Paging_Locate_FirstPage(head, paging);

    do
    {
        printf(
            "\n================================================================"
            "==\n");
        printf(
            "********************** Schedule  List "
            "**********************\n");
        printf("%10s  %10s  %10s  %10s  %30s\n", "Play_id", "id", "studio_id",
               "seat_count", "Schedule time");
        printf(
            "------------------------------------------------------------------"
            "\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i)
        {
            printf("%10d  %10d  %10d  %10d  %d--%d--%d--%d--%d--%d\n",
                   pos->data.play_id, pos->data.id, pos->data.studio_id,
                   pos->data.seat_count, pos->data.date.year,
                   pos->data.date.month, pos->data.date.day,
                   pos->data.time.hour, pos->data.time.minute,
                   pos->data.time.second);
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
        getchar();
        switch (choice)
        {
            case 'a':
            case 'A':
                if (Schedule_UI_Add(play_id))  //新添加成功，跳到最后一页显示
                {
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, studio_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("Input the ID:");
                scanf("%d", &id);
                if (Schedule_UI_Delete(id))
                {  //从新载入数据
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    List_Paging(head, paging, studio_node_t);
                }
                break;
            case 'u':
            case 'U':
                printf("Input the ID:");
                scanf("%d", &id);
                if (Schedule_UI_Modify(id))
                {  //从新载入数据
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    List_Paging(head, paging, studio_node_t);
                }
                break;
            case 't':
            case 'T':
                printf("Input the RoomID:");
                scanf("%d", &id);
                Seat_UI_MgtEntry(id);
                paging.totalRecords = Schedule_Srv_FetchAll(head);
                List_Paging(head, paging, studio_node_t);
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
            case 'r':
            case 'R':
                break;
            default:
                printf("Input Error,Please Input again\n");
                break;
        }
    } while (choice != 'r' || choice != 'R');
}

int Schedule_UI_Add(int play_id)
{
    int newCount = 0;
    char choice;
    schedule_t sch;
    do
    {
        printf("\n=======================================================\n");
        printf("****************  Add New Schedule  ****************\n");
        printf("-------------------------------------------------------\n");
        printf("Schedule id:");
        fflush(stdin);
        scanf("%d", &(sch.id));
        printf("Schedule play_id:");
        scanf("%d", &(sch.play_id));
        printf("Schedule studio_id:");
        scanf("%d", &(sch.studio_id));
        do
        {
            printf("The Schedule Time:===========>");
            scanf("%d %d %d %d %d %d", &(sch.date.year), &(sch.date.month),
                  &(sch.date.day), &(sch.time.hour), &(sch.time.minute),
                  &(sch.time.second));
        } while (!IsTimeLegal(sch.date.year, sch.date.month, sch.date.day,
                              sch.time.hour, sch.time.minute, sch.time.second));

        printf("Schedule seat_count:");
        scanf("%d", &(sch.seat_count));
        printf("=======================================================\n");

        if (Schedule_Srv_Add(&sch))
        {
            newCount += 1;
            printf("The new Schedule added successfully!\n");
        }
        else
        {
            printf("The new Schedule added failed!\n");
        }
        printf("-------------------------------------------------------\n");
        printf("[A]dd more, [R]eturn:");
        fflush(stdin);
        scanf("%c", &choice);
    } while ('a' == choice || 'A' == choice);

    return newCount;
}

int Schedule_UI_Modify(int id)
{
    schedule_t sch;
    int rtn = 0;
    if (!Schedule_Srv_FetchByID(id, &sch))
    {
        printf("The room does not exist!\nPress [Enter] key to return!\n");
        getchar();
        return 0;
    }
    printf("\n=======================================================\n");
    printf("****************  Update Schedule  ****************\n");
    printf("-------------------------------------------------------\n");
    printf("Schedule ID[%d]=====>", sch.id);
    fflush(stdin);
    scanf("%d", (&sch.id));
    printf("Schedule Play_id[%d]=====>", sch.play_id);
    scanf("%d", &(sch.play_id));
    printf("Schedule studio_id[%d]=====>", sch.studio_id);
    scanf("%d", (&sch.studio_id));
    printf("Schedule seat_count[%d]====>", sch.seat_count);
    scanf("%d", &(sch.seat_count));
    do
    {
        printf("The Schedule Time:[%d--%d--%d--%d--%d--%d]\n========>",
               sch.date.year, sch.date.month, sch.date.day, sch.time.hour,
               sch.time.minute, sch.time.second);
        scanf("%d %d %d %d %d %d", &(sch.date.year), &(sch.date.month),
              &(sch.date.day), &(sch.time.hour), &(sch.time.minute),
              &(sch.time.second));
    } while (!IsTimeLegal(sch.date.year, sch.date.month, sch.date.day,
                          sch.time.hour, sch.time.minute, sch.time.second));

    if (Schedule_Srv_Modify(&sch))
    {
        printf("This Schedule Modify Successfully!");
        rtn++;
        return rtn;
    }
    else
    {
        printf("fail to modify!");
        return 0;
    }
}

int Schedule_UI_Delete(int id)
{
    int rtn = 0;
    if (!Schedule_Srv_Delete(id))
    {
        printf("error to delete!");
        return 0;
    }
    else
    {
        printf("delete Successfully!");
        rtn++;
        return rtn;
    }
}
