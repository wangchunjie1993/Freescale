/******************** (C) COPYRIGHT 2012-2013 岱默科技 DEMOK**********************
 * 文件名          ：mcg.h
 * 描述            ：锁相环头文件
 *
 *
 * 实验平台        ： 岱默科技DEMOK Kinetis开发板
 * 作者            ： 岱默科技DEMOK Kinetis开发小组

 * 淘宝店铺        ： http://shop60443799.taobao.com/
 * 技术交流邮箱    ： 1030923155@qq.com 
 * 技术交流QQ群    ： 103360642

 * 最后修订时间    ：2012-11-7
 * 修订内容        ：无
 *********************************************************************************/

#ifndef __MCG_H__
#define __MCG_H__


enum crystal_val
{
    XTAL2,
    XTAL4,
    XTAL6,
    XTAL8,
    XTAL10,
    XTAL12,
    XTAL14,
    XTAL16,
    XTAL18,
    XTAL20,
    XTAL22,
    XTAL24,
    XTAL26,
    XTAL28,
    XTAL30,
    XTAL32
};


typedef enum clk_option
{
    PLLUSR      ,  //自定义设置分频系数模式，直接加载 全局变量 mcg_div 的值
    PLL48    = 48,
    PLL50    = 50,
    PLL96    = 96,
    PLL100   = 100,
    PLL110   = 110,
    PLL120   = 120,
    PLL125   = 125,
    PLL130   = 130,
    PLL140   = 140,
    PLL150   = 150,
    PLL160   = 160,
    PLL170   = 170,
    PLL180   = 180,
    PLL200   = 200, //绝大部分芯片都成超到这个程度
    PLL225   = 225, //不同芯片，不同板子，超频能力不一样，不一定全部都能超到这个水平
    PLL250   = 250
} clk_option;


//时钟分频因子
struct mcg_div
{
    u8 prdiv;       //外部晶振分频因子选项
    u8 vdiv;        //外部晶振倍频因子选项
    u8 core_div;    //内核时钟分频因子
    u8 bus_div;     //总线时钟分频因子
    u8 flex_div;    //flex时钟分频因子
    u8 flash_div;   //flash时钟分频因子
};

extern struct mcg_div  mcg_div;


unsigned char pll_init(clk_option);         //锁相环初始化



/********************** 内部用 或 不常用  **************************/

__RAMFUN void set_sys_dividers(uint32 outdiv1, uint32 outdiv2, uint32 outdiv3, uint32 outdiv4);




/********************************************************************/
#endif /* __MCG_H__ */
