#ifndef TICKET_H
#define TICKET_H
//票状态
typedef enum {
    TICKET_AVL=0,   //待售
    TICKET_SOLD=1, //已售
    TICKET_RESV=9 //预留
}ticket_status_t;

//票实体数据类型
typedef struct{
    int id;     //票id
    int schedule_id;    //演出计划id
    int seat_id;    //座位id
    int price;      //票价
    ticket_status_t status;     //票状态
}ticket_t;

//票链表节点
typedef struct ticket_node {
        ticket_t data;
        struct ticket_node *next, *prev;
}ticket_node_t,*ticket_list_t;
//生成演出票界面
void Ticket_UI_MgtEntry(int schedule_id){

}

#endif