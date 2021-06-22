#ifndef TTMS_SCU_Schedule_UI_List
#define TTMS_SCU_Schedule_UI_List
#include <stdio.h>

#include "../Common/List.h"
#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Schedule_Qry.h"
#include "../Service/Studio.h"
/**
 * @brief 以列表形式显示所有的演出计划信息，
 * 列表上方显示表头信息，
 *表头下方显示与所有演出计划中第一页的信息，
 * 列表下方显示查询功能选项
 */
void Schedule_UI_ListAll(void);

/**
 * @brief 根据剧目名称获取演出计划
 * @param int 获取到的演出计划的数量
 *
 */
int Schedule_UI_Query(char *play_name);

#endif /* TTMS_SCU_Schedule_UI_List */