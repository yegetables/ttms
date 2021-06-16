/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_02
 * File name: Seat.c
 * Description : 设置座位用例业务逻辑层
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#include "Seat.h"

#include <stdlib.h>
#include <string.h>

#include "../Common/List.h"
#include "../Persistence/Seat_Persist.h"

/*TODO:增加座位:添加新座位
MARK:函数功能：用于添加一个新座位数据。
参数说明：data为seat_t类型指针，表示需要添加的座位数据结点。
返 回 值：整型，表示是否成功添加了座位的标志。
*/
int Seat_Srv_Add(const seat_t *data)
{
    // 请补充完整
    return Seat_Perst_Insert(data);  //存储新座位
}

/*TODO:批量增加座位数据
函数功能：批量添加座位数据。
参数说明：list为seat_list_t类型指针，表示需要添加的批量座位数据形成的链表。
返 回 值：整型，表示是否成功添加了批量座位的标志。
*/
int Seat_Srv_AddBatch(seat_list_t list)
{
    // 请补充完整
    return Seat_Perst_InsertBatch(list);
}

/*TODO:修改座位:更新座位属性
函数功能：用于修改一个座位数据。
参数说明：data为seat_t类型指针，表示需要修改的座位数据结点。
返 回 值：整型，表示是否成功修改了座位的标志。
*/
int Seat_Srv_Modify(const seat_t *data)
{
    // 请补充完整
    return Seat_Perst_Update(data);  //在文件中更新座位数据
}

/*TODO:删除座位:根据座位ID删除座位
函数功能：根据座位ID删除一个座位。
参数说明：ID为整型，表示需要删除的座位数据结点。
返 回 值：整型，表示是否成功删除了座位的标志。
*/
int Seat_Srv_DeleteByID(int ID)
{
    // 请补充完整
    return Seat_Perst_DeleteByID(ID);  //删除座位
}

/*TODO:管理座位:通过座位ID获取座位数据
函数功能：根据座位ID获取座位数据。
参数说明：第一个参数ID为整型，表示座位ID，第二个参数buf为seat_t指针，指向待获取的座位数据结点。
返 回 值：整型，表示是否成功获取了座位的标志。
*/
int Seat_Srv_FetchByID(int ID, seat_t *buf)
{
    // 请补充完整
    return Seat_Perst_SelectByID(ID, buf);
}

/*TODO:删除座位:根据影厅ID删除所有座位
函数功能：根据演出厅ID删除所有座位。
参数说明：roomID为整型，表示需要删除所有座位的演出厅ID。
返 回 值：整型，表示是否成功删除了演出厅所有座位的标志。
*/
inline int Seat_Srv_DeleteAllByRoomID(int roomID)
{
    // 请补充完整
    return Seat_Srv_DeleteAllByRoomID(roomID);
}

/*TODO:根据影厅ID获取所有座位
函数功能：根据演出厅ID获取所有座位服务
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数是放映厅ID
返 回 值：该影厅座位数
*/
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID)
{
    // 请补充完整
    int Count = Seat_Perst_SelectByRoomID(list, roomID);
    Seat_Srv_SortSeatList(list);
    return Count;
}

