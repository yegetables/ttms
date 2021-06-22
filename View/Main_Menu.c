/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * File name: Main_Menu.c
 * Description : TTMS 系统主菜单
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#include "Main_Menu.h"
//系统主菜单
extern account_t gl_CurUser;
void Main_Menu(void)
{
    if(SysLogin()==1)
    {
    char choice;
    do
    {
        printf(
            "\n================================================================"
            "==\n");
        printf(
            "**************** Theater Ticket Management System "
            "****************\n");
        if (gl_CurUser.type==9)
        printf("[S]tudio Management.\n"); //管理演出厅
        if (gl_CurUser.type==2)
        printf("[P]lay Management.\n");  //管理剧目
        if (gl_CurUser.type==1)
        {
        printf("[T]icket Sale.\n");  //售票
        printf("[R]eturn Ticket.\n");  //退票
        }
        // printf("[Q]ueries\n");
        if (gl_CurUser.type==2)
        printf("Ra[N]king and Statistics.\n"); //统计票房
        if (gl_CurUser.type==9)
        printf("[A]ccount Management.\n"); 
        if (gl_CurUser.type==1||gl_CurUser.type==2)
        printf("[B]StaSales_UI_MgtEntry\n");  //统计销售额
        printf("[E]xist.\n");
        printf(
            "\n================================================================"
            "==\n");
        printf("Please input your choice:");
        fflush(stdin);
        choice = getchar();
        if(choice=='\n')
        choice = getchar();
        fflush(stdin);
        switch (choice)
        {
            case 'S':
            case 's':
            if (gl_CurUser.type==9)
                Studio_UI_MgtEntry();
                break;
            case 'P':
            case 'p':
            if (gl_CurUser.type==2)
                Play_UI_MgtEntry();
                break;
            // case 'Q':
            // case 'q':
            // Queries_Menu();
            // break;
            case 'T':
            case 't':
            if (gl_CurUser.type==1)
                Sale_UI_MgtEntry();
                break;
            case 'R':
            case 'r':
            if (gl_CurUser.type==1)
                Sale_UI_RetfundTicket();
                break;
            case 'N':
            case 'n':
            if (gl_CurUser.type==2)
                SalesAnalysis_UI_MgtEntry();
                break;
            case 'A':
            case 'a':
                if (gl_CurUser.type==9)
                Account_UI_MgtEntry();
                break;
            case 'B':
            case 'b':
            if (gl_CurUser.type==1||gl_CurUser.type==2)
                StaSales_UI_MgtEntry();
                break;
            case 'M':
            case 'm':
 //bug               MainAccount_UI_MgtEntry();
                break;
        }
    } while ('E' != choice && 'e' != choice);
    }
}
