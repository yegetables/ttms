/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * File name: EntityKey_Persit.h
 * Description :  主键服务头文件
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#ifndef COMMON_PERSIST_H_
#define COMMON_PERSIST_H_

/**
 * @brief 根据传入的实体名entName及实体个数count，
 * 为这个count个新实体分配一个长度为count的主键值区间，
 * 使得每个新实体在该区间内都可以分配到 唯一的主键。
 * @param entName 字符数组,表示带获取主键的实体名
 * @param count 实体个数count
 * @return long 该主键区间的最小值
 */
long EntKey_Perst_GetNewKeys(const char entName[], int count);

#endif /* COMMON_PERSIST_H_ */
