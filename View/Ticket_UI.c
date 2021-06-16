#include "Ticket_UI.h"
#include "../Service/Schedule.h"
void Ticket_UI_MgtEntry(int schedule_id)
{
    schedule_t *buf = (schedule_t *)malloc(sizeof(schedule_t));
    //获取演出计划信息
    if (1 != Schedule_Srv_FetchByID(schedule_id, buf))
    {
        printf("error : Schedule_Srv_FetchByID %s %d!\n", __FILE__, __LINE__);
        exit(1);
    }
    //用剧目id作为参数 ,获取剧目信息
    // TODO:
    Play_Srv_FetchByID(schedule_id);
//显示剧目名称,演出厅编号,演出日期演出时间

//接受输入,
reshow:
    int which= -1;
    //选择 生成还是重新生成 还是返回上一层
    printf("2:重新生成票；1：生成票；0：返回上一层\n");
    scanf("%d", &which);
    switch (which)
    {
        case 2:
            //重新生成票
            Ticket_Srv_DeleteBatch(schedule_id);
            Ticket_Srv_GenBatch(schedule_id);
        case 1:
            //?生成票?
            Ticket_Srv_GenBatch(schedule_id);
            // 跳转步骤e
            return;
        case 0:
            //返回上一层,步骤e
            return;
        default:
            //提示错误
            printf("重新输入\n");
            break;
    }
    goto reshow;
}
void Ticket_UI_Query()
{
    
}
int Ticket_UI_ShiwTicket(int ticket_id)
{
    int rtn;
    if(Ticket_Srv_FetchByID(ticket_id)!=1)
    {
        printf("没有这张票");
        exit(1);
    }
    printf("查找成功");
    rtn = 1;
    return rtn;
}
