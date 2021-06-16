#include<stdio.h>

#include"Schedule_UI.h"

#include"../Service/Schedule.h"


#include "../Common/List.h"

void Schedule_UI_MgtEntry(int play_id){




}

int Schedule_UI_Add(int play_id){
    int newCount = 0;
    char choice;
    schedule_t sch;
    do{
        printf("\n=======================================================\n");
        printf("****************  Add New Schedule  ****************\n");
        printf("-------------------------------------------------------\n");
        printf("Schedule id:");
        fflush(stdin);
        scanf("%d",&(sch.id));
        printf("Schedule play_id:");
        scanf("%d",&(sch.play_id));
        printf("Schedule studio_id:");
        scanf("%d",&(sch.studio_id));
        printf("Schedule time\n");
        printf("hour:");
        scanf("%d",&(sch.time.hour));
        printf("minute:");
        scanf("%d",&(sch.time.second));
        printf("Schedule seat_count:");
        scanf("%d",&(sch.seat_count));
         printf("=======================================================\n");
         
         if(Schedule_Srv_Add()){
             newCount+=1;
             printf("The new Schedule added successfully!");
         }else{
             printf("The new Schedule added failed!");
         }
         printf("-------------------------------------------------------\n");
        printf("[A]dd more, [R]eturn:");
        fflush(stdin);
        scanf("%c",&choice);
    }while('a' == choice || 'A' == choice);

    return  newCount;
   
}



int Schedule_UI_Modify(int id){
    int rtn = 0;
    schedule_t sch;



}



int Schedule_UI_Delete(int id){




}
