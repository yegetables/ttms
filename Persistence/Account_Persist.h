#ifndef ACCOUNT_PERSIST_H_
#define ACCOUNT_PERSIST_H_
#include "../Service/Account.h";
/**
 * @brief 判断系统用户文件是否存在
 * 
 * @return int 返回0表示不存在，1表示存在
 */
int Account_Perst_CheckAccFile(); //默认放在当前目录下了，不是的话后面改路径
/**
 * @brief 存储新系统用户
 * 
 * @param data 为account_t类型指针，指向一个用户信息
 * @return int 返回0表示插入失败，返回1表示成功
 */
int Account_Perst_Insert(account_t* data);
/**
 * @brief 更新系统用户
 * 
 * @param data 为account_t类型的指针，指向一个系统用户信息
 * @return int 返回0表示更新失败，返回1表示成功
 */
int Account_Perst_Update(account_t* data);
/**
 * @brief 根据ID去除系统用户
 * 
 * @param id 表示系统用户的ID
 * @return int 返回0表示删除失败，1表示成功
 */
int Account_Perst_RemByID(int id);
/**
 * @brief 载入全部系统用户
 * 
 * @param list 为account_list_t类型，表示指向系统用户链表的头指针。
 * @return int 表示获取到的系统用户数
 */
int Account_Perst_SelectAll(account_list_t list);

#endif