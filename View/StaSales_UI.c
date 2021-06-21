/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : 统计销售额界面层头文件
 * Author:   XUPT
 * Version:  v.1
 */
#include "StaSales_UI.h"
#include "../Common/Common.h"
#include "../Service/Account.h"
#include "../Service/Play.h"
#include "../Service/StaSales.h"
#include "stdio.h"
#include "time.h"
void StaSales_UI_MgtEntry(void)
{
    extern account_t Gl_CurUser;
    if (Gl_CurUser.type == USR_CLERK)
    {
        StaSales_UI_Self();
    }
    else
    {
        if (Gl_CurUser.type == USR_MANG)
        {
            StaSales_UI_Clerk();
        }
        else
        {
            printf("账号没有权限！！");
        }
    }
    return;
}

void StaSales_UI_Self(void)
{
    extern account_t Gl_CurUser;
    int id = Gl_CurUser.id;
    ttms_date_t curdate, startdate, enddate;
    time_t timep;
    struct tm *p;
    time(&timep);
    p               = localtime(&timep);
    curdate.year    = p->tm_year;
    curdate.month   = p->tm_mon;
    curdate.day     = p->tm_mday;
    startdate.year  = p->tm_year;
    startdate.month = p->tm_mon;
    startdate.day = 1;
    enddate.year = p->tm_year;
    enddate.month = p->tm_mon;
    enddate.day = 31;
    printf(
            "---------------------------选择菜单信息----------------------------"
            "----\n");
    printf(
            "\n================================================================"
            "==\n");
    char choice;
    printf("Your choice:");
    scanf("%c",&choice);
    switch (choice)
    {
    case 'd':
    case 'D':
        printf("当日销售额统计：");
        StaSales_Srv_CompSaleVal(id,curdate,curdate);
        break;
    case 'm':
    case 'M':
        printf("当月销售额统计：");
        StaSales_Srv_CompSaleVal(id,startdate,enddate);
        break;
    }
    return;
}

void StaSales_UI_Clerk(void)
{
    extern account_t Gl_CurUser;
    int id = Gl_CurUser.id;
    ttms_date_t curdate,startdate,enddate;
    account_t tmp;
    char Usrname[1000];
    scanf("%s",&Usrname);
    tmp = Account_Srv_FetchbyUser(Usrname);
    id = tmp.id;
    if()
    {
        printf("用户不存在！！");
    }
    else
    {
        StaSales_Srv_CompSaleVal(id, startdate, enddate);
    }
    return;
}