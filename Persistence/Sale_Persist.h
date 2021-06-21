#ifndef SALE_PERSIST_H_
#define SALE_PERSIST_H_
#include "../Common/Common.h"
#include "EntityKey_Persist.h"
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
 * @brief 将参数指向的订单信息写入售票文件
 * @param data 售出票信息
 * @return int >=0成功 <0失败
 */
int Sale_Perst_Insert(sale_t* data);

/**
 * @brief 根据售票员ID构建该售票员的记录链表
 * 销售记录即订单信息
 * @param list 存放售票员ID的销售记录
 * @param usrID 售票员ID
 * @return int 匹配ID的销售记录条数,即
 * list节点数量
 */
int Sale_Perst_SelByID(sale_list_t list, int usrID);

/**
 * @brief 根据票id载入销售记录id
 * @param ticket_id 票id
 * @param sale 销售记录
 * @return int 1成功否则失败
 */
int Sale_Perst_SelByTicketID(int ticket_id, sale_t* sale);

#endif
