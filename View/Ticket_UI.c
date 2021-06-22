#include "Ticket_UI.h"

void Ticket_UI_MgtEntry(int schedule_id)
{
    schedule_t buf;
    //获取演出计划信息
    if (1 != Schedule_Srv_FetchByID(schedule_id, &buf))
    {
        printf("该演出计划不存在!\n按 [Enter] 返回上层!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
    }
    //用剧目id作为参数 ,获取剧目信息
    play_t buf2;
    if(!Play_Srv_FetchByID(buf.play_id, &buf2))
    {
        printf("该剧目不存在!\n按 [Enter] 返回上层!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
    }
    //显示剧目名称,演出厅编号,演出日期演出时间

    //接受输入,
    int which = -1;
reshow:
    //选择 生成还是重新生成 还是返回上一层
    printf("******************************************************************\n");
    printf("[1]生成演出票　　|　　[2]重新生成票 　　|　　 [0]返回上层\n");
    printf("==================================================================\n");
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
    ticket_list_t tmp;
    List_Init(tmp, ticket_node_t);
}
int Ticket_UI_ShowTicket(int ticket_id)
{
    int rtn = 0;
    ticket_t *buf = (ticket_t *)malloc(sizeof(ticket_t));
    if (Ticket_Srv_FetchByID(ticket_id, buf) != 1)
    {
        printf("没有这张票");
        return rtn;
    }
    printf("查找成功");
    rtn = 1;
    return rtn;
}
