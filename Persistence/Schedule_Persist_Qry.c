#include "Schedule_Persist_Qry.h"

static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";
int Schedule_Perst_SelectAll(schedule_list_t list)
{
    schedule_node_t *newNode;
    schedule_t data;
    int recCount = 0;

    assert(NULL != list);

    List_Free(list, schedule_node_t);

    FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
    if (NULL == fp)
    {  //文件不存在
        printf("文件打开失败%s\n", SCHEDULE_DATA_FILE);
        return 0;
    }
    while (!feof(fp))
    {
        if (fread(&data, sizeof(schedule_t), 1, fp))
        {
            newNode = (schedule_node_t *)malloc(sizeof(schedule_node_t));
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
int Schedule_Perst_SelectByID(int id, schedule_t *buf)
{
    int found = 0;
    FILE *fp  = fopen("Schedule.dat", "rb");
    if (fp == NULL)
    {
        printf("fail to open file\n");
        return -1;
    }
    if (feof(fp))
    {
        fclose(fp);
        return found;
    }
    else
    {
        schedule_t data;
        while (!feof(fp))
        {
            int x = fread(&data, sizeof(data), 1, fp);

            if (data.id == id)
            {
                found = 1;
                *buf  = data;
                break;
            }
        }
        fclose(fp);
        return found;
    }
}
