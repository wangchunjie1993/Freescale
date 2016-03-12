/******************** (C) COPYRIGHT 2012-2013 岱默科技 DEMOK**********************
 * 文件名         ：delay.h
 * 描述           ：模拟延时函数头文件
 *
 * 实验平台       ： 岱默科技DEMOK Kinetis开发板
 * 作者           ： 岱默科技DEMOK Kinetis开发小组

 * 淘宝店铺       ： http://shop60443799.taobao.com/
 * 技术交流邮箱   ： 1030923155@qq.com 
 * 技术交流QQ群   ： 103360642
**********************************************************************************/


#ifndef __DELAY_H__
#define __DELAY_H__

#include "common.h"

void  delay(void);          //延时约500ms
void  delayms(uint32  ms);

#endif