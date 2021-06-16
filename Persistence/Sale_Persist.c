#include "Sale_Persist.h"

int Sale_Perst_Insert(sale_t* data)
{
    data->id = EntKey_Perst_GetNewKeys("销售记录", 1);
    FILE* fp = fopen("Sale.dat", "ab");
    if (fp == NULL) return -1;
    int ret = fwrite(data, sizeof(sale_t), 1, fp);
    fclose(fp);
    return ret;
}