/*
 * Copyright(C), 2007-2008, XUPT Univ.
 * File name: TTMS.c
 * Description : Main in C, Ansi-style
 * Author:   XUPT
 * Version:  v.1
 * Date: 	2015年4月22日
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "./View/Main_Menu.h"
#include "io.h"

//系统运行入口函数main
int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    Main_Mednu();
    return EXIT_SUCCESS;
}
