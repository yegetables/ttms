#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Service/Account.h"
#include "MaiAccount_UI.h"
extern account_t gl_CurUser;
void MainAccount_UI_MgtEntry()
{
    account_t cdata = gl_CurUser;
    char cpassword[30];
    while (1)
    {
        printf("维护个人资料界面\n");
        printf("1.修改个人密码\n");
        printf("2.修改其他资料(未开放)\n");
        printf("3.退出此界面\n");
        char a;
        char b;
        char n;
        int i = 0;
        while (1)
        {
            a = getchar();
            while ((b = getchar()) != '\n')
                ;
            if (a != '1' && a != '2' && a != '3')
            {
                printf("%c不是一个可执行的选项！\n", a);
                printf("请重新输入！");
            }
            else
                break;
        }
        if (a == '3')
        {
            break;
        }
        switch (a)
        {
            case '1':
                i = 0;
                printf("请输入你的新密码\n");
                while (1)
                {
                    n = getchar();
                    if (i == 0 && n == '\n')
                    {
                        printf("密码不为空\n");
                    }
                    else if (n == ' ' || i >= 29)
                    {
                        printf("密码不合规请重新输入\n");
                        i = 0;
                        while ((n = getchar()) != '\n')
                            ;
                    }
                    else
                    {
                        if (n == '\n') break;
                        cpassword[i++] = n;
                    }
                }
                cpassword[i] = '\0';
                memset(cdata.password, '\0', sizeof(cdata.password));
                strcpy(cdata.password, cpassword);
                printf("new:%s\n", cdata.password);
                if (Account_Srv_Modify(&cdata) == 0)
                {
                    printf("Account_Srv_Modify error!\n");
                }
                break;
            case '2':
                printf("暂时未开放");
                break;
        }
    }
}