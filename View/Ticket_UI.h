#ifndef TICKET_H
#define TICKET_H
//生成演出票界面
void Ticket_UI_MgtEntry(int schedule_id);
/**
 * @brief 查询演出界面；
 * 
 */
void Schedule_UI_ListALL();

/**
 * @brief：根据剧目名称获取演出计划
 * 功能：显示与参数关联的演出计划的数量
 * return：整型，表示获取到演出计划的数量；
 * *play_name:字符型指针，表示带获取演出计划的剧目名称
 */
int Schedule_UI_Query(char *play_name)

#endif