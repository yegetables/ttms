#include "Account.h"
#include<stdio.h>
account_t Account_Srv_FetchbyUser(char usrName[])
{
    account_t tmp;
    return tmp;
}
int Account_Srv_Modify(account_t *data)
{
    account_t tmp;
    FILE*fp=fopen("Account.dat","rb+");
    if (!fp)
    {
        printf("Account.dat fopen failed\n");
        return 0;
    }
    else{
        while(1)
        {
            if (fread(&tmp, sizeof(account_t), 1, fp)<1)
            {
                if (!feof(fp))//文件结束：返回非0值；文件未结束：返回0值
                {
                    printf("fread error\n");
                    return 0;
                }
                break;
            }
            if (tmp.id==data->id)
            {
                fseek(fp,-(int)sizeof(account_t),SEEK_CUR);
                fwrite(data,sizeof(account_t), 1, fp);
            }
        }
    }
    fclose(fp);
    return 1;
}