/*TODO:根据影厅ID获取有效座位
函数功能：根据演出厅ID获得该演出厅的有效座位。
参数说明：第一个参数list为seat_list_t类型，表示获取到的有效座位链表头指针，第二个参数roomID为整型，表示需要提取有效座位的演出厅ID。
返 回 值：整型，表示演出厅的有效座位个数。
*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
    // 请补充完整
    seat_list_t headStr;  //所有roomID的头节点
    List_Init(headStr, seat_node_t);
    Seat_Srv_FetchByRoomID(headStr, roomID);  //获取所有roomID的座位
    int validCount     = 0;                   //有效座位个数
    seat_list_t curPos = NULL;                //遍历座位的指针
    List_ForEach(headStr, curPos)             //遍历所有roomID座位
    {
        if (curPos->data.roomID == SEAT_GOOD)
        {
            List_AddTail(list, curPos);
            validCount++;
        }
    }
    Seat_Srv_SortSeatList(list);
    return validCount;
}
//拼接合成座位ID
int Seat_Srv_myStrcat(int roomID, int rowsCount, int colsCount)
{
    char ID[300] = {'\0'};
    char roomIDStr[100], rowsCountStr[100], colsCountStr[100];
    itoa(roomID, roomIDStr, 10);
    itoa(rowsCount, rowsCountStr, 10);
    itoa(colsCount, colsCountStr, 10);
    strcat(ID, roomIDStr);
    strcat(ID, rowsCountStr);
    strcat(ID, colsCountStr);
    return atoi(ID);
}
/*TODO:管理座位:初始化演出厅座位
函数功能：根据给定演出厅的行、列数初始化演出厅的所有座位数据，并将每个座位结点按行插入座位链表。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功初始化了演出厅的所有座位。
*/
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,
                      int colsCount)
{
    // 请补充完整
    for (int i = 1; i <= rowsCount; i++)
    {
        for (int j = 1; j <= colsCount; j++)
        {
            seat_list_t p = (seat_list_t)malloc(sizeof(seat_node_t));
            seat_t node   = {
                Seat_Srv_myStrcat(roomID, rowsCount, colsCount),
                roomID,
                rowsCount,
                colsCount,
                SEAT_GOOD,
            };
            p->data = node;
            List_AddTail(list, p);
        }
    }
    return Seat_Perst_InsertBatch(list);  //批量存储座位
}
// TODO:排序
void Seat_Srv_qSort(seat_list_t low, seat_list_t high)
{
    seat_list_t i = low, j = high;
    seat_list_t key = (seat_list_t)malloc(sizeof(seat_node_t));
    if (low == high || low->prev == high || low == NULL)
    {
        return;
    }
    key->data = low->data;
    while (low != high && low->prev != high)
    {
        for (;
             low != high && low->prev != high && key->data.id <= high->data.id;
             high = high->prev)
            ;
        if (key->data.id > high->data.id)
        {
            low->data = high->data;
        }
        for (; low != high && low->prev != high && key->data.id >= low->data.id;
             low = low->next)
            ;
        if (key->data.id < low->data.id)
        {
            high->data = low->data;
        }
    }
    low->data = high->data;
    Seat_Srv_qSort(i, low->prev);
    Seat_Srv_qSort(low->next, j);
}
/*TODO:管理座位:对链表排序
函数功能：对座位链表list按座位行号、列号进行排序。
参数说明：list为seat_list_t类型，表示待排序座位链表头指针。
返 回 值：无。
*/
void Seat_Srv_SortSeatList(seat_list_t list)
{
    // 请补充完整
    if (List_IsEmpty(list))
    {
        return;
    }
    list->prev->next     = NULL;
    seat_list_t listLeft = list->next;
    list->next = list->prev = list;
    while (1)
    {
        if (listLeft == NULL)
        {
            return;
        }
        seat_list_t p = listLeft;
        listLeft      = listLeft->next;
        Seat_Srv_AddToSoftedList(listLeft, p);
    }
}

/*TODO:管理座位:增加结点到排序链表
函数功能：将一个座位结点加入到已排序的座位链表中。
参数说明：第一个参数list为seat_list_t类型，表示待插入结点的座位链表头指针，第二个参数node为seat_node_t指针，表示需要插入的座位数据结点。
返 回 值：无。
*/
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node)
{
    // 请补充完整
    if List_IsEmpty (list)
    {
        List_AddTail(list, node);
        return;
    }
    seat_list_t curPos;
    List_ForEach(list, curPos)
    {
        if (!(curPos != list && (curPos->data.row < node->data.row) ||
              curPos->data.row == node->data.row &&
                  curPos->data.column < node->data.column))
        {
            List_InsertBefore(curPos, node);
            return;
        }
    }
    List_AddTail(list, node);
}

/*TODO:增加座位|修改座位|删除座位:判断是否存在
函数功能：根据座位的行、列号获取座位数据。
参数说明：第一个参数list为seat_list_t类型，表示座位链表头指针，
         第二个参数row为整型，表示待获取座位的行号，第三个参数column为整型，表示待获取座位的列号。
返 回 值：为seat_node_t指针，表示获取到的座位数据。
*/
seat_node_t *Seat_Srv_FindByRowCol(seat_list_t list, int row, int column)
{
    // 请补充完整
    seat_list_t p = NULL;
    List_ForEach(list, p)
    {
        if (p->data.row == row && p->data.column == column)
        {
            return p;
        }
    }
    return NULL;
}

/*TODO:根据座位ID获取座位数据
函数功能：根据座位ID在链表中获取座位数据。
参数说明：第一个参数list为seat_list_t类型，指向座位数据链表，第二个参数ID为整型，表示座位ID。
返 回 值：seat_node_t类型，表示获取的座位数据。
*/
seat_node_t *Seat_Srv_FindByID(seat_list_t list, int rowID)
{
    // 请补充完整
    seat_list_t p = NULL;
    List_ForEach(list, p)
    {
        if (p->data.id == rowID)
        {
            return p;
        }
    }
    return NULL;
}
