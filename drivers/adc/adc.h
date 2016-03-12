/******************** (C) COPYRIGHT 2012-2013 岱默科技 DEMOK*******************
 * 文件名         ：adc.h
 * 描述           ：adc驱动函数头文件
 *
 * 实验平台       ： 岱默科技DEMOK Kinetis开发板
 * 作者           ： 岱默科技DEMOK Kinetis开发小组

 * 淘宝店铺       ： http://shop60443799.taobao.com/
 * 技术交流邮箱   ： 1030923155@qq.com 
 * 技术交流QQ群   ： 103360642

 * 最后修订时间    ：2012-11-2
 * 修订内容        ：无
**********************************************************************************/




#ifndef __ADC_H__
#define __ADC_H__ 1

#include "adc_cfg.h"


typedef enum ADCn    //ADC端口
{
    ADC0,
    ADC1
} ADCn;


typedef enum ADC_Ch   //ADC通道
{
    //SC1n[DIFF]= 0
    //  ---------------------ADC0----------------       ---------------ADC1------------
    DAD0 = 0, //	    1P3(0P0)				       1P0
    DAD1 = 1, //	    0P1				               1P1
    DAD2 = 2, //	    DP                                          DM
    DAD3 = 3, //	    1P0(0P3)	                               1P3			         

    //ADCx_CFG2[MUXSEL] 位决定 ADCx_SEn 通道为 a 或 b.
    AD4a = 4, //	    保留                               ADC1_SE4a   -- PTE0
    AD5a = 5, //	    保留                               ADC1_SE5a   -- PTE1
    AD6a = 6, //	    保留		               ADC1_SE6a   -- PTE2
    AD7a = 7, //	    保留	                       ADC1_SE7a   -- PTE3

    //也是 4、5、6、7
    AD4b = AD4a, //	    ADC0_SE4b	-- PTC2			 ADC1_SE4b-- PTC8
    AD5b = AD5a, //	    ADC0_SE5b	-- PTD1			                ADC1_SE5b-- PTC9
    AD6b = AD6a, //	    ADC0_SE6b	-- PTD5			                ADC1_SE6b   -- PTC10
    AD7b = AD7a, //	    ADC0_SE7b	-- PTD6			                ADC1_SE7b   -- PTC11

    AD8 = 8,  //	    ADC0_SE8  	-- PTB0			                ADC1_SE8    -- PTB0
    AD9 = 9,  //	    ADC0_SE9  	-- PTB1			                ADC1_SE9    -- PTB1
    AD10 = 10, //	    ADC0_SE10 	-- PTA7			                ADC1_SE10   -- PTB4
    AD11 = 11, //	    ADC0_SE11 	-- PTA8			                ADC1_SE11   -- PTB5
    AD12 = 12, //	    ADC0_SE12 	-- PTB2			                ADC1_SE12   -- PTB6
    AD13 = 13, //	    ADC0_SE13 	-- PTB3			                ADC1_SE13   -- PTB7
    AD14 = 14, //	    ADC0_SE14 	-- PTC0			                ADC1_SE14   -- PTB10
    AD15 = 15, //	    ADC0_SE15 	-- PTC1			                ADC1_SE15   -- PTB11
    AD16 = 16, //	    ADC0_SE16				                    ADC1_SE16
    AD17 = 17, //	    ADC0_SE17 	-- PTE24		                ADC1_SE17   -- PTA17
    AD18 = 18, //	    ADC0_SE18 	-- PTE25		                VREF Output
    AD19 = 19, //	    ADC0_DM0				                    ADC1_DM0
    AD20 = 20, //	    ADC0_DM1				                    ADC1_DM1
    AD21 = 21, //				        	                        保留
    AD22 = 22, //
    AD23 = 23, //	    DAC0_OUT(12-bit) -- DAC0_OUT		        DAC1_OUT(12-bit)
    AD24 = 24, //	    保留					保留
    AD25 = 25, //	    保留					保留
    AD26 = 26, //	    Temperature Sensor (S.E)		            Temperature Sensor (S.E)
    AD27 = 27, //	    Bandgap (S.E)				                Bandgap (S.E)
    AD28 = 28, //	    保留					                    保留
    AD29 = 29, //	    VREFH (S.E)				                    VREFH (S.E)
    AD30 = 30, //	    VREFL					                    VREFL
    AD31 = 31 //	    禁用ADC0				                    禁用ADC1
} ADC_Ch;

//精度位数
typedef enum ADC_nbit
{
    ADC_8bit   = 0x00,
    ADC_10bit  = 0x02,
    ADC_12bit  = 0x01,
    ADC_16bit  = 0x03
} ADC_nbit;


//外部函数接口声明
extern void     adc_init  (ADCn, ADC_Ch);              //AD初始化
extern u16      ad_once   (ADCn, ADC_Ch, ADC_nbit);    //采集一次一路模拟量的AD值

extern u16      ad_mid    (ADCn, ADC_Ch, ADC_nbit);    //中值滤波后的结果
extern u16      ad_ave    (ADCn, ADC_Ch, ADC_nbit, u8 N); //均值滤波后的结果
extern u16      ad_flt    (ADCn, ADC_Ch, ADC_nbit);    //与前几次采样均值滤波   速度快于ad_ave很多，如果相邻采样时间比较短，则采样精确于 ad_once。即采样间距较短的情况下优先考虑使用这个

extern void     adc_start (ADCn, ADC_Ch, ADC_nbit);    //开始adc转换
extern void     adc_stop  (ADCn);                      //停止ADC转换


//内部函数声明
static void adc_config_alt(ADC_MemMapPtr adcmap, tADC_ConfigPtr ADC_CfgPtr);//将adc寄存器结构体配置进adc寄存器


#endif /* __ADC16_H__ */
