#include "MaiAccount_UI.h"
extern account_t gl_CurUser;
void MaiAccount_UI_MgtEntry()
{
    account_t cdata = gl_CurUser;
    char cpassword[30];

    char a;
     char n;
    do{
        printf("维护个人资料界面\n");
        printf("1.修改个人密码\n");
        printf("2.退出此界面\n");
        int i = 0;
        printf("You Choice:");
        scanf("%c", &a);
        getchar();
        switch (a)
        {
            case '1':
               add_pass_:
                i=0;
                printf("请输入新密码\n");
                 while ((n = getchar()) != '\n')
                {
                    if (n == ' ' || i >= 29)
                    {
                        while ((n = getchar()) != '\n');
                        
                        printf("密码不合规\n");
                        i = 0;
                        goto add_pass_;
                    }
                     cpassword[i++] = n;
                }
                if (n == '\n' && i == 0)
                {
                    printf("密码不为空\n");
                    i = 0;
                    goto add_pass_;
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
                break;
        }
    }while (a!='2');
}