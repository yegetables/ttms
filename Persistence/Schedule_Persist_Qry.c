#include"../Common/List.h"
#include<stdio.h>
#include"../Service/Schedule.h"
#include"../Service/Play.h"

static const char SCHEDULE_DAT_FILE[] = "Schedule.dat";
static const char PLAY_DAT_FILE[] = "play.dat";
int Schedule_Perst_SelectAll(schedule_list_t list){
    schedule_node_t *newNode;
    schedule_t data;
    int recCount = 0;

    assert(NULL != list);

    List_Free(list, studio_node_t);

    FILE *fp = fopen(SCHEDULE_DAT_FILE, "rb");
    if (NULL == fp)
    {  //文件不存在
        return 0;
    }

    while (!feof(fp))
    {
        if (fread(&data, sizeof(schedule_t), 1, fp))
        {
            newNode = (studio_node_t *)malloc(sizeof(studio_node_t));
            if (!newNode)
            {
                printf(
                    "Warning, Memory OverFlow!!!\n Cannot Load more Data into "
                    "memory!!!\n");
                break;
            }
            newNode->data = data;
            List_AddTail(list, newNode);
            recCount++;
        }
    }
    fclose(fp);
    return recCount;


}


int Play_Perst_SelectByName(play_list_t list,char condt[]){
   List_Init(list,play_list_t);
   play_t sch;
   int recCount = 0;
   play_node_t *newNode;
   FILE *fp = fopen(PLAY_DAT_FILE,"rb");
   if(!(fp == NULL)){
      while(!feof(fp)){
          if(fread(&sch,sizeof(play_t),1,fp)){
              if(strcmp(condt,sch.name)){
                  newNode = (schedule_node_t *)malloc(sizeof(schedule_node_t));
                  newNode->data = sch;           
                  List_AddTail(list,newNode);
                  recCount++;
          }
      }
   }
   }else{
       printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
       return 0;
   }
   fclose(fp);
   return recCount; 
    

}