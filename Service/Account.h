#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <stdio.h>
typedef enum
{
    USR_ANOMY = 0,
    USR_CLERK = 1,
    USR_MANG  = 2,
    USR_ADMIN = 9,
} account_type_t;
typedef struct
{
    int id;
    account_type_t type;
    char username[30];
    char password[30];
} account_t;
typedef struct account_node
{
    account_t data;
    struct account_node *next;
    struct account_node *prev;
} account_node_t, *account_list_t;
void Account_Srv_InitSys();
/**
 * @brief 验证系统用户的用户名和密码
 * 
 * @param usrName 字符数组类型，存储待验证的用户名
 * @param pwd 字符数组类型，存储待验证的用户名的密码
 * @return int 返回1表示存在，返回0表示不存在
 */
int Account_Srv_Verify(char usrName[], char pwd[]);
int Account_Srv_Add(account_t *data);
int Account_Srv_Modify(account_t *data);  //实际根据用户名来找到修改处
int Account_Srv_DeleteByID(int usrID);
int Account_Srv_FetchAll(account_list_t list);
account_node_t *Account_Srv_FindByUsrName(account_list_t list, char usrName[]);
account_t Account_Srv_FetchbyUser(char usrName[]);
#endif