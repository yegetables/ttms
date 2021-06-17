#ifndef TICKET_H_
#define TICKET_H_
#include <stdio.h>

#include "../Service/Ticket.h"
#include "../Service/Schedule.h"
#include "../Common/List.h"
/**
 * @brief 存储演出票
 * 
 * @param list 保存票务信息的链表的头指针
 * 
 * @return 返回值 == 1 成功， ！= 1失败
 */
int Ticket_Perst_Insert(ticket_list_t list);

//根据演出计划ID去除演出票
int Ticket_Perst_Rem(int schedule_id);
/**
 * @brief 根据ID载入演出票
 * 
 * @param id 待查找的演出计划ID
 * @param buf 查找到的演出票的变量地址
 * @return int 返回1表示查找信息成功，否则失败
 */
int Ticket_Perst_SelByID(int id, ticket_t * buf);
/**
 * @brief 用data的票信息更改数据文件的票
 * @param data 新的票信息
 * @return int >=0成功 <0失败
 */
int Ticket_Perst_Update(const ticket_t* data);


#endif