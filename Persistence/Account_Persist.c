#include "Account_Persist.h"
#include <unistd.h>
int Account_Perst_CheckAccFile()
{
    int ret;
    ret=access("Account.dat",F_OK);
    return ret;
}
int Account_Perst_Insert(account_t* data)
{
    return 1;
}
int Account_Perst_Insert(account_t* data)
{
    return 1;
}
int Account_Perst_RemByID(int id)
{
    return 1;
}
int Account_Perst_SelectAll(account_list_t list)
{
    int n;
    return n;
}
