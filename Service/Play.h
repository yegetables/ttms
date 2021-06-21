#ifndef PLAY_H_
#define PLAY_H_
#include <stdio.h>
#include <string.h>

#include "../Common/Common.h"
#include "../Common/List.h"
#include "../Persistence/Play_Persist.h"
#include "../Persistence/Seat_Persist.h"

/**
 * @brief 获取全部剧目
 *
 * @param list 存剧目的链表头
 * @return int 返回值:剧目数量
 */
int Play_Srv_FetchAll(play_list_t list);

/**
 * @brief 添加新剧目
 *
 * @param data 新剧目的信息
 * @return int 返回值==1添加成功,!=1添加失败
 */
int Play_Srv_Add(play_t *data);

/**
 * @brief 修改剧目
 *
 * @param data 指向待修改的剧目信息
 * @return int 返回值==1
 */
int Play_Srv_Modify(const play_t *data);

/**
 * @brief 删除剧目
 *
 * @param id 根据剧目id删除剧目
 * @return int 返回值==1删除成功,!=1删除失败
 */
int Play_Srv_DeleteByID(int id);

/**
 * @brief 根据剧目ID获取剧目信息
 *
 * @param id 剧目id
 * @param buf buf保存获取剧目的内存地址
 * @return int 返回值==1获取成功,!=1获取失败
 */
int Play_Srv_FetchByID(int id, play_t *buf);
/**
 * @brief 根据剧目name获取剧目信息
 * @param name 剧目name
 * @param buf buf保存获取剧目的内存地址
 * @return int 返回值==1获取成功,!=1获取失败
 */
int Play_Srv_FetchByName(char *name, play_t *buf);
/**
 * @brief 通过剧目关键字模糊查询剧目
 *
 * @param list 存储含有关键字的剧目链表头指针
 * @param key 剧目名关键字
 * @return int 含有关键字的剧目数量
 */
int Play_Srv_FilterByName(play_list_t list, char *key);
#endif
