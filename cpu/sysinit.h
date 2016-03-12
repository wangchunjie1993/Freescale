/******************** (C) COPYRIGHT 2012-2013 岱默科技 DEMOK**********************
 * 文件名         ：sysinit.h
 * 描述           ：系统时钟配置相关函数的头文件
 *
 * 实验平台       ： 岱默科技DEMOK Kinetis开发板
 * 作者           ： 岱默科技DEMOK Kinetis开发小组

 * 淘宝店铺       ： http://shop60443799.taobao.com/
 * 技术交流邮箱   ： 1030923155@qq.com 
 * 技术交流QQ群   ： 103360642
 *
**********************************************************************************/

#ifndef    _SYSINIT_H_
#define    _SYSINIT_H_

/********************************************************************/
extern u32 core_clk_khz;
extern u32 core_clk_mhz;
extern u32 bus_clk_khz;



// function prototypes
void sysinit (void);
void trace_clk_init(void);
void fb_clk_init(void);
void enable_abort_button(void);



/********************************************************************/

#endif  //_SYSINIT_H_