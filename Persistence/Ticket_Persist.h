#ifndef TICKET_H
#define TICKET_H
#include "../View/Ticket.h"
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
 * @brief:载入全部演出计划
 * return：整型，载入的演出计划数量
 * 参数：表示记录所有演出计划的链表头指针 
 * 
 */
int Schedule_Perst_SelectByAll(schedule_list_t list)

#endif