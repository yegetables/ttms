#include "Sale.h"

int Sale_Srv_Add(sale_t* data) { return Sale_Perst_Insert(data); }

ticket_node_t* Ticket_Srv_FetchBySeatID(ticket_list_t list, int seat_id)
{
    return NULL;
}