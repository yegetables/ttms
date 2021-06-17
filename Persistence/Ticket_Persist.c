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

int Ticket_Srv_SelBySchID(int schedule_id, ticket_list_t list)
{
    List_Init(list, ticket_list_t)
    ticket_t data;
    int rtn  = 0;
    FILE* fp = fopen("Ticket.dat", "r");
    if (fp == NULL)
    {
        printf("file open fiaied\n");
        return -1;
    }
    while (!feof(fp))
    {
        fread(&data, sizeof(ticket_t), 1, fp);
        if (schedule_id == data.schedule_id)
        {
            ticket_list_t  tmp = (ticket_list_t)malloc(sizeof(ticket_list_t));
            tmp->data         = data;
            tmp->prev = tmp->next = tmp;
            List_AddTail(list, tmp);
            rtn += 1;
        }
    }
    fclose(fp);
    return rtn;
}
int Schedule_Perst_SelectByID(int id,schedule_t *buf)
{
        int found = 0;
        FILE *fp = fopen("Schedule.dat", "r");
        if(feof(fp))
        {
            fclose(fp);
            return found;
        }
        else{
            schedule_t data;
            while(feof(fp))
            {
                int x=fread(&data, sizeof(data), 1, fp);
                if(x==0)
                {
                    fclose(fp);
                    return found;
                }
                else{
                    if(data.id==id)
                    {
                        found=1;
                        buf=&data;
                    }
                }
            }
            fclose(fp);
            return found;
        }
}
int Ticket_Perst_Insert(ticket_list_t list)
{
    FILE *fp=fopen("Ticket.dat", "a");
    if(fp==NULL)
    {
        printf("打开失败");
        return 0;
    }
    
}