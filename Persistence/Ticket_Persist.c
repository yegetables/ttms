#include "Ticket_Persist.h"

#include "stdio.h"

int Ticket_Perst_Update(const ticket_t* data)
{
    ticket_t ret;
    int rtn  = -1;
    FILE* fp = fopen("Ticket.dat", "rb+");
    if (fp == NULL || data == NULL)
    {
        printf("file open fiaied or data is NULL\n");
        return -1;
    }
    while (!feof(fp))
    {
        fread(&ret, sizeof(ticket_t), 1, fp);
        if (ret.id == data->id)
        {
            fwrite(data, sizeof(studio_t), 1, fp);
            rtn = 1;
        }
    }
    fclose(fp);
    return rtn;
}


int Ticket_Perst_Insert(ticket_list_t list)
{
    FILE *fp=fopen("Ticket.dat", "a");
    if(fp==NULL)
    {
        printf("打开失败");
        return 0;
    }
    Schedule_Perst_SelectByID()
}
//----------------------------------------------------------------
int Ticket_Perst_Rem(int schedule_id)
{
    int found=0;
    if(rename("Ticket.dat", "TicketTmp.dat")==-1)
    {
        printf("改名失败");
        return ;
    }
    FILE *fp=fopen("TicketTmp.dat", "r");
    FILE *fp2=fopen("Ticket.dat", "w");
    if(fp&&fp2){
        return found;
    }
    while(feof(fp))
    {
        ticket_t buf;
        fread(&buf,sizeof(ticket_t),1,fp);
        if(buf.schedule_id==schedule_id)
        {
            found++;
        }
        else{
        fwrite(&buf,sizeof(ticket_t),1,fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    rename("TicketTmp.dat", "Ticket.dat");
    return found;
}
