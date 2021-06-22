#include "Ticket_UI.h"

void Ticket_UI_MgtEntry(int schedule_id)
{
    schedule_t buf1;
    //获取演出计划信息
    if (1 != Schedule_Srv_FetchByID(schedule_id, &buf1))
    {
        printf("error : Schedule_Srv_FetchByID %s %d!\n", __FILE__, __LINE__);
        exit(1);
    }

    //用剧目id作为参数 ,获取剧目信息
    play_t buf2;
    Play_Srv_FetchByID(buf1.play_id, &buf2);
    //显示剧目名称,演出厅编号,演出日期演出时间

    //接受输入,
    int which = -1;
reshow:
    //选择 生成还是重新生成 还是返回上一层
    printf("2:重新生成票；1：生成票；0：返回上一层\n");
    scanf("%d", &which);
    getchar();
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
    ticket_list_t tmp;
    List_Init(tmp, ticket_node_t);
}
int Ticket_UI_ShowTicket(int ticket_id)
{
    ticket_t buf;
    if (Ticket_Srv_FetchByID(ticket_id, &buf) != 1)
    {
        printf("没有这张票");
        return -1;
    }
    printf("查找成功");
    return 1;
}
