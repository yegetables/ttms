#ifndef TICKET_H_
#define TICKET_H_
#include "../Common/List.h"
#include "../View/Ticket_UI.h"
#include "Schedule.h"
#include "Seat.h"
#include "Studio.h"
//票状态
typedef enum
{
    TICKET_AVL  = 0,  //待售
    TICKET_SOLD = 1,  //已售
    TICKET_RESV = 9   //预留
} ticket_status_t;

//票实体数据类型
typedef struct
{
    int id;                  //票id
    int schedule_id;         //演出计划id
    int seat_id;             //座位id
    int price;               //票价
    ticket_status_t status;  //票状态
} ticket_t;

//票链表节点
typedef struct ticket_node
{
    ticket_t data;
    struct ticket_node *next, *prev;
} ticket_node_t, *ticket_list_t;

/**
 * @brief 批量增加Ticket.dat的票信息
 * @param schedule_id 演出计划id
 * @return <0生成失败,>=0表示生成多少票
 */
int Ticket_Srv_GenBatch(int schedule_id);

/**
 * @brief 根据ID获取演出计划
 * @param id
 * @param buf
 * @return int
 */
int Schedule_Srv_FetchByID(int id, schedule_t* buf);

/**
 * @brief  根据演出计划ID删除演出票
 * @param schedule_id
 */
void Ticket_Srv_DeleteBatch(int schedule_id);
#endif