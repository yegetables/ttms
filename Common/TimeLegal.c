#include "TimeLegal.h"

#include <stdio.h>
/**
 * @brief 判断给定年是否是闰年
 *
 * @param year 给定年
 * @return int 返回值==1闰年,返回值!=1不是闰年
 */
int IsLeadYear(int year)
{
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/**
 * @brief 返回月份最大天数
 *
 * @param year 给定年
 * @param month 给定月
 * @return int 返回最大天数
 */
int MaxDay(int year, int month)  //返回月份的天数
{
    if (month == 2)
    {
        if (IsLeadYear(year))
        {
            return 29;
        }
        else
        {
            return 30;
        }
    }
    else
    {
        if (month == 1 || month == 3 || month == 5 || month == 7 ||
            month == 8 || month == 10 || month == 12)
        {
            return 31;
        }
        else
        {
            return 30;
        }
    }
}

int IsTimeLegal(int year, int month, int day, int nowyear, int nowmon,
                int nowday)  //判断年月日是否合法
{
    if (year >= nowyear)
    {
        if (((year > nowyear && month >= 1) || month >= nowmon) && month <= 12)
        {
            if ((year > nowyear || (month > nowmon && day >= 1) ||
                 day >= nowday) &&
                day <= MaxDay(year, month))
            {
                return 1;
            }
        }
    }
    return 0;
}