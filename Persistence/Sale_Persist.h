#ifndef SALE_PERSIST_H_
#define SALE_PERSIST_H_
#include "../Persistence/Sale_Persist.h"
#include "../Service/Sale.h"
#include "../View/Sale_UI.h"
/**
 * @brief 将参数指向的订单信息写入售票文件
 * @param data 售出票信息
 * @return int >=0成功 <0失败
 */
int Sale_Perst_Insert(const sale_t* data);
/**
 * @brief 用data的票信息更改数据文件的票
 * @param data 新的票信息
 * @return int >=0成功 <0失败
 */
int Ticket_perst_Update(const ticket_t* data);
/**
 * @brief 根据演出计划id载入票数据
 * @param id 演出计划id
 * @param list 指向载入的演出票信息
 * @return int载入票数量
 */
int Ticket_Srv_SelBySchID(int id, ticket_list_t list);

#endif
