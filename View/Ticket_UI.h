#ifndef TICKET_H
#define TICKET_H

//生成演出票界面
void Ticket_UI_MgtEntry(int schedule_id);

/**
 * @brief 使用data的票信息
 * 修改数据文件中的票信息
 * @param data 新的票信息
 * @return int 0成功其他失败
 */
int Ticket_Srv_Modify(const ticket_t* data);

/**
 * @brief 根据演出计划id获取所有票数据
 * @param ID 演出计划id
 * @param list 记录所有票的链表头指针
 * @return int 获取到的票数量
 */
int Ticket_Srv_FetchBySchID(int ID, ticket_list_t list);

/**
 * @brief 根据座位id获取票数据
 * @param list 指向票链表
 * @param seat_id 座位id
 * @return ticket_node_t* 获取到的票数据
 */
ticket_node_t* Ticket_Srv_FetchBySeatID(ticket_list_t list, int seat_id);


#endif