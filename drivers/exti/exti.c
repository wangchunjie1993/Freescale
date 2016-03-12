/******************** (C) COPYRIGHT 2012-2013 岱默科技 DEMOK*********
 * 文件名         ：exti.c
 * 描述           ：EXTI外部GPIO中断例程
 *
 * 实验平台       ： 岱默科技DEMOK Kinetis开发板
 * 作者           ： 岱默科技DEMOK Kinetis开发小组

 * 淘宝店铺       ： http://shop60443799.taobao.com/
 * 技术交流邮箱   ： 1030923155@qq.com 
 * 技术交流QQ群   ： 103360642

 * 最后修订时间   ：2012-11-02
 * 修订内容       ：无
**********************************************************************************/

#include "common.h"
#include "gpio.h"
#include "exti.h"




/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：exti_init
*  功能说明：EXTI外部GPIO中断初始化
*  参数说明：PORTx       端口号（PORTA,PORTB,PORTC,PORTD,PORTE）
*            n           端口引脚
*            exti_cfg    触发选项和上拉下拉选项
*  函数返回：无
*
*************************************************************************/
void  exti_init(PORTx portx, u8 n, exti_cfg cfg)
{
    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << portx);    //开启PORTx端口

    PORT_PCR_REG(PORTX[portx], n) = PORT_PCR_MUX(1) | PORT_PCR_IRQC(cfg & 0x7f ) | PORT_PCR_PE_MASK | ((cfg & 0x80 ) >> 7); // 复用GPIO , 确定触发模式 ,开启上拉或下拉电阻
    GPIO_PDDR_REG(GPIOx[portx]) &= ~(1 << n);       //输入模式
    enable_irq(portx + 87);                         //使能PORT中断，PORTA的ISR中断号为87
}