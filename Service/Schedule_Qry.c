#include"Schedule.h"
#include"Play.h"
#include"../Persistence/Schedule_Persist_Qry.h"
#include<stdio.h>

int Schedule_Srv_FetchAll( schedule_list_t list){
    return Schedule_Perst_SelectAll(list);

}

int Play_Srv_FetchByName(play_list_t list,char condt[]){
    return Play_Perst_SelectByName(list,condt);
}
