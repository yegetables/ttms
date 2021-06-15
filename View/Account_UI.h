#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_
#include "../Service/Account.h"
int SysLogin();
void Account_UI_MgtEntry();
int Account_UI_Add(account_list_t list);
int Account_UI_Modify(account_list_t list,char usrName[]);
int Account_UI_Delete(account_list_t list,char usrName[]);
int Account_UI_Query(account_list_t list,char usrName[]);

#endif