#ifndef _ACCOUNT_PERSIST_H_
#define _ACCOUNT_PERSIST_H_
#include "ttms/Service/Account.h";
int Account_Perst_CheckAccFile();
int Account_Perst_Insert(account_t* data);
int Account_Perst_Update(account_t* data);
int Account_Perst_RemByID(int id);
int Account_Perst_SelectAll(account_list_t list);

#endif