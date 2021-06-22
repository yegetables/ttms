/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_02
 * File name: Seat_UI.c
 * Description : 设置座位用例界面层
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#include "Seat_UI.h"

/*
表识符：TTMS_SCU_Seat_UI_S2C
函数功能：根据座位状态获取界面显示符号。
参数说明：status为seat_status_t类型，表示座位状态。
返 回 值：字符型，表示座位的界面显示符号。
*/
inline char Seat_UI_Status2Char(seat_status_t status)
{
    if (status == SEAT_GOOD)
    {
        return CHAR_SEAT_GOOD;
    }
    else if (status == SEAT_NONE)
    {
        return CHAR_SEAT_NONE;
    }
    else if (status == SEAT_BROKEN)
    {
        return CHAR_SEAT_BROKEN;
    }
    else
    {
        return CHAR_SEAT_NONEONE;
    }
}

/*
标识符：TTMS_SCU_Seat_UI_C2S
函数功能：根据输入符号获取座位状态。
参数说明：statusChar为字符型，表示设置座位的输入符号。
返 回 值：seat_status_t类型，表示座位的状态。
*/
inline seat_status_t Seat_UI_Char2Status(char statusChar)
{
    if (statusChar == CHAR_SEAT_GOOD)
    {
        return SEAT_GOOD;
    }
    else if (statusChar == CHAR_SEAT_NONE)
    {
        return SEAT_NONE;
    }
    else
    {
        return SEAT_BROKEN;
    }
}

/*
标识符：TTMS_SCU_Seat_UI_MgtEnt
函数功能：界面层管理座位的入口函数，显示当前的座位数据，并提供座位数据添加、修改、删除功能操作的入口。
参数说明：roomID为整型，是需要设置座位的演出厅ID。
返 回 值：无。
*/
void Seat_UI_MgtEntry(int roomID)
{
    studio_t *buf = (studio_t *)malloc(sizeof(studio_t));  //存储放映厅信息
    if (Studio_Srv_FetchByID(roomID, buf) == 0)  //从文件中读放映厅
    {
        printf("不存在此放映厅\n");
        return;
    }
    seat_list_t list = NULL;  //存储座位的链表
    List_Init(list, seat_node_t);
    char choice;
    do
    {
        if (Seat_Srv_FetchByRoomID(list, roomID) == 0)  //从文件中读座位信息
        {
            printf("此放映厅座位未初始化\n");
            if (Seat_Srv_RoomInit(list, roomID, buf->rowsCount,
                                  buf->colsCount) ==
                0)  //座位初始化并保存到文件中
            {
                printf("初始化失败\n");
                break;
            }
            else
            {
                buf->seatsCount = buf->rowsCount * buf->colsCount;
                printf("初始化成功\n");
                break;
            }
        }
        else
        {
            seat_node_t *curPos;
            printf(
                "\n======================================================="
                "\n");
            printf("****************  座位管理界面  ****************\n");
            printf(
                "-------------------------------------------------------"
                "\n");
            printf("%d放映厅座位共%d行%d列\n", roomID, buf->rowsCount,
                   buf->colsCount);
            int seat[100][100];
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    seat[i][j] = NONE;
                }
            }
            List_ForEach(list, curPos)
            {
                seat[curPos->data.row][curPos->data.column] =
                    (int)(curPos->data.status);
            }
            for (int i = 0; i < buf->rowsCount; i++)
            {
                for (int j = 0; j < buf->colsCount; j++)
                {
                    printf("%c ", Seat_UI_Status2Char(seat[i][j]));
                }
                printf("\n");
            }
            // for (int i = 0; i < buf->rowsCount; i++)
            // {
            //     free(seat[i]);
            // }
            printf(
                "[A]添加座位\n"
                "[U]修改座位\n"
                "[D]删除座位\n"
                "[R]返回\n");

            printf("输入您的选择\n");
            scanf("%c", &choice);
            getchar();
            int row, col;
            switch (choice)
            {
                case 'A':
                case 'a':
                    Seat_UI_Add(list, roomID, buf->rowsCount, buf->colsCount);
                    break;
                case 'u':
                case 'U':
                    printf("输入需要修改的座位行号和列号\n");

                    scanf("%d%d", &row, &col);

                    Seat_UI_Modify(list, row, col);
                    break;
                case 'd':
                case 'D':
                    printf("输入删除座位的行列\n");
                    scanf("%d%d", &row, &col);

                    Seat_UI_Delete(list, row, col);
                    break;
                case 'r':
                case 'R':
                    return;
                default:
                    printf("输入有误,请重新输入\n");
                    break;
            }
        }
    } while (choice != 'r' && choice != 'R');
    List_Destroy(list, seat_node_t);
}

