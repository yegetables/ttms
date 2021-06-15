#ifndef TICKET_H
#define TICKET_H
#include "../Service/Ticket.h"
//根据ID载入演出计划
int Schedule_perst_SelectByID(int id, schedule_t* buf);

//存储演出票
void Ticket_perst_Insert(ticket_list_t list);

//根据演出计划ID去除演出票
void Ticket_perst_Rem(int schedule_id);

#endif