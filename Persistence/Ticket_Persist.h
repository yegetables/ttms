#ifndef TICKET_H
#define TICKET_H
#include "../Service/Ticket.h"
/**
 * @brief ：根据ID载入演出计划
 * 
 * @param id:待载入的演出计划的ID 
 * @param buf ：演出计划的地址
 * @return int ：返回1代表演出成功，负责代表演出失败；
 */
int Schedule_Perst_SelectByID(int id, schedule_t * buf);

//存储演出票
void Ticket_Perst_Insert(ticket_list_t list);

//根据演出计划ID去除演出票
void Ticket_Perst_Rem(int schedule_id);
/**
 * @brief 根据ID载入演出票
 * 
 * @param id ：待查找的演出计划
 * @param buf ：查找到的演出票的变量地址
 * @return int ：1成功，非1失败；
 */
int Ticket_Perst_SelByID(int id, ticket_t * buf);
#endif