/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_02
 * File name: Seat.h
 * Description : 设置座位用例业务逻辑层头文件
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#ifndef SEAT_H_
#define SEAT_H_
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

/**
 * @brief
 * 根据给定演出厅的行、列数初始化演出厅的所有座位数据，并将每个座位结点按行插入座位链表。管理座位:初始化演出厅座位
 * @param list  seat_list_t类型指针，指向座位链表头指针
 * @param roomID
 * @param rowsCount 座位所在行号
 * @param colsCount 座位所在列号
 * @return int 表示是否成功初始化了演出厅的所有座位。
 */
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,
                      int colsCount);

/**
 * @brief 对座位链表list按座位行号、列号进行排序。
 *
 * @param list seat_list_t类型，表示待排序座位链表头指针。
 */
void Seat_Srv_SortSeatList(seat_list_t list);

/**
 * @brief 增加结点到排序链表
 * 将一个座位结点加入到已排序的座位链表中。
 * @param list seat_list_t类型，表示待插入结点的座位链表头指针
 * @param node seat_node_t指针，表示需要插入的座位数据结点
 */
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node);

/*
标识符：TTMS_SCU_Seat_Srv_Add
功能：单个添加座位
*/
int Seat_Srv_Add(const seat_t *data);

/*
标识符：TTMS_SCU_Seat_Srv_AddBatch
功能：批量添加座位
*/
int Seat_Srv_AddBatch(seat_list_t list);

/*
标识符：TTMS_SCU_Seat_ Srv_Mod
功能：修改座位
*/
int Seat_Srv_Modify(const seat_t *data);

/*
标识符：TTMS_SCU_Seat_Srv_DelByID
功能：删除座位
*/
int Seat_Srv_DeleteByID(int ID);

/*
标识符：TTMS_SCU_Seat_Srv_DeleteAllByRoomID
功能：批量删除座位
*/
int Seat_Srv_DeleteAllByRoomID(int roomID);

/**
 * @brief 根据演出厅ID获得该演出厅的有效座位。
 * @param list seat_list_t类型，表示获取到的有效座位链表头指针
 * @param roomID 需要提取有效座位的演出厅ID。
 * @return int 表示演出厅的有效座位个数
 */
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID);

/*
标识符：TTMS_SCU_Seat_Srv_FetchByID
功能：根据ID获取座位服务
*/
int Seat_Srv_FetchByID(int ID, seat_t *buf);

/*
标识符：标识符：TTMS_SCU_Seat_Srv_FetchByRoomID
功能：根据演出厅ID获取所有座位服务
*/
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID);

/**
 * @brief 根据座位的行、列号获取座位数据。
 *
 * @param list seat_list_t类型，表示座位链表头指针，
 * @param row 待获取座位的行号
 * @param column 列号
 * @return seat_node_t* 获取到的座位数据,没有数据放回NULL。
 */
seat_node_t *Seat_Srv_FindByRowCol(seat_list_t list, int row, int column);

/**
 * @brief 根据座位ID在链表中获取座位数据。
 *
 * @param list seat_list_t类型，指向座位数据链表
 * @param seatID 座位ID
 * @return seat_node_t* 表示获取的座位数据,没有找到返回NULL
 */
seat_node_t *Seat_Srv_FindByID(seat_list_t list, int seatID);

#endif  // SEAT_H_
