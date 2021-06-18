#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include <stdio.h>

#include "../Common/List.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Service/Ticket.h"
#include "Play.h"
typedef struct
{
    int hour;
    int minute;
    int second;
} ttms_time_t;

typedef struct
{
    int id;            //演出计划id
    int play_id;       //剧目ID
    int studio_id;     //演出厅ID
    ttms_date_t date;  //日期
    ttms_time_t time;  //演出时间
    int seat_count;    //座位数

} schedule_t;
typedef struct schedule_node
{
    schedule_t data;
    struct schedule_node *next;
    struct schedule_node *prev;
} schedule_node_t, *schedule_list_t;

/**
 * @brief 查找与ID号相关的的演出计划
 *
 * @param play_id 根据此参数查找相关的演出计划
 * @return 整型，为相关的演出计划的个数
 */
int Schedule_Srv_FetchByPlay(schedule_list_t list, int play_id);

/**
 * @brief 调用持久层，增加演出计划
 *
 * @param data 新增的演出计划数据
 * @return 返回1成功，不为1失败
 */
int Schedule_Srv_Add(schedule_t *data);

/**
 * @brief 调用持久层，修改演出计划
 * @param data 新的演出计划数据
 * @return 返回1成功，不为1失败
 */
int Schedule_Srv_Modify(const schedule_t *data);

/**
 * @brief 根据ID获取演出计划
 * @param id
 * @param buf
 * @return int
 */
int Schedule_Srv_FetchByID(int id, schedule_t *buf);
/**
 * @brief 根据id删除指定演出计划
 *
 * @param id 指定演出计划数据
 * @return 返回1成功，不为1失败
 */
int Schedule_Srv_Delete(int id);

int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount);
#endif