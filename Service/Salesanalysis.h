/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : TTMS_UC_11
 * Author:   XUPT
 * Version:  v.1
 */

#ifndef SALESANALYSIS_t
#define SALESANALYSIS_t

#include "../Common/List.h"
#include "../Service/Play.h"
/**
 * @brief 函数实现了构建salesanalysis_list_t类型链表功能
 *  标识符：TTMS_SCU_SalesAnalysis_Srv_StaticSale
 */
typedef struct
{
    int play_id;             //剧目编号
    char name[31];           //剧目名称
    char area[9];            //剧目区域
    int duration;            //剧目播放时长
    long totaltickets;       //剧目上座数量
    long sales;              //剧目票房（销售额统计）
    int price;               //剧目票价
    ttms_date_t start_date;  //剧目上映日期
    ttms_date_t end_date;    //剧目下映日期
} salesanalysis_t;

typedef struct salesanalysis_node
{
    salesanalysis_t data;             //实体数据
    struct salesanalysis_node *next;  //后向指针
    struct salesanalysis_node *prev;  //前向指针
} salesanalysis_node_t, *salesanalysis_list_t;

int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list);
#endif /* salesanalysis_t */