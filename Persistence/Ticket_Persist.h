#ifndef TICKET_Persist_H_
#define TICKET_Persist_H_
#include <stdio.h>

#include "../Common/List.h"
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
int Ticket_Perst_SelByID(int id, ticket_t* buf);
/**
 * @brief 用data的票信息更改数据文件的票
 * @param data 新的票信息
 * @return int >=0成功 <0失败
 */
int Ticket_Perst_Update(const ticket_t* data);
/**
 * @brief 根据schedule_id获取票信息的链表
 *
 * @param ticket 票信息头结点
 * @param schedule_id id
 * @return int 返回票的数量
 */
int Ticket_Perst_SelBySchID(ticket_list_t ticket, int schedule_id);

#endif