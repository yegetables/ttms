#ifndef PLAY_PERSIST_H
#define PLAY_PERSIST_H

#include "../Service/Play.h"
//载入全部剧目,返回值载入剧目数量,list为所有剧目信息的头结点
int Play_Perst_SelectAll(play_list_t list);
//存储新剧目,返回值==1保存成功!=1保存失败,data为待存储的剧目信息
int Play_Perst_Insert(play_t *data);
//更新剧目信息,返回值==1更新成功,!=1更新失败
int Play_Perst_Update(const play_t *data);
//删除剧目信息,根据剧目ID删除剧目信息,返回值==1删除成功,!=1删除失败
int Play_Perst_RemByID(int id);
//根据剧目ID载入剧目信息,返回值==1载入成功,!=1载入失败,buf存储载入的剧目信息
int Play_Perst_SelectByID(int id, play_t *buf);
#endif