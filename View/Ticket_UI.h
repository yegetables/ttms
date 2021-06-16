#ifndef TICKET_H
#define TICKET_H
//生成演出票界面
void Ticket_UI_MgtEntry(int schedule_id);
/**
 * @brief 界面层演出票查询管理的入口函数
 * 
 */
void Ticket_UI_Query();
/**
 * @brief 显示演出界面
 *
 * @return 整形，1成功，否则失败
 * 参数：演出票ID号 
 */
int Ticket_UI_ShowTicket(int ticket_id);
#endif