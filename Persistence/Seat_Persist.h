/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_02
 * File name: Seat.h
 * Description : 设置座位用例持久化层头文件
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#ifndef SEATPERSIST_H_
#define SEATPERSIST_H_
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Common/List.h"
#include "EntityKey_Persist.h"
static const char SEAT_DATA_FILE[]      = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";
//座位状态
typedef enum
{
    SEAT_NONE   = 0,  //空位
    SEAT_GOOD   = 1,  //有座位
    SEAT_BROKEN = 9   //损坏的座位
} seat_status_t;

//座位数据结构
typedef struct
{
    int id;      //座位id
    int roomID;  //所在演出厅id
    int row;     //座位行号
    int column;  //座位列号
    seat_status_t
        status;  //座位在该行的状态，0表示没有座位，1表示有座位。扩展2可表示座位坏了
} seat_t;

//双向链表
typedef struct seat_node
{
    seat_t data;
    struct seat_node *next, *prev;
} seat_node_t, *seat_list_t;
//添加对象主键标识名称
static const char SEAT_KEY_NAME[] = "Seat";

//标识符： TTMS_SCU_Seat_Perst_Insert
//功能：向文件中存储新座位
int Seat_Perst_Insert(seat_t *data);

//标识符：TTMS_SCU_Seat_Perst_InsertBatch
//功能：向文件中批量存储座位
int Seat_Perst_InsertBatch(seat_list_t list);

//标识符：TTMS_SCU_Seat_Perst_Update
//功能：在文件中更新座位
int Seat_Perst_Update(const seat_t *data);

//标识符：TTMS_SCU_Seat_Perst_DelByID
//功能：根据座位ID删除座位
int Seat_Perst_DeleteByID(int ID);

//标识符：TTMS_SCU_Seat_Perst_DelAllByID
//功能：根据演出厅ID删除座位
int Seat_Perst_DeleteAllByRoomID(int roomID);

//标识符：TTMS_SCU_Seat_Perst_SelByRoomID
//功能：根据演出厅ID从文件中载入所有座位
int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID);

//标识符：TTMS_SCU_Studio_Perst_SelByID
//功能：根据ID从文件中载入座位
int Seat_Perst_SelectByID(int ID, seat_t *buf);

//标识符：TTMS_SCU_Seat_Perst_SelAll
//功能：从文件中载入所有座位
int Seat_Perst_SelectAll(seat_list_t list);

#endif /* SEATPERSIST_H_ */
