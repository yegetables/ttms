#ifndef TICKET_H_
#define TICKET_H_
#include "../Common/List.h"
#include "Schedule.h"
#include "Seat.h"
#include "Studio.h"

/**
 * @brief 批量增加Ticket.dat的票信息
 * @param schedule_id 演出计划id
 * @return <0生成失败,>=0表示生成多少票
 */
int Ticket_Srv_GenBatch(int schedule_id);

#endif