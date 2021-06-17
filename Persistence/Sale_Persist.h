#ifndef SALE_PERSIST_H_
#define SALE_PERSIST_H_
#include <unistd.h>

#include "../Persistence/Sale_Persist.h"
#include "../Service/Sale.h"
#include "../View/Sale_UI.h"
#include "EntityKey_Persist.h"
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
#endif
