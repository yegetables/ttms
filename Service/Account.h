#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Common/List.h"
#include "../Persistence/Account_Persist.h"
#include "../Persistence/EntityKey_Persist.h"
/**
 * @brief 创建管理员匿名系统用户
 * 
 */
void Account_Srv_InitSys();
/**
 * @brief 验证系统用户的用户名和密码
 *
 * @param usrName 字符数组类型，存储待验证的用户名
 * @param pwd 字符数组类型，存储待验证的用户名的密码
 * @return int 返回1表示存在，返回0表示不存在
 */
int Account_Srv_Verify(char usrName[], char pwd[]);
/**
 * @brief 添加新系统用户
 * 
 * @param data 指向account_t类型的一个常量指针，表示接收一个新的系统用户
 * @return int 
 */
int Account_Srv_Add(account_t *data);
/**
 * @brief 修改系统用户
 * 
 * @param data 指向account_t类型的一个指针，表示接收一个系统用户。
 * @return int 返回0表示失败，1表示成功。
 */
int Account_Srv_Modify(account_t *data);  //实际根据用户名来找到修改处
/**
 * @brief 删除系统用户
 * 
 * @param usrID 整形，表示系统用户的ID编码。
 * @return int 返回0表示删除失败，1表示删除成功。
 */
int Account_Srv_DeleteByID(int usrID);
/**
 * @brief 为所有系统用户创建节点并加入链表
 * 
 * @param list 一个初始化过的链表头节点
 * @return int 返回链表元素个数
 */
int Account_Srv_FetchAll(account_list_t list);
/**
 * @brief 根据用户名获取系统用户指针
 * 
 * @param list list为account_list_t类型，表示系统用户链表头指针
 * @param usrName usrName为字符数组，表示接收的系统用户名
 * @return account_node_t* 
 */
account_node_t *Account_Srv_FindByUsrName(account_list_t list, char usrName[]);
/**
 * @brief 判断用户是否存在
 * 
 * @param usrName 传入的系统用户名称
 * @return account_t 返回找到的系统用户信息
 */
account_t Account_Srv_FetchbyUser(char usrName[]);
#endif