/*

识符：TTMS_SCU_Seat_UI_Add
函数功能：用于添加一个新的座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，
         第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功添加了座位的标志。
//输入一个座位
*/
int Seat_UI_Add(seat_list_t list, int roomID, int row, int column)
{
    int newRecCount = 0;
    char char_status;
    while (1)
    {
        printf("\n=======================================================\n");
        printf("****************  增加座位界面  ****************\n");
        printf("-------------------------------------------------------\n");
        printf("输入待添加的座位行和列\n");
        int newRow, newCol;
        scanf("%d%d", &newRow, &newCol);

        if (newRow <= 0 || newCol <= 0 || newRow > row || newCol > column)
        {
            printf("输入有误,请核实后操作");
            return newRecCount;
        }
        if (Seat_Srv_FindByRowCol(list, newRow,
                                  newCol))  //从文件中读是否存在此座位
        {
            printf("此座位已存在,请核实后操作\n");
            return newRecCount;
        }
        printf("输入此座位状态\n");
        printf(
            "%c:有座位\n"
            "%c:无座位\n"
            "%c:损坏的座位\n",
            CHAR_SEAT_GOOD, CHAR_SEAT_NONE, CHAR_SEAT_BROKEN);
        scanf("%d", &char_status);

        if (char_status == CHAR_SEAT_GOOD || char_status == CHAR_SEAT_NONE ||
            char_status == CHAR_SEAT_BROKEN)
        {
            seat_t data = {
                0,       //座位id
                roomID,  //所在演出厅id
                newRow,  //座位行号
                newCol,  //座位列号
                Seat_UI_Char2Status(char_status),
            };
            if (Seat_Srv_Add(&data))  //文件中添加
            {
                seat_node_t node;
                node.data = data;
                Seat_Srv_AddToSoftedList(list, &node);  //链表中添加
                printf("增加成功\n");
                newRecCount++;
            }
            else
            {
                printf("增加失败\n");
            }
            printf("继续添加输入y\n");
            char choice;
            scanf("%c", choice);
            getchar();
            if (choice != 'y' && choice != 'Y')
            {
                return newRecCount;
            }
        }
        else
        {
            printf("状态输入有误\n");
            return 0;
        }
    }
}

/*
标识符：TTMS_SCU_Seat_UI_Mod
函数功能：用于修改一个座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功修改了座位的标志。
*/
int Seat_UI_Modify(seat_list_t list, int row, int column)
{
    printf("\n=======================================================\n");
    printf("****************  修改座位状态  ****************\n");
    printf("-------------------------------------------------------\n");
    seat_node_t *nodePtr =
        Seat_Srv_FindByRowCol(list, row, column);  //从文件中获取座位信息
    if (nodePtr == NULL)
    {
        printf("此座位不存在\n");
        return 0;
    }
    printf(
        "%c:有座位\n"
        "%c:无座位\n"
        "%c:损坏的座位\n",
        CHAR_SEAT_GOOD, CHAR_SEAT_NONE, CHAR_SEAT_BROKEN);
    printf("%02d行%02d列座位状态为:%c", nodePtr->data.row, nodePtr->data.column,
           Seat_UI_Status2Char(nodePtr->data.status));
    printf("请输入修改后座位的状态\n");
    char char_status;
    scanf("%d", &char_status);

    if (char_status == CHAR_SEAT_GOOD || char_status == CHAR_SEAT_NONE ||
        char_status == CHAR_SEAT_BROKEN)
    {
        nodePtr->data.status = Seat_UI_Char2Status(char_status);  //链表中修改
        if (Seat_Srv_Modify(&nodePtr->data))  //文件中修改
        {
            printf("修改成功\n");
            return 1;
        }
        else
        {
            printf("修改失败\n");
        }
    }
    else
    {
        printf("状态输入有误\n");
    }
    return 0;
}

/*
标识符：TTMS_SCU_Seat_UI_Del
函数功能：用于删除一个座位的数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功删除了座位的标志。
*/
int Seat_UI_Delete(seat_list_t list, int row, int column)
{
    printf("\n=======================================================\n");
    printf("****************  删除座位界面  ****************\n");
    printf("-------------------------------------------------------\n");
    seat_node_t *node = Seat_Srv_FindByRowCol(list, row, column);
    if (node)
    {
        if (Seat_Srv_DeleteByID(node->data.id))  //将座位从文件中删除
        {
            List_FreeNode(node);  //从链表中删除
            printf("删除成功\n");
            return 1;
        }
        else
        {
            printf("删除失败\n");
        }
    }
    else
    {
        printf("不存在此座位\n");
    }
    return 0;
}
