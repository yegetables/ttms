#include "Account_Persist.h"

account_t gl_CurUser;
int Account_Perst_CheckAccFile()
{
    if (access("Account.dat", F_OK) == 0)
    {
        return 1;
    }
    else
        return 0;
}
int Account_Perst_Insert(account_t* data)
{
    FILE* fp = fopen("Account.dat", "ab+");
    if (!fp)
    {
        printf("Account.dat fopen failed\n");
        fclose(fp);
        return 0;
    }
    data->id = EntKey_Perst_GetNewKeys("系统用户", 1);
    if (fwrite(data, sizeof(account_t), 1, fp) < 0)
    {
        printf("fwrite error\n");
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}
int Account_Perst_Update(account_t* data)
{
    account_t tmp;
    FILE* fp = fopen("Account.dat", "rb+");
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
                if (!feof(fp))  //文件结束：返回非0值；文件未结束：返回0值
                {
                    printf("fread error\n");
                    return 0;
                }
                break;
            }
            if (tmp.id == data->id)
            {
                fseek(fp, -(int)sizeof(account_t), SEEK_CUR);
                fwrite(data, sizeof(account_t), 1, fp);
            }
        }
    }
    fclose(fp);
    return 1;
}
int Account_Perst_RemByID(int id)
{
    account_t tmp;
    FILE* fp  = fopen("Account.dat", "rb+");
    int found = 0;
    FILE* fp1 = fopen("Account1.dat", "wb+");
    if (!fp || !fp1)
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
                if (!feof(fp))  //文件结束：返回非0值；文件未结束：返回0值
                {
                    printf("fread error\n");
                    return 0;
                }
                break;
            }
            if (tmp.id == id)
            {
                found = 1;
            }
            else
            {
                fwrite(&tmp, sizeof(account_t), 1, fp1);
            }
        }
    }
    fclose(fp);
    fclose(fp1);
    if (remove("Account.dat") != 0)
    {
        return 0;
    }
    if (rename("Account1.dat", "Account.dat") != 0)
    {
        return 0;
    }
    return found;
}
int Account_Perst_SelectAll(account_list_t list)  // list在外部初始化
{
    int n;
    account_node_t* p;
    account_t tmp;
    FILE* fp = fopen("Account.dat", "rb+");
    if (!fp)
    {
        printf("Account.dat fopen failed\n");
        return 0;
    }
    else
    {
        while (1)
        {
            p = (account_node_t*)malloc(sizeof(account_node_t));
            if (fread(&tmp, sizeof(account_t), 1, fp) < 1)
            {
                if (!feof(fp))  //文件结束：返回非0值；文件未结束：返回0值
                {
                    printf("fread error\n");
                    return 0;
                }
                break;
            }
            p->data = tmp;
            n++;
            List_AddTail(list, p)
        }
    }
    fclose(fp);
    return n;
}
int Account_Perst_SelByName(char usrName[], account_t* usr)
{
    account_t tmp;
    FILE* fp = fopen("Account.dat", "rb+");
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
                if (!feof(fp))  //文件结束：返回非0值；文件未结束：返回0值
                {
                    printf("fread error\n");
                }
                break;
            }
            if (strcmp(usrName, tmp.username) == 0)
            {
                *usr = tmp;
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}