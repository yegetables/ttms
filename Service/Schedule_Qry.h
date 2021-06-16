#include"Schedule.h"
#include"Play.h"
#ifndef TTMS_SCU_Schedule_UI_List
#define TTMS_SCU_Schedule_UI_List
/**
 * @brief 将界面层建立的演出计划链表的头指针传递给持久化层函数，
 * 并将持久化层函数返回的含有所有演出计划信息的链表的头指针返回给界面层函数
 * @return int 表示获取到的演出计划数量
 */
int Schedule_Srv_FetchAll( schedule_list_t list);


 /* @brief 根据名称获取剧目
 * 
 * @param list 表示保存结果的单链表头指针
 * @param condt 表示要查询的剧目名称
 * @return int 表示获取到的剧目信息数量
 */
int Play_Srv_FetchByName(play_list_t list,char condt[]);
#endif /* TTMS_SCU_Schedule_UI_List */