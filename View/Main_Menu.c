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
void Main_Menu(void)
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
        printf("[S]tudio Management.\n");
        printf("[P]lay Management.\n");
        printf("[T]icket Sale.\n");
        printf("[R]eturn Ticket.\n");
        // printf("[Q]ueries\n");
        printf("Ra[N]king and Statistics.\n");
        printf("[A]ccount Management.\n");
        printf("[B]StaSales_UI_MgtEntry\n");
        printf("[E]xist.\n");
        printf(
            "\n================================================================"
            "==\n");
        printf("Please input your choice:");
        fflush(stdin);
        choice = getchar();
        switch (choice)
        {
            case 'S':
            case 's':
                Studio_UI_MgtEntry();
                break;
            case 'P':
            case 'p':
                Play_UI_MgtEntry();
                break;
            // case 'Q':
            // case 'q':
            // Queries_Menu();
            // break;
            case 'T':
            case 't':
                Sale_UI_MgtEntry();
                break;
            case 'R':
            case 'r':
                Sale_UI_RetfundTicket();
                break;
            case 'N':
            case 'n':
                SalesAnalysis_UI_MgtEntry();
                break;
            case 'A':
            case 'a':
                Account_UI_MgtEntry();
                break;
            case 'B':
            case 'b':
                StaSales_UI_MgtEntry();
                break;
        }
    } while ('E' != choice && 'e' != choice);
}
