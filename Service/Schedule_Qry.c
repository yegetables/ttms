#include"Schedule.h"
#include"Play.h"
#include"../Common/List.h"
#include"../Persistence/Schedule_Persist_Qry.h"
#include<stdio.h>

int Schedule_Srv_FetchAll( schedule_list_t list){
    schedule_list_t list_s;
    List_Init(list_s,schedule_node_t);
    play_list_t list_p;
    List_Init(list_p,play_node_t);
    return Schedule_Perst_SelectAll(list);

}

int Play_Srv_FetchByName(play_list_t list,char condt[]){
    return Play_Perst_SelectByName(list,condt);
}
