#ifndef PLAY_PERSIST_H_
#define PLAY_PERSIST_H_
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../Common/List.h"
#include "EntityKey_Persist.h"
#include "../Common/Common.h"
//剧目文件名常量"Play.dat"
static const char PLAY_DATA_FILE[] = "Play.dat";

//剧目临时文件名常量"PlayTmp.dat"
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat";

//剧目名常量"Play"
static const char PLAY_KEY_NAME[] = "Play";

//剧目类型定义
typedef enum
{
    PLAY_TYPE_FILE    = 1,
    PLAY_TYPE_OPEAR   = 2,
    PLAY_TYPE_CONCERT = 3
} play_type_t;

//剧目分级定义
typedef enum
{
    PLAY_RATE_CHILD   = 1,
    PLAY_RATE_TEENAGE = 2,
    PLAY_RATE_ADULT   = 3
} play_rating_t;

//剧目实体数据类型定义
typedef struct
{
    int id;                  //剧目ID
    char name[31];           //剧目名称
    play_type_t type;        //剧目类型
    char area[9];            //剧目出品地区
    play_rating_t rating;    //剧目等级
    int duration;            //时长,以分钟为单位
    ttms_date_t start_date;  //开始放映日期
    ttms_date_t end_date;    //结束放映日期
    int price;               //价格
    // char describe[100];  //剧目描述
} play_t;
//剧目链表定义
typedef struct play_node
{
    play_t data;
    struct play_node *next;
    struct play_node *prev;
} play_node_t, *play_list_t;
/**
 * @brief 载入全部剧目
 *
 * @param list list为所有剧目信息的头结点
 * @return int 返回值载入剧目数量
 */
int Play_Perst_SelectAll(play_list_t list);
/**
 * @brief 存储新剧目
 *
 * @param data data指向待存储的剧目信息
 * @return int 返回值==1保存成功!=1保存失败
 */
int Play_Perst_Insert(play_t *data);
/**
 * @brief 更新剧目信息
 *
 * @param data 指向待更新的剧目信息
 * @return int 返回值==1更新成功,!=1更新失败
 */
int Play_Perst_Update(const play_t *data);
/**
 * @brief 根据剧目ID删除剧目信息
 *
 * @param id 剧目id
 * @return int 返回值==1删除成功,!=1删除失败
 */
int Play_Perst_RemByID(int id);
//,
/**
 * @brief 根据剧目ID载入剧目信息
 *
 * @param id 剧目id
 * @param buf buf存储载入的剧目信息
 * @return int 返回值==1载入成功,!=1载入失败,
 */
int Play_Perst_SelectByID(int id, play_t *buf);

/**
 * @brief 根据名称载入数据
 *
 * @param list 储存数据的单链表头指针
 * @param condt 指定的剧目名
 * @return int 符合条件的剧目数量
 */
int Play_Perst_SelectByName(play_list_t list, char condt[]);
#endif