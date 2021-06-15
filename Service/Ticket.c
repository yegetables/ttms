#include "Ticket.h"

int Schedule_Srv_FetchByID(int id, schedule_t* buf)
{
    return Schedule_Perst_SelectByID(id, buf);
}
int Ticket_Srv_GenBatch(int schedule_id)
{
    int number = -1;
    seat_list_t seat_head;
    List_Init(seat_head, seat_list_t);
    if (seat_head == NULL) return number;
    number = 0;
    //????
    if ((re = Seat_Srv_FetchValidByRoomID(seat_head,? ))>=0)
    {
        //成功
        number += re;
        Ticket_Perst_Insert(seat_head, schedule_id);
    }
    else
    {
        printf("error %s:%d", __FILE__, __LINE__);
    }
    return number;
}

