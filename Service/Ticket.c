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
    int re = 0;
    if ((re = Seat_Srv_FetchValidByRoomID(seat_head, schedule_id)) >= 0)
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
void Ticket_Srv_DeleteBatch(int schedule_id)
{
    int found = 0;
    found     = Ticket_Perst_Rem(schedule_id);
    return found;
}
int Ticket_Srv_FetchByID(int id, ticket_t* buf)
{
    return Ticket_Perst_SelByID(id, buf);
}
