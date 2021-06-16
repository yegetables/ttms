#ifndef TICKET_H
#define TICKET_H
//票状态
typedef enum
{
    TICKET_AVL  = 0,  //待售
    TICKET_SOLD = 1,  //已售
    TICKET_RESV = 9   //预留
} ticket_status_t;

//票实体数据类型
typedef struct
{
    int id;                  //票id
    int schedule_id;         //演出计划id
    int seat_id;             //座位id
    int price;               //票价
    ticket_status_t status;  //票状态
} ticket_t;

//票链表节点
typedef struct ticket_node
{
    ticket_t data;
    struct ticket_node *next, *prev;
} ticket_node_t, *ticket_list_t;
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