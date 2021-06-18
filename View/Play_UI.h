#ifndef PLAY_UI_H_
#define PLAY_UI_H_
#include <stdio.h>
#include <string.h>

#include "../Common/Common.h"
#include "../Common/List.h"
#include "../Common/TimeLegal.h"
#include "../Service/Play.h"
#include "Schedule_UI.h"
/**
 * @brief 管理剧目界面函数
 *
 */
void Play_UI_MgtEntry();
/**
 * @brief 添加新剧目界面函数
 *
 * @return int 返回值>0添加成功,==0添加失败
 */
int Play_UI_Add();
/**
 * @brief 修改剧目界面函数
 *
 * @param id 剧目id号修改剧目
 * @return int 返回值==1说明修改成功,!=1修改失败
 */
int Play_UI_Modify(int id);
/**
 * @brief 删除剧目界面函数
 *
 * @param id 剧目id
 * @return int 返回值==1删除成功,!=1删除失败
 */
int Play_UI_Delete(int id);
//
/**
 * @brief 查询剧目界面函数,查询剧目信息,以列表形式展出
 *
 * @param id 剧目id
 * @return int 返回值==1查询成功,返回值!=1查询失败
 */
int Play_UI_Query(int id);
#endif