/******************** (C) COPYRIGHT 2011 岱默科技DEMOK Kinetis开发小组**************
 * 文件名         ： isr.c
 * 描述           ： 中断处理例程
 *
 * 实验平台       ： 岱默科技DEMOK Kinetis开发板
 * 作者           ： 岱默科技DEMOK Kinetis开发小组

 * 淘宝店铺       ： http://shop60443799.taobao.com/
 * 技术交流邮箱   ： 1030923155@qq.com 
 * 技术交流QQ群   ： 103360642

 * 最后修订时间    ：2012-11-7
 * 修订内容        ：无
**********************************************************************************/



#include "common.h"
#include "include.h"
#define firstROW 30
#define secondROW 37
#define midROW  45
s16 xielv2=0;
s16 xielv1=0;
s16 xielvavrage=0;
s16 weizhiPID;
extern u8 cross_flag;
extern u8 line_need_scan[10][4];
extern u8 choice;
s16 PRE_xielvavrage=0;
s16 PRE_ERROR=0;
s16 LAST_ERROR=0;
s32 count=0;
extern s16  mid_need[];
double findKI[]={0.27,0.28,0.29,0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,0.40,0.42,0.44,0.47,0.50,0.54,0.60,0.65,0.75,0.90,1.1,1.60};
double findKP[]={0.05,0.06,0.07,0.08,0.09,0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.30};
double servoduty;
#define weizhicha  16   //修正位置PID与实际舵机控制数值的关系

volatile u32 LPT_INT_count = 0;
volatile u8  pit_flag   = 0;

double PDservo()
{
  
    s16 DJvalue=0;
    double DJ_P=0.1;//0.2
    double DJ_I=0.6;//0.3
    double DJ_D=0.2;//  
   // double DJ_D=0.001;//0.02
 
    
    u8 speed_rela_servo=0;
    double K_speed_rela_servo=0.1;//?？待测，车速与舵机速度关系
    speed_rela_servo=LPTMR0_CNR;
    if(cross_flag==1)
    { 
      DJ_I=findKI[1];
       PIDSetPoint(7);  
    choice=9;
      /* if(choice>=7)
         choice=9;
       else
         choice+=3;*/
     
    }
    else
    {
      choice=3;
       xielv1=mid_need[0]-mid_need[1];
        xielv2=mid_need[1]-mid_need[2];
        xielvavrage=(xielv1+xielv2)/2;
        if(xielv1<=-16)                                //（--- -25）
        {
	    //mid2=150;
		DJ_I=findKI[21];
                 PIDSetPoint(5); 
           
                 //PIDmotor();
                //DJ_P=0.15;
             /*if(choice>=7)
              choice=9;
             else
              choice+=3;*/
                 //choice=5;
        }
        else if(xielv1<-11)                         //(-23  -15)
        {
		DJ_I=findKI[17];
                 PIDSetPoint(5);  
            
                /* if(choice>=8)
                  choice=9;
                 else
                  choice+=2;*/
                // choice=5;
                 //PIDmotor();
        }
        else if(xielv1<-7)                          //(-15   -10)
        {
		    DJ_I=findKI[15];
                 PIDSetPoint(6);  
           
                /* if(choice>=9)
                  choice=9;
                 else
                  choice++;*/
                // choice=4;
                 //PIDmotor();
                       
        }
        else if(xielv1<-3)                        //(-10       -1)
        {
		DJ_I=findKI[7];
                 PIDSetPoint(7);
                //choice=4;
               /*if(choice<=0)
                   choice=0;
                 else
                   choice--;*/
                 //PIDmotor();
        }
        else if(xielv1<=3)                        //(-1    +1)
        {
		 DJ_I=findKI[1];
                 PIDSetPoint(8);  
             
                // choice=3;
                /* if(choice<=1)
                   choice=0;
                 else
                   choice-=2;*/
                 //PIDmotor();
        }
        else if(xielv1<=7)                      //(3   10)
        {
			DJ_I=findKI[7];
                PIDSetPoint(7);  
      
                 //PIDmotor();
                /*if(choice<=0)
                   choice=0;
                 else
                   choice--;*/
                //choice=4;
          } 
          else if(xielv1<=11)                        //(10     15)
          {
			DJ_I=findKI[15];
                PIDSetPoint(6);  
              
                 //PIDmotor();
             /*   if(choice>=9)
                  choice=9;
                 else
                  choice++;*/
               // choice=4;
                
          }
          else if(xielv1<=16)                      //(15   23)
          {
			   DJ_I=findKI[17];
                PIDSetPoint(5); 
               
                 //PIDmotor();
               /* if(choice>=8)
                  choice=9;
                 else
                  choice+=2;*/
               // choice=5;
          }
          else                               //(25    +++)
          {
		DJ_I=findKI[21];
                 PIDSetPoint(5);  
              
                 //PIDmotor();
                 //mid2=170;
                //DJ_P=0.25;
                 /*if(choice>=7)
                  choice=9;
                 else
                  choice+=3;*/
                // choice=5;
          } 
    }
    
     
   
    DJvalue=0-mid_need[3]*DJ_P-xielvavrage*DJ_I+(xielvavrage-PRE_xielvavrage)*DJ_D;
   
      //+(mid[midROW]-PRE_midROW)*DJ_P;
    
    PRE_xielvavrage=xielvavrage;
    return (DJvalue);  
}

