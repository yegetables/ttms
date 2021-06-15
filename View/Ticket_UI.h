#ifndef TICKET_UI_H_
#define TICKET_UI_H_
#include "../Service/Ticket.h"
/**
 * @brief 根据演出计划id显示计划信息,提供生成演出票和重新生成票入口
 * @param schedule_id 演出计划id
 */
void Ticket_UI_MgtEntry(int schedule_id);
#define SALESANALYSIS_PAGE_SIZE 5

void Ticket_Srv_DeleteBatch(int schedule_id);

//查询
void Queries_Menu(void);

//售票管理界面
void Sale_UI_MgtEntry(void);

/**
 * @brief 生成演出票
 * 在文件Play.dat中载入特定ID的剧目信息到buf中
 * @param id 剧目ID
 * @param buf play_t指针,表示载入剧目信息的地址
 * @return int
 */
int Play_Perst_SelectByID(int id, play_t *buf);

#endif