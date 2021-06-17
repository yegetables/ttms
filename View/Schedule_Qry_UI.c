#include"Schedule_Qry_UI.h"
#include "../Common/List.h"
#include"../Service/Play.h"
#include"../Service/Schedule.h"
#include"../Service/Play.h"
#include"../Service/Studio.h"
#include"../Service/Schedule_Qry.h"

static const int SCHEDULE_QUERY_SIZE = 5;

#include<stdio.h>

void Schedule_UI_ListAll(void){
    char choice;
    int i,id;
    char condt[30];

    schedule_list_t head;
    schedule_node_t *pos;
    Pagination_t paging;

    studio_t stu;
    play_t play;
    List_Init(head,schedule_node_t);
    
    paging.offset = 0;
    paging.pageSize = SCHEDULE_QUERY_SIZE;

    paging.totalRecords = Schedule_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head,paging);

    do{
         printf(
            "\n================================================================"
            "==\n");
        printf(
            "********************** Schedule  List "
            "**********************\n");
        printf("%10s  %10s  %10s  %10s  %30s  %15s  %15s\n", "Play_id", "id", "studio_id",
               "seat_count", "Schedule_time","Play_name","Studio_name");
        printf(
            "------------------------------------------------------------------"
            "\n");
            Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i)
        {
            Play_Srv_FetchByID(pos->data.play_id,&play);
            Studio_Srv_FetchByID(pos->data.studio_id,&stu);
            printf("%10d  %10d  %10d  %10d  %d--%d--%d--%d--%d--%d  %15s  %15s\n", pos->data.play_id,
                   pos->data.id, pos->data.studio_id, pos->data.seat_count,
                   pos->data.date.year,pos->data.date.month,pos->data.date.day,
                   pos->data.time.hour,pos->data.time.minute,pos->data.time.second,
                   play.name,stu.name);
        }
        rintf(
            "------- Total Records:%2d ----------------------- Page %2d/%2d "
            "----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));
        printf(
            "******************************************************************"
            "\n");
        printf(
            "[P]revPage|[N]extPage | [Q]uery | "
            "[R]eturn");
        printf(
            "\n================================================================"
            "==\n");
        printf("Your Choice:");
        scanf("%c", &choice);
        switch (choice)
        {
            case 'q':
            case 'Q':
            printf("Please enter the name to Query:");
            scanf("%s",condt);
                if(Schedule_UI_Query(condt)){
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    List_Paging(head,paging,schedule_node_t);
                }

            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                {
                    Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging))
                {
                    Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
                }
                break;
            case 'r':
            case 'R':
                break;
            default:
                printf("Input Error,Please Input again\n");
                break;
        }
    }while(!(choice=='r' || choice == 'R'));
    List_Destroy(head,schedule_node_t);
}


int Schedule_UI_Query(char *play_name){
    play_list_t list_p;
    int recCount = 0;
    Play_Srv_FetchByName(play_name,list_p);
    schedule_list_t list_s;
    while(list_p != NULL){
        Schedule_Srv_FetchByPlay(list_s,list_p->data.id);
        while(list_s != NULL){
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
            printf("%10d  %10d  %10d  %10d  %d--%d--%d--%d--%d--%d\n",
                   list_s->data.play_id, list_s->data.id, list_s->data.studio_id,
                   list_s->data.seat_count, list_s->data.date.year,
                   list_s->data.date.month, list_s->data.date.day,
                   list_s->data.time.hour, list_s->data.time.minute,
                   list_s->data.time.second);

        list_s = list_s->next;
        } 
        list_p = list_p->next;
    }   
        
       
    }

    
