#ifndef TICKET_UI_H
#define TICKET_UI_H
#include <stdio.h>

#include "../Service/Play.h"
#include "../Service/Ticket.h"
/**
 * @brief 生成演出票界面
 *
 * @param schedule_id 余票相关的演出计划ID
 */
void Ticket_UI_MgtEntry(int schedule_id);
/**
 * @brief :界面层演出票查询的入口函数；
 *
 */
void Ticket_UI_Query();
/**
 * @brief 显示演出票界面
 *
 * @param ticket_id 查询的演出票ID
 * @return int 1：成功 否则失败；
 */
int Ticket_UI_ShowTicket(int ticket_id);

#endif