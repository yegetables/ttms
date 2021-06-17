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
    
}
