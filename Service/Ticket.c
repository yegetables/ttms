#include "Ticket.h"
#include "../Service/Sale.h"

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

Ticket_Srv_Update();

int Ticket_Srv_SelBySchID(int schedule_id, ticket_list_t list)
{
    List_Init(list, *ticket_list_t);
    ticket_t data;
    int rtn  = 0;
    FILE* fp = fopen("Ticket.dat", "r");
    if (fp == NULL)
    {
        printf("file open fiaied\n");
        return -1;
    }
    while (!feof(fp))
    {
        fread(&data, sizeof(ticket_t), 1, fp);
        if (schedule_id == data.schedule_id)
        {
            ticket_list_t tmp = (ticket_list_t)malloc(sizeof(ticket_list_t));
            tmp->data         = data;
            tmp->prev = tmp->next = tmp;
            List_AddTail(list, tmp);
            rtn += 1;
        }
    }
    fclose(fp);
    return rtn;
}

ticket_node_t* Ticket_Srv_FetchBySeatID(ticket_list_t list, int seat_id)
{
    ticket_list_t temp = NULL;
    List_ForEach(list, temp)
    {
        if (temp->data.seat_id == seat_id) return temp;
    }
    if (temp == list) return NULL;
}
int Ticket_Srv_FetchBySchID(int ID, ticket_list_t list)
{
    return Ticket_Srv_SelBySchID(ID, list);
}
int Ticket_Srv_Modify(ticket_t* data) { return Ticket_Perst_Update(data); }

int Ticket_Srv_StatRevBySchID(int schedule_id,int *soldCount)
{
    int value;
    ticket_list_t list;
    ticket_node_t *p;
    sale_node_t  *sale;
    List_Init(list,ticket_node_t);
    *soldCount = 0;
    *soldCount = Ticket_Srv_FetchBySchID(list,schedule_id);
    List_ForEach(list,p);
    Sale_Srv_FetchByTicketID(schedule_id,sale);
    if(sale->data.type == 1)
    {
        if(p->data.status == 1)
        {
            (*soldCount)++;
            value += p->data.price;
        }
    }
    List_Destroy(list,ticket_node_t);
    return value;
}
