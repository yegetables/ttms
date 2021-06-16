#include "Sale.h"

int Sale_Srv_Add(const sale_t* data) { return 0; }

int Ticket_Srv_Modify(const ticket_t* data) { return 0; }

int Ticket_Srv_FetchBySchID(int ID, ticket_list_t list) { return 0; }

ticket_node_t* Ticket_Srv_FetchBySeatID(ticket_list_t list, int seat_id)
{
    return NULL;
}
