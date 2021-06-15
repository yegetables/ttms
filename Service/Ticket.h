#ifndef TICKET_H_
#define TICKET_H_
#include "../Common/List.h"
#include "Schedule.h"
#include "Seat.h"
#include "Studio.h"
#include "../View/Ticket_UI.h"

/**
 * @brief 批量增加Ticket.dat的票信息
 * @param schedule_id 演出计划id
 * @return <0生成失败,>=0表示生成多少票
 */
int Ticket_Srv_GenBatch(int schedule_id);


//根据ID获取演出计划
int Schedule_Srv_FetchByID(int id, schedule_t * buf);


//根据演出计划ID删除演出票
void Ticket_Srv_DeleteBatch(int schedule_id);

typedef struct
{
} ticket_t;
typedef enum
{

} ticket_status_t;
typedef struct ticket_node
{
} ticket_node_t, *ticket_list_t;


#endif