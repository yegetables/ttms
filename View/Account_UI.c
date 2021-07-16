#include "Account_UI.h"
int getch()
{
   int c = 0;
   struct termios org_opts, new_opts;
   int res = 0;
   //-----  store old settings -----------
   res = tcgetattr(STDIN_FILENO, &org_opts);
   assert(res == 0);
   //---- set new terminal parms --------
   memcpy(&new_opts, &org_opts, sizeof(new_opts));
   new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
   tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
   c = getchar();
   //------  restore old settings ---------
   res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
   assert(res == 0);
   printf("*");
   return c;
}
int SysLogin()  // SL界面
{
    Account_Srv_InitSys();
    int i = 0;
    int j = 0;
    char n;
    char usrname[30];
    char password[30];
    while (i <= 3)
    {
        printf("                                    登录界面\n");
    add_usr:
        printf("                              用户名:");
        j = 0;
        while ((n = getchar()) != '\n')
        {
            if (n == ' ' || j >= 29)
            {
                while ((n = getchar()) != '\n');
                
                printf("用户名不合规\n");
                j = 0;
                goto add_usr;
            }
            usrname[j++] = n;
        }
        if (n == '\n' && j == 0)
        {
            printf("用户名不为空\n");
            j = 0;
            goto add_usr;
        }
        usrname[j] = '\0';

    add_pass_1:
        printf("                              密码:");
        j = 0;
        while ((n = getch()) != '\n')
        {
            if (n == ' ' || j >= 29)
            {
                while ((n = getch()) != '\n')
                    ;
                printf("密码不合规\n");
                j = 0;
                goto add_pass_1;
            }
            password[j++] = n;
        }
        if (n == '\n' && j == 0)
        {
            printf("密码不为空\n");
            j = 0;
            goto add_pass_1;
        }
        password[j] = '\0';
        i++;
        printf("\n");
        if (Account_Srv_Verify(usrname, password) == 0)
        {
            printf("用户不存在或密码错误\n");
        }
        else
        {
            printf("Welcome!%s\n", usrname);
            break;
        }
    }
    if (i == 3)
    {
        printf("错误次数过多\n");
        return 0;
    }
    else
        return 1;
}
int account_UI_Add(account_list_t list)
{
    char cpassword[30];
    char usrename[30];
    account_node_t *tmp = (account_node_t *)malloc(sizeof(account_node_t));
    int i               = 0;
    char n;
    account_t cdata;
    printf("添加新系统用户界面\n");
    add_usr_2:
    printf("请输入你的用户名\n");
    i=0;
    while ((n = getchar()) != '\n')
        {
            if (n == ' ' || i >= 29)
            {
                while ((n = getchar()) != '\n');
                
                printf("用户名不合规\n");
                i = 0;
                goto add_usr_2;
            }
            usrename[i++] = n;
        }
        if (n == '\n' && i == 0)
        {
            printf("用户名不为空\n");
            i = 0;
            goto add_usr_2;
        }
        usrename[i] = '\0';
    memset(cdata.username, '\0', sizeof(cdata.username));
    strcpy(cdata.username, usrename);

add_pass_2:
    printf("请输入你的新密码\n");
    i = 0;
        while ((n = getchar()) != '\n')
        {
            if (n == ' ' || i >= 29)
            {
                while ((n = getchar()) != '\n')
                    ;
                printf("密码不合规\n");
                i = 0;
                goto add_pass_2;
            }
            cpassword[i++] = n;
        }
        if (n == '\n' && i == 0)
        {
            printf("密码不为空\n");
            i = 0;
            goto add_pass_2;
        }
        cpassword[i] = '\0';
    memset(cdata.password, '\0', sizeof(cdata.password));
    strcpy(cdata.password, cpassword);
    printf("请输入新用户的权限\n");
    while (1)
    {
        scanf("%d", (int *)&cdata.type);
        getchar();
        if (cdata.type == 0 || cdata.type == 1 || cdata.type == 2 ||
            cdata.type == 9)
            break;
        else
        {
            printf("不存在此权限\n");
        }
    }
    if (Account_Srv_FindByUsrName(list, usrename) != NULL)
    {
        printf("用户已存在\n");
        return 0;
    }
    else
    {
        if (Account_Srv_Add(&cdata) == 1)
        {
            tmp->data = cdata;
            List_AddTail(list, tmp);
            return 1;
        }
        else
            return 0;
    }
}
int account_UI_Modfify(account_list_t list, char usrName[])
{
    char n;
    int i = 0;
    account_t cdata;
    account_node_t *p;
    char cpassword[30];
    if ((p = Account_Srv_FindByUsrName(list, usrName)) == NULL)
    {  

        printf("用户不存在\n");
        return 0;
    }
    else
        cdata = p->data;
    printf("%s %s\n", cdata.username, cdata.password);
   add_pass_3:
   printf("请输入你的新密码\n");
    i = 0;
        while ((n = getchar()) != '\n')
        {
            if (n == ' ' || i >= 29)
            {
                while ((n = getchar()) != '\n')
                    ;
                printf("密码不合规\n");
                i = 0;
                goto add_pass_3;
            }
            cpassword[i++] = n;
        }
        if (n == '\n' && i == 0)
        {
            printf("密码不为空\n");
            i = 0;
            goto add_pass_3;
        }
        cpassword[i] = '\0';
    memset(cdata.password, '\0', sizeof(cdata.password));
    strcpy(cdata.password, cpassword);
    if (Account_Srv_Modify(&cdata) == 0)
    {
        printf("修改失败\n");
        return 0;
    }
    else
        return 1;
}
int Account_UI_Delete(account_list_t list, char usrName[])
{
    account_node_t *p;
    if ((p = Account_Srv_FindByUsrName(list, usrName)) == NULL)
    {
        printf("用户不存在\n");
        return 0;
    }
    if (Account_Srv_DeleteByID(p->data.id))
    {
        printf("删除成功\n");
        List_DelNode(p) return 1;
    }
    else
    {
        printf("删除失败\n");
        return 0;
    }
}
int Account_UI_Query(account_list_t list, char usrName[])
{
    account_node_t *p;
    if ((p = Account_Srv_FindByUsrName(list, usrName)) == NULL)
    {
        printf("用户不存在\n");
        return 0;
    }
    else
    {
        printf("==================user List=================\n");
        printf("%5s%20s%8s\n\n", "ID", "名称", "权限");
        printf("--------------------------------------------\n");
        printf("%5d%20s%8d\n", p->data.id, p->data.username, p->data.type);
    }
    return 1;
}
void Account_UI_MgtEntry()
{
    int n;
    account_list_t head = NULL;
    List_Init(head, account_node_t);
    n = Account_Srv_FetchAll(head);

    int pageSize, i;
    account_node_t *p;
    char choice;
    char tmp_char;
    char usrename[30];
    printf("Input page size:");
    scanf("%d", &pageSize);
    getchar();
    if (pageSize <= 5) pageSize = 5;
    Pagination_t paging;
      paging.totalRecords = n;
    paging.pageSize     = pageSize;
    Paging_Locate_FirstPage(head, paging);
    do
    {
        printf("==================user List=================\n");
        printf("%5s%20s%8s\n\n", "ID", "名称", "权限");
        printf("--------------------------------------------\n");
        Paging_ViewPage_ForEach(head, paging, account_node_t, p, i)
        {
            printf("%5d%20s%8d\n", p->data.id, p->data.username, p->data.type);
        }
        printf("---Total Records:%2d---------Page%2d/%2d--\n",
               paging.totalRecords, Pageing_CurPage(paging),
               Pageing_TotalPages(paging));
        printf(
            "[A]dd | [M]odify | [D]el | [Q]uery | [P]ast | [N]ext | "
            "[R]eturn\n");
        printf("You Choice:");
        scanf("%c", &choice);
        getchar();
        if (choice >= 'a' && choice <= 'z') choice -= 32;
        switch (choice)
        {
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                    Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
                break;
            case 'N':
                if (!Pageing_IsLastPage(paging))
                    Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
                break;
            case 'A':
                if (account_UI_Add(head) == 1)
                {
               //     n = Account_Srv_FetchAll(head);
                    n++;
                     paging.totalRecords = n;
                    Paging_Locate_LastPage(head, paging, account_node_t);
                }
                else
                    printf("add error\n");
                break;
            case 'M':
        add_usr_1:
                i=0;
                printf("请输入用户名\n");
                 while ((n = getchar()) != '\n')
                {
                    if (n == ' ' || i >= 29)
                    {
                        while ((n = getchar()) != '\n');
                        
                        printf("用户名不合规\n");
                        i = 0;
                        goto add_usr_1;
                    }
                    usrename[i++] = n;
                }
                if (n == '\n' && i == 0)
                {
                    printf("用户名不为空\n");
                    i = 0;
                    goto add_usr_1;
                }
                usrename[i] = '\0';
                if (account_UI_Modfify(head, usrename))
                {
                    printf("修改成功\n");
                    List_Paging(head, paging, account_node_t)
                }
                break;
            case 'D':
                add_usr_3:
                i=0;
                printf("请输入用户名\n");
                 while ((n = getchar()) != '\n')
                {
                    if (n == ' ' || i >= 29)
                    {
                        while ((n = getchar()) != '\n');
                        
                        printf("用户名不合规\n");
                        i = 0;
                        goto add_usr_3;
                    }
                    usrename[i++] = n;
                }
                if (n == '\n' && i == 0)
                {
                    printf("用户名不为空\n");
                    i = 0;
                    goto add_usr_3;
                }
                usrename[i] = '\0';
                if (Account_UI_Delete(head, usrename))
                {

                    n--;
                    paging.totalRecords = n;
                    List_Paging(head, paging, account_node_t)
                }
                break;
            case 'Q':
                add_usr_4:
                i=0;
                printf("请输入用户名\n");
                 while ((n = getchar()) != '\n')
                {
                    if (n == ' ' || i >= 29)
                    {
                        while ((n = getchar()) != '\n');
                        
                        printf("用户名不合规\n");
                        i = 0;
                        goto add_usr_4;
                    }
                    usrename[i++] = n;
                }
                if (n == '\n' && i == 0)
                {
                    printf("用户名不为空\n");
                    i = 0;
                    goto add_usr_4;
                }
                usrename[i] = '\0';
                if (Account_UI_Query(head, usrename))
                {
                    List_Paging(head, paging, account_node_t)
                }
                break;
        }
    } while (choice != 'R' && choice != 'r');
    List_Destroy(head, account_node_t)
}