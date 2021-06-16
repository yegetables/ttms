#include"../Service/Schedule.h"
#include"../Service/Play.h"
#ifndef TTMS_SCU_Schedule_Persist_List
#define TTMS_SCU_Schedule_Persist_List
/**
 * @brief 从Schedule.dat种载入所有演出计划，加载到链表list上
 * 
 * @param list 要储存数据的链表
 * @return int 表示载入的演出计划数量
 */
int Schedule_Perst_SelectAll(schedule_list_t list);

/**
 * @brief 根据名称载入数据
 * 
 * @param list 储存数据的单链表头指针
 * @param condt 指定的剧目名
 * @return int 符合条件的剧目数量
 */
int Play_Perst_SelectByName(play_list_t list,char condt[]);

#endif /* TTMS_SCU_Schedule_Persist_List */