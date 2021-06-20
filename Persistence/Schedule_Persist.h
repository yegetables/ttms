#ifndef SCHEDULE_PERSIST_H_
#define SCHEDULE_PERSIST_H_
#include"../Service/Schedule.h"
#include"../Service/Schedule.h"
//功能：从演出计划数据文件中载入与指定剧目关联的演出计划信息，构成链表list
int Schedule_Perst_SelectByPlay(schedule_list_t list,int play_id);

//功能：向演出计划文件Schedule.dat得末尾存储一条新的演出计划信息
int Schedule_Perst_Insert(schedule_t *data);


//功能：更新演出计划文件Schedule.dat中一条演出计划信息
int Schedule_Perst_Update(const schedule_t *data);

//功能：去除数据文件Schedule.dat中指定ID的演出计划信息
int Schedule_Perst_RemByID(int id);




#endif /* SCHEDULE_Persist_H */
