#include "Sale_Persist.h"

int Sale_Perst_Insert(sale_t* data)
{
    data->id = EntKey_Perst_GetNewKeys("销售记录", 1);
    FILE *fp = fopen("Sale.dat", "ab");
    if (fp == NULL || data == NULL) return -1;
    int ret = fwrite(data, sizeof(sale_t), 1, fp);
    fclose(fp);
    return ret;
}
int Sale_Perst_SelByID(sale_list_t list, int usrID)
{
    int rtn = 0;
    List_Init(list, sale_node_t);
    sale_t data;

    FILE* fp = fopen("Sale.dat", "rb");
    if (fp == NULL) return 0;
    while (!feof(fp))
    {
        fread(&data, sizeof(sale_t), 1, fp);
        if (usrID == data.user_id)
        {
            sale_list_t node = (sale_node_t*)malloc(sizeof(sale_node_t));
            node->data       = data;
            node->prev = node->next = node;
            List_AddTail(list, node);
            rtn += 1;
        }
    }
    fclose(fp);
    return rtn;
}

int Sale_Perst_SelByTicketID(int ticket_id, sale_t* sale)
{
    assert(NULL != sale);
    FILE* fp = fopen("Sale.dat", "rb");
    if (NULL == fp)
    {
        return 0;
    }

    sale_t data;
    int found = 0;
    while (!feof(fp))
    {
        if (fread(&data, sizeof(sale_t), 1, fp))
        {
            if (ticket_id == data.id)
            {
                *sale = data;
                found = 1;
                break;
            }
        }
    }
    fclose(fp);
    return found;
}
