#include "Play_UI.h"

#include <stdio.h>

#include "../Common/List.h"
#include "../Service/Play.h"
//管理剧目界面函数
void Play_UI_MgtEntry() {}
//添加新剧目界面函数,返回值>0添加成功,==0添加失败
int Play_UI_Add() { return 1; }
//修改剧目界面函数,通过剧目id号修改剧目,返回值==1说明修改成功,!=1修改失败
int Play_UI_Modify(int id) { return 1; }
//删除剧目界面函数,通过剧目id号删除剧目,返回值==1删除成功,!=1删除失败
int Play_UI_Delete(int id) { return 1; }
//查询剧目界面函数,查询剧目信息,以列表形式展出,返回值==1查询成功,返回值!=1查询失败
int Play_UI_Query(int id) { return 1; }