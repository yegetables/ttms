#include "Ticket_Persist.h"
#include "stdio.h"

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