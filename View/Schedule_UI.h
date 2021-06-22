#ifndef SCHEDULE_UI_H_
#define SCHEDULE_UI_H_
#include <stdio.h>

#include "../Common/Common.h"
#include "../Common/List.h"
#include "../Common/TimeLegal.h"
#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Schedule_Qry.h"
#include "../Service/Ticket.h"
#include "../View/Seat_UI.h"
#include "Ticket_UI.h"

/**
 * @brief 显示指定ID的剧目相关联的所有演出计划，并提供增删改演出计划的功能
 *
 * @param play_id 指定剧目的ID所对应的所有演出计划
 *
 * @return 返回值 == 1 成功， ！= 1失败
 */
void Schedule_UI_MgtEntry(int play_id);

/**
 * @brief 增加新演出计划
 *
 * @param id 指定演出计划对应的ID
 *
 * @return 返回值 == 1 成功， ！= 1失败
 */
int Schedule_UI_Add(int play_id);

/**
 * @brief 修改演出计划界面
 *
 * @param id 指定演出计划对应的ID
 *
 * @return 返回值 == 1 成功， ！= 1失败
 */
int Schedule_UI_Modify(int id);

/**
 * @brief 删除指定演出计划
 *
 * @param id 指定演出计划对应的ID
 *
 * @return 返回值 == 1 成功， ！= 1失败
 */
int Schedule_UI_Delete(int id);

#endif /* SCHEDULE_UI_MGTENT_H_ */