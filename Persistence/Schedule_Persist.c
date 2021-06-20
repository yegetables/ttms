#include "Schedule_Persist.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Common/List.h"
static const char SCHEDULE_DATA_FILE[]      = "Schedule.dat";
static const char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat";
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id)
{
    List_Init(list, schedule_node_t);
    schedule_t sch;
    int recCount = 0;
    schedule_node_t *newNode;
    FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
    if (!(fp == NULL))
    {
        while (!feof(fp))
        {
            if (fread(&sch, sizeof(schedule_t), 1, fp))
            {
                if (sch.play_id == play_id)
                {
                    newNode =
                        (schedule_node_t *)malloc(sizeof(schedule_node_t));
                    newNode->data = sch;
                    List_AddTail(list, newNode);
                    recCount++;
                }
            }
        }
    }
    else
    {
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }
    fclose(fp);
    return recCount;
}

int Schedule_Perst_Insert(schedule_t *data)
{
    FILE *fp = fopen(SCHEDULE_DATA_FILE, "ab");
    int rtn  = 0;
    if (!(fp == NULL))
    {
        rtn = fwrite(data, sizeof(schedule_t), 1, fp);
        fclose(fp);
        return rtn;
    }
    else
    {
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }
}

int Schedule_Perst_SelectByID(int id, schedule_t *buf)
{
    int found = 0;
    FILE *fp  = fopen("Schedule.dat", "r");
    if (feof(fp))
    {
        fclose(fp);
        return found;
    }
    else
    {
        schedule_t data;
        while (feof(fp))
        {
            int x = fread(&data, sizeof(data), 1, fp);
            if (x == 0)
            {
                fclose(fp);
                return found;
            }
            else
            {
                if (data.id == id)
                {
                    found = 1;
                    buf   = &data;
                }
            }
        }
        fclose(fp);
        return found;
    }
}

int Schedule_Perst_Update(const schedule_t *data)
{
    int found = 0;
    schedule_t buf;
    FILE *fp = fopen(SCHEDULE_DATA_FILE, "wb+");
    if (!(fp == NULL))
    {
        while (!feof(fp))
        {
            if (fread(&buf, sizeof(schedule_t), 1, fp))
            {
                if (buf.id == data->id)
                {
                    fseek(fp, -((int)sizeof(schedule_t)), SEEK_CUR);
                    fwrite(data, sizeof(schedule_t), 1, fp);
                    found = 1;
                    break;
                }
            }
        }
    }
    else
    {
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }
    fclose(fp);

    return found;
}

int Schedule_Perst_RemByID(int id)
{
    int found = 0;
    if (rename(SCHEDULE_DATA_FILE, SCHEDULE_DATA_TEMP_FILE) < 0)
    {
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }

    FILE *fpSour, *fpTarg;
    fpSour = fopen(SCHEDULE_DATA_TEMP_FILE, "rb");
    if (fpSour == NULL)
    {
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }

    fpTarg = fopen(SCHEDULE_DATA_FILE, "wb");
    if (fpTarg == NULL)
    {
        printf("Cannot open file %s!\n", SCHEDULE_DATA_TEMP_FILE);
        return 0;
    }

    schedule_t buf;
    while (!feof(fpSour))
    {
        if (fread(&buf, sizeof(schedule_t), 1, fpSour))
        {
            if (id == buf.id)
            {
                found = 1;
                continue;
            }
            fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
        }
    }

    fclose(fpTarg);
    fclose(fpSour);

    remove(SCHEDULE_DATA_TEMP_FILE);
    return found;
}