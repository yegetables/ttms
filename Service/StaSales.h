/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : 统计销售额界面层头文件
 * Author:   XUPT
 * Version:  v.1
 */
#ifndef STASALES_H_
#define STASALES_H_
#include "../Common/Common.h"
#include "../Common/List.h"
#include "../Persistence/Sale_Persist.h"
#include "../Service/Play.h"
#include "../Service/Sale.h"
/**
 * @brief 根据售票员ID统计在给定日期区间的销售额
 * 标识符：TTMS_SCU_StaSales_Srv_CompSaleVal
 * @param usrID
 * @param stDate
 * @param endDate
 * @return int
 */
int StaSales_Srv_CompSaleVal(int usrID, ttms_date_t stDate,
                             ttms_date_t endDate);
#endif /* STASALES_SRV_H_ */