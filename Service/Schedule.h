#include"Play.h"
#ifndef SCHEDULE_H_
#define SCHEDULE_H_

typedef struct{
    int hour;
    int minute;
    int second;
}ttms_time_t;
typedef struct 
{
  int id;
  int play_id;
  int studio_id;
  ttms_date_t date;
  ttms_time_t time;
  int seat_count;

}schedule_t;
typedef struct schedule_node
{
   schedule_t data;
   struct 
   
}schedule_node_t,* schedule_list_t;

/**
 * @brief 查找与ID号相关的的演出计划
 * 
 * @param play_id 根据此参数查找相关的演出计划
 * @return 整型，为相关的演出计划的个数
 */
int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id);


/**
 * @brief 调用持久层，增加演出计划
 * 
 * @param data 新增的演出计划数据
 * @return 返回1成功，不为1失败
 */
int Schedule_Srv_Add(schedule_t *data);



/**
 * @brief 调用持久层，修改演出计划
 * 
 * @param data 新的演出计划数据
 * @return 返回1成功，不为1失败
 */
int Schedule_Srv_Modify(const schedule_t *data);


/**
 * @brief 根据id删除指定演出计划
 * 
 * @param id 指定演出计划数据
 * @return 返回1成功，不为1失败
 */
int Schedule_Srv_Delete(int id);
#endif