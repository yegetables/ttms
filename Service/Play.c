#include "Play.h"

#include <stdio.h>

#include "../Common/List.h"
#include "../persistence/Play_Persist.h"
//获取全部剧目,返回值:剧目数量
int Play_Srv_FetchAll(play_list_t list) {}

//添加新剧目,返回值==1添加成功,!=1添加失败
int Play_Srv_Add(play_t *data) {}

//修改剧目,返回值==1修改成功,!=1修改失败
int Play_Srv_Modify(const play_t *data) {}

//删除剧目,根据剧目id删除剧目,返回值==1删除成功,!=1删除失败
int Play_Srv_DeleteByID(int id) {}

//获取剧目,根据剧目ID获取剧目信息,返回值==1获取成功,!=1获取失败,buf保存获取剧目的内存地址
int Play_Srv_FetchByID(int id, play_t *buf) {}