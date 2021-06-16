#ifndef TICKET_H
#define TICKET_H
#include "../Service/Ticket.h"
//根据ID载入演出计划
int Schedule_perst_SelectByID(int id, schedule_t* buf);

//存储演出票
void Ticket_perst_Insert(ticket_list_t list);

//根据演出计划ID去除演出票
void Ticket_perst_Rem(int schedule_id);

/**
 * @brief 用data的票信息更改数据文件的票
 * @param data 新的票信息
 * @return int >=0成功 <0失败
 */
int Ticket_perst_Update(const ticket_t* data);
/**
 * @brief 根据演出计划id载入票数据
 * @param id 演出计划id
 * @param list 指向载入的演出票信息
 * @return int载入票数量
 */
int Ticket_Srv_SelBySchID(int id, ticket_list_t list);

int Ticket_perst_Update(const ticket_t* data);

int Ticket_Srv_SelBySchID(int id, ticket_list_t list);

#endif