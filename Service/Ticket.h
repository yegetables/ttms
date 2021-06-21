#ifndef TICKET_H_
#define TICKET_H_
#include <stdio.h>

#include "../Common/List.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Ticket_Persist.h"
#include "Sale.h"
#include "Schedule.h"
#include "Seat.h"
#include "Studio.h"

/**
 * @brief 批量增加Ticket.dat的票信息
 * @param schedule_id 演出计划id
 * @return <0生成失败,>=0表示生成多少票
 */
int Ticket_Srv_GenBatch(int schedule_id);

/**
 * @brief 根据演出计划id获取所有票数据
 * @param ID 演出计划id
 * @param list 记录所有票的链表头指针
 * @return int 获取到的票数量
 */
int Ticket_Srv_FetchBySchID(int ID, ticket_list_t list);

/**
 * @brief 使用data的票信息
 * 修改数据文件中的票信息
 * @param data 新的票信息
 * @return int 0成功其他失败
 */
int Ticket_Srv_Modify(ticket_t* data);
/**
 * @brief  根据演出计划ID删除演出票
 * @param schedule_id
 */
void Ticket_Srv_DeleteBatch(int schedule_id);

/**
 * @brief 根据座位id获取票数据
 * @param list 指向票链表
 * @param seat_id 座位id
 * @return ticket_node_t* 获取到的票数据
 */
ticket_node_t* Ticket_Srv_FetchBySeatID(ticket_list_t list, int seat_id);

/**
 * @brief 根据演出计划id载入票数据
 * @param schedule_id 演出计划id
 * @param list 指向载入的演出票信息
 * @return int 载入票数量
 */
int Ticket_Srv_SelBySchID(int schedule_id, ticket_list_t list);

int Ticket_Srv_StatRevBySchID(int schedule_id, int* soldCount);

int Ticket_Srv_Update();

/**
 * @brief 根据ID获取演出票
 *
 * @param id 查询的演出票ID
 * @param buf 查询成功的内存地址
 * @return int 1成功，否则失败
 */
int Ticket_Srv_FetchByID(int id, ticket_t* buf);
#endif