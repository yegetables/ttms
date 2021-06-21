#ifndef SALE_H_
#define SALE_H_

#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Seat_Persist.h"
#include "Play.h"
#include "Schedule.h"
#include "Seat.h"

#define SALESANALYSIS_PAGE_SIZE 5

/**
 * @brief 将新的售票订单加入销售记录
 * @param data 售票的订单数据
 * @return int 0成功其他失败
 */
int Sale_Srv_Add(sale_t* data);
#define Sale_Srv_insert Sale_Srv_Add
// Sale_Srv_insert();

#endif