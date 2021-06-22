/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_01
 * File name: Studio_c
 * Description : 演出厅用例业务逻辑层头文件
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#ifndef STUDIO_H_
#define STUDIO_H_
#include "../Persistence/Studio_Persist.h"


//标识符：TTMS_SCU_Studio_Srv_Add
/**
 * @brief 用于添加一个新演出厅数据。
 * @param data data为studio_t类型指针，是需要添加的演出厅数据结点。
 * @return int 表示是否成功添加了演出厅的标志。
 */
int Studio_Srv_Add(studio_t *data);

//标识符：TTMS_SCU_Studio_ Srv _Mod
/**
 * @brief 用于修改一个演出厅数据。
 * @param datadata为studio_t类型指针，是需要修改的演出厅数据结点。
 * @return int 表示是否成功修改了演出厅的标志。
 */
int Studio_Srv_Modify(const studio_t *data);

//标识符：TTMS_SCU_Studio_Srv_DelByID
/**
 * @brief 用于删除一个演出厅的数据。
 * @param ID id为整型，是需要删除的演出厅ID。
 * @return int 表示是否成功删除了演出厅的标志。
 */
int Studio_Srv_DeleteByID(int ID);

//标识符：TTMS_SCU_Studio_Srv_FetchByID
/**
 * @brief 根据演出厅ID获取一个演出厅的数据。
 * @param ID  是需要获取数据的演出厅ID
 * @param buf studio_t类型指针，指向获取的演出厅数据。
 * @return int 表示是否成功获取了演出厅数据的标志
 */
int Studio_Srv_FetchByID(int ID, studio_t *buf);

//标识符：TTMS_SCU_Studio_Srv_FetchAll
/**
 * @brief 获取所有演出厅的数据，形成以list为头指针的演出厅链表。
 * @param list list是studio_list_t类型指针，指向演出厅链表的头指针。
 * @return int 表示是否成功获取了所有演出厅的标志。
 */
int Studio_Srv_FetchAll(studio_list_t list);

//标识符：TTMS_SCU_Studio_Srv_FindByID
/**
 * @brief 根据演出厅ID和链表头指针获取该链表上相应演出厅的数据
 * @param list studio_list_t类型指针，指向演出厅链表的头指针
 * @param ID 需要获取数据的演出厅ID。
 * @return studio_node_t*指针，表示获取相应ID的演出厅数据。
 */
studio_node_t *Studio_Srv_FindByID(studio_list_t list, int ID);

#endif  // STUDIO_H_
