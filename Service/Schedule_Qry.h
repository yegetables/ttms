#ifndef TTMS_SCU_Schedule_UI_List
#define TTMS_SCU_Schedule_UI_List
#include "Play.h"
#include"../Persistence/Schedule_Persist.h"

/**
 * @brief 将界面层建立的演出计划链表的头指针传递给持久化层函数，
 * 并将持久化层函数返回的含有所有演出计划信息的链表的头指针返回给界面层函数
 * @return int 表示获取到的演出计划数量
 */

int Schedule_Srv_FetchAll(schedule_list_t list);

#endif /* TTMS_SCU_Schedule_UI_List */