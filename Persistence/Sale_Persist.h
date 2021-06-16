#ifndef SALE_PERSIST_H_
#define SALE_PERSIST_H_
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

#endif
