#ifndef SCHEDULE_H_
#define SCHEDULE_H_

typedef struct
{
    int a;
    //随便写的,自己改内容
} schedule_t;

/**
 * @brief 根据id获取演出计划
 * @param id 演出计划id
 * @param buf 保存到buf
 * @return int 1成功非1失败
 */
int Schedule_Srv_FetchByID(int id, schedule_t* buf);
#endif