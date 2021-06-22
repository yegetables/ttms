#ifndef SCHEDULE_PERSIST_QRY_H_
#define SCHEDULE_PERSIST_QRY_H_
#include"Schedule_Persist.h"
#include"../Common/List.h"
#include<stdio.h>
/**
 * @brief 从Schedule.dat种载入所有演出计划，加载到链表list上
 * 
 * @param list 要储存数据的链表
 * @return int 表示载入的演出计划数量
 */
int Schedule_Perst_SelectAll(schedule_list_t list);

/**
 * @brief ：根据ID载入演出计划
 * 
 * @param id:待载入的演出计划的ID 
 * @param buf ：演出计划的地址
 * @return int ：返回1代表演出成功，否则代表演出失败；
 */
int Schedule_Perst_SelectByID(int id, schedule_t * buf);

#endif /* TTMS_SCU_Schedule_Persist_List */