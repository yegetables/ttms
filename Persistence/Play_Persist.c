#include "Play_Persist.h"

//载入全部剧目,返回值载入剧目数量,list为所有剧目信息的头结点
int Play_Perst_SelectAll(play_list_t list)
{
    List_Free(list, play_node_t);
    int recCount = 0;
    assert(NULL != list);
    FILE *fp = fopen(PLAY_DATA_FILE, "rb");
    if (NULL == fp)
    {
        return 0;
    }
    play_t data;
    while (!feof(fp))
    {
        if (fread(&data, sizeof(play_t), 1, fp))
        {
            play_node_t *newNode = (play_node_t *)malloc(sizeof(play_node_t));
            if (!newNode)
            {
                printf("Warning,Memory OverFlow!!!\n");
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
//存储新剧目,返回值==1保存成功!=1保存失败,data为待存储的剧目信息
int Play_Perst_Insert(play_t *data)
{
    assert(NULL != data);
    FILE *fp = fopen(PLAY_DATA_FILE, "ab");
    int rtn  = 0;
    if (NULL == fp)
    {
        printf("Cannot open file %s!\n", PLAY_DATA_FILE);
        return 0;
    }
    data->id = EntKey_Perst_GetNewKeys(PLAY_KEY_NAME, 1);  //获取主键
    rtn      = fwrite(data, sizeof(play_t), 1, fp);

    fclose(fp);
    return rtn;
}
//更新剧目信息,返回值==1更新成功,!=1更新失败
int Play_Perst_Update(const play_t *data)
{
    assert(NULL != data);

    FILE *fp = fopen(PLAY_DATA_FILE, "rb+");
    if (NULL == fp)
    {
        printf("Cannot open file %s!\n", PLAY_DATA_FILE);
        return 0;
    }

    play_t buf;
    int found = 0;

    while (!feof(fp))
    {
        if (fread(&buf, sizeof(play_t), 1, fp))
        {
            if (buf.id == data->id)
            {
                fseek(fp, -((int)sizeof(play_t)), SEEK_CUR);
                fwrite(data, sizeof(play_t), 1, fp);
                found = 1;
                break;
            }
        }
    }
    fclose(fp);

    return found;
}
//删除剧目信息,根据剧目ID删除剧目信息,返回值==1删除成功,!=1删除失败
int Play_Perst_RemByID(int id)
{  //对原始数据文件重命名
    if (rename(PLAY_DATA_FILE, PLAY_DATA_TEMP_FILE) < 0)
    {
        printf("Cannot open file %s!\n", PLAY_DATA_FILE);
        return 0;
    }

    FILE *fpSour, *fpTarg;
    fpSour = fopen(PLAY_DATA_TEMP_FILE, "rb");
    if (NULL == fpSour)
    {
        printf("Cannot open file %s!\n", PLAY_DATA_FILE);
        return 0;
    }

    fpTarg = fopen(PLAY_DATA_FILE, "wb");
    if (NULL == fpTarg)
    {
        printf("Cannot open file %s!\n", PLAY_DATA_TEMP_FILE);
        return 0;
    }

    play_t buf;

    int found = 0;
    while (!feof(fpSour))
    {
        if (fread(&buf, sizeof(play_t), 1, fpSour))
        {
            if (id == buf.id)
            {
                found = 1;
                continue;
            }
            fwrite(&buf, sizeof(play_t), 1, fpTarg);
        }
    }

    fclose(fpTarg);
    fclose(fpSour);

    //删除临时文件
    remove(PLAY_DATA_TEMP_FILE);
    return found;
}
//根据剧目ID载入剧目信息,返回值==1载入成功,!=1载入失败,buf存储载入的剧目信息
int Play_Perst_SelectByID(int id, play_t *buf)
{
    assert(NULL != buf);
    int find            = 0;
    play_node_t *curPos = NULL;
    play_list_t headPtr = (play_list_t)malloc(sizeof(play_node_t));
    List_Init(headPtr, play_node_t);
    if (Play_Perst_SelectAll(headPtr) <= 0)
    {
        printf("无剧目信息\n");
        return find;
    }
    List_ForEach(headPtr, curPos)
    {
        if (curPos->data.id == id)
        {
            *buf = curPos->data;
            find   = 1;
            break;
        }
    }
    return find;
}
int Play_Perst_SelectByName(play_list_t list, char condt[])
{
    int recCount = 0;
    play_node_t *curPos;
    play_list_t headPtr = (play_list_t)malloc(sizeof(play_node_t));
    List_Init(headPtr, play_node_t);
    if (Play_Perst_SelectAll(headPtr) <= 0)
    {
        return recCount;
    }
    List_ForEach(headPtr, curPos)
    {
        if (strcmp(condt, curPos->data.name) == 0)
        {
            List_AddTail(list, curPos);
            recCount++;
        }
    }
    return recCount;
}