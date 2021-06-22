/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : 统计销售额界面层头文件
 * Author:   XUPT
 * Version:  v.1
 */
#include "StaSales.h"

int StaSales_Srv_CompSaleVal(int usrID, ttms_date_t stDate, ttms_date_t endDate)
{
    int amount = 0;
    sale_list_t saleList;
    sale_node_t *pSale;
    List_Init(saleList,sale_node_t);
    Sale_Perst_SelByID(saleList,usrID);
    List_ForEach(saleList,pSale)
    {
        amount += pSale->data.value;
    }
    List_Destroy(saleList,sale_node_t);
    
    return amount;
}