void AUTOcontrol3()
{
        weizhiPID=PDservo()+weizhicha;
        
         //uart_putchar (UART1, '0'+weizhiPID/10); 
         //uart_putchar (UART1, '0'+weizhiPID%10); 
        
        if(weizhiPID<-35)
        {
                //weizhiPID=-35;
                FTM_PWM_Duty(FTM1,CH0,40);
        }
        else if(weizhiPID>31)
        {
                //weizhiPID=31;
                FTM_PWM_Duty(FTM1,CH0,106);
        }
       else 
       {
              servoduty=weizhiPID+75;
              FTM_PWM_Duty(FTM1,CH0,servoduty); 
       }
        
                
        
}






/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：USART1_IRQHandler
*  功能说明：串口1 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //关总中断

    //接收一个字节数据并回发
    ch = uart_getchar (UART1);      //接收到一个数据
    uart_sendStr  (UART1, "\n你发送的数据为：");
    uart_putchar (UART1, ch);       //就发送出去

    EnableInterrupts;		    //开总中断
}

/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：PIT0_IRQHandler
*  功能说明：PIT0 定时中断服务函数
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
#if 1
void PIT0_IRQHandler(void)
{       
  
    //FTM_PWM_Duty(FTM1,CH0,106);//舵机        106舵机打到右极限，40舵机打到左极限 75中心
    //FTM_PWM_Duty(FTM0,CH0,400);
    //AUTOcontrol3();
  
    //PIDSetPoint(4);  
    PIDmotor();
    

  
 /***********************串口读速度*********************/    
    /* uart_putchar(UART1,'0'+LPTMR0_CNR/100);
     uart_putchar(UART1,'0'+LPTMR0_CNR%100/10);
     uart_putchar(UART1,'0'+LPTMR0_CNR%10);
     uart_putchar(UART1,0x0A);
     uart_putchar(UART1,0x0D);   */
     
 /*********************************************/    
     lptmr_counter_clean();  //清累计器数值
     LPT_INT_count = 0;      //累加器初值
  
     //LED_turn(LED1);             //LED1反转
     PIT_Flag_Clear(PIT0);       //清中断标志位
}
#else
extern u32 test_time;
void PIT0_IRQHandler(void)
{
    test_time++;
    PIT_Flag_Clear(PIT0);       //清中断标志位
}
#endif


/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：SysTick_Handler
*  功能说明：系统滴答定时器中断服务函数
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
void SysTick_Handler(void)
{
    //    OSIntEnter();
    //    OSTimeTick();
    //    OSIntExit();
}


/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：HardFault_Handler
*  功能说明：硬件上访中断服务函数
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****硬件上访错误!!!*****\r\n\n");
    }
}

/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：PendSV_Handler
*  功能说明：PendSV（可悬起系统调用）中断服务函数
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
void PendSV_Handler(void)
{
}


