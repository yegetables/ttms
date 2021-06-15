#include "Ticket_UI.h"

#include <stdio.h>

#include "../Service/Ticket.h"
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
    Play_Srv_FetchByID(play_id);
//显示剧目名称,演出厅编号,演出日期演出时间

//接受输入,
reshow:
    int witch = -1;
    //选择 生成还是重新生成 还是返回上一层
    scanf("%d", &which);
    switch (which)
    {
        case 2:
            //重新生成票
            Ticket_Srv_DeleteBatch();
        case 1:
            //?生成票?
            Ticket_Srv_GenBatch();
            // 跳转步骤e
            return;
        case 0:
            //返回上一层,步骤e
            return;
        default:
            //提示错误
            break;
    }
    goto reshow;
}
