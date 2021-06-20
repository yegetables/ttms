#ifndef SALE_H_
#define SALE_H_

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
int Sale_Srv_Add(sale_t* data);
#define Sale_Srv_insert Sale_Srv_Add
// Sale_Srv_insert();

#endif