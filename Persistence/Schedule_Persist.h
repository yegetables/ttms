#ifndef SCHEDULE_PERSIST_H_
#define SCHEDULE_PERSIST_H_
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Common/Common.h"
#include "../Common/List.h"
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
//功能：从演出计划数据文件中载入与指定剧目关联的演出计划信息，构成链表list
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id);

//功能：向演出计划文件Schedule.dat得末尾存储一条新的演出计划信息
int Schedule_Perst_Insert(schedule_t *data);

//功能：更新演出计划文件Schedule.dat中一条演出计划信息
int Schedule_Perst_Update(const schedule_t *data);

//功能：去除数据文件Schedule.dat中指定ID的演出计划信息
int Schedule_Perst_RemByID(int id);

#endif /* SCHEDULE_Persist_H */
