/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * 用例编号：TTMS_UC_10
 * File name: Studio_UI.h
 * Description : 统计销售额界面层头文件
 * Author:   XUPT
 * Version:  v.1
 */
#ifndef StaSales_UI_H_
#define StaSales_UI_H_


//标识符：TTMS_SCU_StaSales_UI_MgtEnt
//功能：提供统计销售额界面，剧院经理和售票员可以根据角色权限使用“统计售票员销售额”功能和“统计个人销售额”功能。剧院经理只能使用“统计销售员销售额”，售票员只能使用“统计个人销售额”功能
void StaSales_UI_MgtEntry(void);

//标识符：TTMS_SCU_StaSales_UI_Self
//功能：当前登录系统的售票员浏览当日或当月个人的销售额统计功能的入口界面
void StaSales_UI_Self(void);

//标识符：TTMS_SCU_StaSales_UI_Clerk
//功能：剧院经理根据售票员姓名统计售票员某日期区间销售额功能的入口界面
void StaSales_UI_Clerk(void);


#endif /* StaSales_UI_H_ */