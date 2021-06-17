#include<stdio.h>

#include"Schedule.h"

#include"./Schedule_Persist.h"

#include "../Common/List.h"

#include "../Service/Ticket.h"
int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id){

    return Schedule_Perst_SelectByPlay(list,play_id);

}

int Schedule_Srv_FetchByID(int id, schedule_t* buf)
{
    return Schedule_Perst_SelectByID(id, buf);
}

int Schedule_Srv_Add(schedule_t *data){

    return Schedule_Perst_Insert(data);


}




int Schedule_Srv_Modify(const schedule_t *data){

    return Schedule_Perst_Update(data);

}



int Schedule_Srv_Delete(int id){

    return Schedule_Perst_RemByID(id);


}
int Schedule_Srv_StatRevByPlay(int play_id,int *soldCount)
{
    int value,sold;
    schedule_list_t list;
    schedule_node_t *p;
    *soldCount = 0;
    List_Init(list,schedule_node_t);
    Schedule_Perst_SelectByPlay(list,play_id);
    List_ForEach(list,p);
    value += Ticket_Srv_StatRevBySchID(p->data.id,&sold);
    *soldCount = *soldCount+sold;
    List_Destroy(list,schedule_node_t);
    return value;
}