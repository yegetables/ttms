#ifndef TICKET_H_
#define TICKET_H_
#include <stdio.h>

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
 * @brief 用data的票信息更改数据文件的票
 * @param data 新的票信息
 * @return int >=0成功 <0失败
 */
int Ticket_Perst_Update(const ticket_t* data);

int Ticket_Perst_SelBySchID(ticket_list_t ticket,int schedule_id);
#endif