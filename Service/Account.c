#include "Account.h"

extern account_t gl_CurUser;
account_t Account_Srv_FetchbyUser(char usrName[])
{
    account_t tmp;
    if (Account_Perst_SelByName(usrName, &tmp) == 0)
    {
        printf("未找到");
        tmp.id = -1;
    }
    return tmp;
}
int Account_Srv_Modify(account_t *data)
{
    printf("asddasasd\n\n");
        account_t tmp;
    int found=0;
    FILE *fp = fopen("Account.dat", "rb+");
    if (!fp)
    {
        printf("Account.dat fopen failed\n");
        return 0;
    }
    else
    {
        while (1)
        {
            if (fread(&tmp, sizeof(account_t), 1, fp) < 1)
            {
                if (feof(fp))  //文件结束：返回非0值；文件未结束：返回0值
                {
                    printf("fread error\n");
                    fclose(fp);
                    return 0;
                }
                break;
            }
            if (strcmp(tmp.username,data->username)==0)
            {
                found=1;
                fseek(fp, -(int)sizeof(account_t), SEEK_CUR);
                fwrite(data, sizeof(account_t), 1, fp);
                break;
            }
        }
    fclose(fp);
    if (found==1)
    {
        return 1;
    }
    else return 0;
    }

}
int Account_Srv_Verify(char usrName[], char pwd[])
{
    account_t usr;
    if (Account_Perst_SelByName(usrName, &usr) == 0)
    {
        return 0;
    }
    else
    {
        if (strcmp(pwd, usr.password) == 0)
        {
            gl_CurUser = usr;
            return 1;
        }
        else
            return 0;
    }
}
void Account_Srv_InitSys()
{
    if (Account_Perst_CheckAccFile())
    {
        return;
    }
    else
    {
        account_t admin = {0, USR_ADMIN, "admin", "12345"};
 //       admin.id        = EntKey_Perst_GetNewKeys("系统用户", 1);
        Account_Srv_Add(&admin);
    }
}
int Account_Srv_Add(account_t *data)
{
    if (Account_Perst_Insert(data) < 0)
    {
        return 0;
    }
    else
        return 1;
}
int Account_Srv_DeleteByID(int usrID)
{
    if (Account_Perst_RemByID(usrID))
    {
        return 1;
    }
    else
        return 0;
}
account_node_t *Account_Srv_FindByUsrName(account_list_t list, char usrName[])
{
    account_node_t *q;
    List_ForEach(list, q)
    {
        if (strcmp(usrName, q->data.username) == 0)
        {
            return q;
        }
    }
    return NULL;
}
int Account_Srv_FetchAll(account_list_t list)  
{
    int n = Account_Perst_SelectAll(list);
    return n;
}