/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：PORTA_IRQHandler
*  功能说明：PORTA端口中断服务函数
*  参数说明：无
*  函数返回：无
*  备    注：引脚号需要自己初始化来清除
*
*************************************************************************/
extern u32 rowCnt ;   //行计数
extern u8 ImageBuf[ROW][COL];
u8 SampleFlag = 0;

void PORTA_IRQHandler()
{
   //---HREF行中断处理
    if( PORTA_ISFR & (1 << 28))         //PTA9触发中断  
    {
        PORTA_ISFR  |= (1 << 28);        //写1清中断标志位
        
         if ( SampleFlag == 0 )         //不足一场时返回
        { 
          return;
        }  
        
        //-------------DAM初始化通道4，数据源为PTD，每次存在数组ImageBuf[]指针中，PCLK接PT19触发，每次传输1个字节，每次触发传输320次，上升沿触发
        DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTB_BYTE0_IN, ImageBuf[rowCnt], PTB8, DMA_BYTE1, 320, DMA_rising);
        //----使能DMA，初始化的时候禁止DMA
        DMA_EN(DMA_CH4); 
    
        rowCnt++;

        if(rowCnt == 240)
        {
          rowCnt = 0;
          DMA_DIS(DMA_CH4);
          
          //---------若为动态显示，删除此行------------//
          DisableInterrupts;
        }
    }
    
    //---VSYN场中断处理
    if(PORTA_ISFR & (1 << 29))         //PTA27触发中断  场中断
    { 
        PORTA_ISFR  |= (1 << 29);       //写1清中断标志位
        rowCnt = 0;
        SampleFlag = 1;
    }
}

/*************************************************************************
*                            岱默科技DEMOK Kinetis开发小组
*
*  函数名称：DMA_CH4_Handler
*  功能说明：DMA通道4的中断服务函数
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
void DMA_CH4_Handler(void)
{
    //DMA通道4
    DMA_IRQ_CLEAN(DMA_CH4);                             //清除通道传输中断标志位    (这样才能再次进入中断)
    DMA_IRQ_DIS(DMA_CH4);                               //禁止DMA   等待下一次行中断来临开启DMA
 
}

/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：PORTB_IRQHandler
*  功能说明：PORTB端口中断服务函数
*  参数说明：无
*  函数返回：无
*  备    注：引脚号需要根据自己初始化来修改
*
*************************************************************************/
void PORTB_IRQHandler()
{
    u8  n = 0;    //引脚号

    n = 0;
    if(PORTB_ISFR & (1 << n))         //PTB0触发中断
    {
        PORTB_ISFR  |= (1 << n);        //写1清中断标志位
        /*  用户任务  */
        //LED_turn(LED1);                 //LED1反转
    }

    n = 10;
    if(PORTB_ISFR & (1 << n))         //PTB10触发中断
    {
        PORTB_ISFR  |= (1 << n);        //写1清中断标志位
        /*  用户任务  */

    }
}

/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：FTM0_IRQHandler
*  功能说明：FTM0输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*
*************************************************************************/
void FTM0_IRQHandler()
{


}

/*************************************************************************
*                             岱默科技DEMOK Kinetis开发小组
*
*  函数名称：FTM1_IRQHandler
*  功能说明：FTM1输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*
*************************************************************************/
void FTM1_IRQHandler()
{
    u8 s = FTM1_STATUS;             //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
    u8 n;
    FTM1_STATUS = 0x00;               //清中断标志位

    n = 0;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */
        //LED_turn(LED1);                             //翻转LED1
        printf("\nFTM1发送中断\n");

        /*********************/
        //不建议在这里开启输入捕捉中断，而是在main函数里根据需要来开启
        //通道 CH0、CH1、Ch2、Ch3 有滤波器
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
        //delayms(10);        //因为输入的信号跳变过程不稳定，容易触发多次输入捕捉，所以添加延时
        //但考虑到中断不应该过长延时，所以开输入捕捉中断就放在main函数里，根据需要来开启
    }

    n = 1;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
    }

}

void  LPT_Handler(void)
{
    LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //清除LPTMR比较标志
    LPT_INT_count++;                    //中断溢出加1
}




