#ifndef SALE_H_
#define SALE_H_

#include "../Persistence/Sale_Persist.h"
#include "Play.h"
#include "Schedule.h"
#include "Seat.h"
#include "Ticket.h"
#define SALESANALYSIS_PAGE_SIZE 5
typedef enum
{
    SALE_SELL    = 1,  //买票
    SALE_REFOUND = -1  //退票
} sale_type_t;
typedef struct
{
    long id;           //销售记录id
    int user_id;       //售票员id
    int ticket_id;     //票id
    ttms_date_t date;  //处理日期
    ttms_time_t time;  //处理时间
    int value;         //票价
    sale_type_t type;  //交易类型
} sale_t;

typedef struct sale_node
{
    sale_t data;  //实体数据
    struct sale_node* prev;
    struct sale_node* next;
} sale_node_t, *sale_list_t;

/**
 * @brief 将新的售票订单加入销售记录
 * @param data 售票的订单数据
 * @return int 0成功其他失败
 */
int Sale_Srv_Add(const sale_t* data);

/**
 * @brief 使用data的票信息
 * 修改数据文件中的票信息
 * @param data 新的票信息
 * @return int 0成功其他失败
 */
int Ticket_Srv_Modify(const ticket_t* data);

/**
 * @brief 根据演出计划id获取所有票数据
 * @param ID 演出计划id
 * @param list 记录所有票的链表头指针
 * @return int 获取到的票数量
 */
int Ticket_Srv_FetchBySchID(int ID, ticket_list_t list);

/**
 * @brief 根据座位id获取票数据
 * @param list 指向票链表
 * @param seat_id 座位id
 * @return ticket_node_t* 获取到的票数据
 */
ticket_node_t* Ticket_Srv_FetchBySeatID(ticket_list_t list, int seat_id);

#endif