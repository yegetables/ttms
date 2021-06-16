#include<stdio.h>

#include"Schedule_Persist.h"
#include"../Common/List.h"
#include"Schedule.h"

int Schedule_Perst_SelectByPlay(schedule_list_t list,int play_id){}
int Schedule_Perst_Insert(schedule_t *data){}
int Schedule_Perst_Update(const schedule_t *data){}
int Schedule_Perst_RemByID(){}
int Schedule_Perst_SelectByID(int id, schedule_t * buf)
{
    int found= 0;
    
    FILE *fp=NULL;
    fp=fopen("Schedule.dat", "r")
    ;
    if(fp==NULL)
    {
        printf("打开失败");
        fclose(fp);
        return found;
    }
    while(!feof(fp))
    {
        
    }
}
