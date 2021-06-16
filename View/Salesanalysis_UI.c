/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : TTMS_UC_11
 * Author:   XUPT
 * Version:  v.1
 */
#include "Salesanalysis_UI.h"
#include "../Common/List.h"
#include "../Service/Salesanalysis.h"
void SalesAnalysis_UI_MgtEntry(void)
{
    salesanalysis_list_t head;
    List_Init(head,salesanalysis_node_t);
    
}