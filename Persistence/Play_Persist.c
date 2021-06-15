#include "Play_Persist.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Common/List.h"
#include "../Service/Play.h"
#include "EntityKey_Persist.h"
//剧目文件名常量"Play.dat"
static const char PLAY_DATA_FILE[] = "Play.dat";

//剧目临时文件名常量"PlayTmp.dat"
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat";

//剧目名常量"Play"
static const char PLAY_KEY_NAME[] = "Play";
//载入全部剧目,返回值载入剧目数量,list为所有剧目信息的头结点
int Play_Perst_SelectAll(play_list_t list) { return 1; }
//存储新剧目,返回值==1保存成功!=1保存失败,data为待存储的剧目信息
int Play_Perst_Insert(play_t *data) { return 1; }
//更新剧目信息,返回值==1更新成功,!=1更新失败
int Play_Perst_Update(const play_t *data) { return 1; }
//删除剧目信息,根据剧目ID删除剧目信息,返回值==1删除成功,!=1删除失败
int Play_Perst_RemByID(int id) { return 1; }
//根据剧目ID载入剧目信息,返回值==1载入成功,!=1载入失败,buf存储载入的剧目信息
int Play_Perst_SelectByID(int id, play_t *buf) { return 1; }