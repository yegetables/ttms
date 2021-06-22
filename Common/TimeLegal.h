#ifndef TIMELEGAL_H_
#define TIMELEGAL_H_
/**
 * @brief 判断给定日期是否在规定日期之后且正确
 *
 * @param year 给定年
 * @param month 给定月
 * @param day 给定天
 * @param nowyear 规定年
 * @param nowmon 规定月
 * @param nowday 规定日
 * @return int 返回值==1合法,!=1不合法
 */
int IsTimeLegal(int year, int month, int day, int nowyear, int nowmon,
                int nowday);  //判断年月日是否合法

#endif