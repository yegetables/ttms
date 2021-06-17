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

int Ticket_Srv_StatRevBySchID(int schedule_id,int *soldCount);

Ticket_Srv_Update();

#endif