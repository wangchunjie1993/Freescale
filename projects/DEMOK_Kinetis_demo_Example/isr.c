/******************** (C) COPYRIGHT 2011 �Ĭ�Ƽ�DEMOK Kinetis����С��**************
 * �ļ���         �� isr.c
 * ����           �� �жϴ�������
 *
 * ʵ��ƽ̨       �� �Ĭ�Ƽ�DEMOK Kinetis������
 * ����           �� �Ĭ�Ƽ�DEMOK Kinetis����С��

 * �Ա�����       �� http://shop60443799.taobao.com/
 * ������������   �� 1030923155@qq.com 
 * ��������QQȺ   �� 103360642

 * ����޶�ʱ��    ��2012-11-7
 * �޶�����        ����
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
#define weizhicha  16   //����λ��PID��ʵ�ʶ��������ֵ�Ĺ�ϵ

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
    double K_speed_rela_servo=0.1;//?�����⣬���������ٶȹ�ϵ
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
        if(xielv1<=-16)                                //��--- -25��
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
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�USART1_IRQHandler
*  ����˵��������1 �ж� ���� ������
*  ����˵������
*  �������أ���
*
*************************************************************************/
void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //�����ж�

    //����һ���ֽ����ݲ��ط�
    ch = uart_getchar (UART1);      //���յ�һ������
    uart_sendStr  (UART1, "\n�㷢�͵�����Ϊ��");
    uart_putchar (UART1, ch);       //�ͷ��ͳ�ȥ

    EnableInterrupts;		    //�����ж�
}

/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�PIT0_IRQHandler
*  ����˵����PIT0 ��ʱ�жϷ�����
*  ����˵������
*  �������أ���
*
*************************************************************************/
#if 1
void PIT0_IRQHandler(void)
{       
  
    //FTM_PWM_Duty(FTM1,CH0,106);//���        106������Ҽ��ޣ�40��������� 75����
    //FTM_PWM_Duty(FTM0,CH0,400);
    //AUTOcontrol3();
  
    //PIDSetPoint(4);  
    PIDmotor();
    

  
 /***********************���ڶ��ٶ�*********************/    
    /* uart_putchar(UART1,'0'+LPTMR0_CNR/100);
     uart_putchar(UART1,'0'+LPTMR0_CNR%100/10);
     uart_putchar(UART1,'0'+LPTMR0_CNR%10);
     uart_putchar(UART1,0x0A);
     uart_putchar(UART1,0x0D);   */
     
 /*********************************************/    
     lptmr_counter_clean();  //���ۼ�����ֵ
     LPT_INT_count = 0;      //�ۼ�����ֵ
  
     //LED_turn(LED1);             //LED1��ת
     PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}
#else
extern u32 test_time;
void PIT0_IRQHandler(void)
{
    test_time++;
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}
#endif


/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�SysTick_Handler
*  ����˵����ϵͳ�δ�ʱ���жϷ�����
*  ����˵������
*  �������أ���
*
*************************************************************************/
void SysTick_Handler(void)
{
    //    OSIntEnter();
    //    OSTimeTick();
    //    OSIntExit();
}


/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�HardFault_Handler
*  ����˵����Ӳ���Ϸ��жϷ�����
*  ����˵������
*  �������أ���
*
*************************************************************************/
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****Ӳ���Ϸô���!!!*****\r\n\n");
    }
}

/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�PendSV_Handler
*  ����˵����PendSV��������ϵͳ���ã��жϷ�����
*  ����˵������
*  �������أ���
*
*************************************************************************/
void PendSV_Handler(void)
{
}


/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�PORTA_IRQHandler
*  ����˵����PORTA�˿��жϷ�����
*  ����˵������
*  �������أ���
*  ��    ע�����ź���Ҫ�Լ���ʼ�������
*
*************************************************************************/
extern u32 rowCnt ;   //�м���
extern u8 ImageBuf[ROW][COL];
u8 SampleFlag = 0;

void PORTA_IRQHandler()
{
   //---HREF���жϴ���
    if( PORTA_ISFR & (1 << 28))         //PTA9�����ж�  
    {
        PORTA_ISFR  |= (1 << 28);        //д1���жϱ�־λ
        
         if ( SampleFlag == 0 )         //����һ��ʱ����
        { 
          return;
        }  
        
        //-------------DAM��ʼ��ͨ��4������ԴΪPTD��ÿ�δ�������ImageBuf[]ָ���У�PCLK��PT19������ÿ�δ���1���ֽڣ�ÿ�δ�������320�Σ������ش���
        DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTB_BYTE0_IN, ImageBuf[rowCnt], PTB8, DMA_BYTE1, 320, DMA_rising);
        //----ʹ��DMA����ʼ����ʱ���ֹDMA
        DMA_EN(DMA_CH4); 
    
        rowCnt++;

        if(rowCnt == 240)
        {
          rowCnt = 0;
          DMA_DIS(DMA_CH4);
          
          //---------��Ϊ��̬��ʾ��ɾ������------------//
          DisableInterrupts;
        }
    }
    
    //---VSYN���жϴ���
    if(PORTA_ISFR & (1 << 29))         //PTA27�����ж�  ���ж�
    { 
        PORTA_ISFR  |= (1 << 29);       //д1���жϱ�־λ
        rowCnt = 0;
        SampleFlag = 1;
    }
}

/*************************************************************************
*                            �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�DMA_CH4_Handler
*  ����˵����DMAͨ��4���жϷ�����
*  ����˵������
*  �������أ���
*
*************************************************************************/
void DMA_CH4_Handler(void)
{
    //DMAͨ��4
    DMA_IRQ_CLEAN(DMA_CH4);                             //���ͨ�������жϱ�־λ    (���������ٴν����ж�)
    DMA_IRQ_DIS(DMA_CH4);                               //��ֹDMA   �ȴ���һ�����ж����ٿ���DMA
 
}

/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�PORTB_IRQHandler
*  ����˵����PORTB�˿��жϷ�����
*  ����˵������
*  �������أ���
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸�
*
*************************************************************************/
void PORTB_IRQHandler()
{
    u8  n = 0;    //���ź�

    n = 0;
    if(PORTB_ISFR & (1 << n))         //PTB0�����ж�
    {
        PORTB_ISFR  |= (1 << n);        //д1���жϱ�־λ
        /*  �û�����  */
        //LED_turn(LED1);                 //LED1��ת
    }

    n = 10;
    if(PORTB_ISFR & (1 << n))         //PTB10�����ж�
    {
        PORTB_ISFR  |= (1 << n);        //д1���жϱ�־λ
        /*  �û�����  */

    }
}

/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�FTM0_IRQHandler
*  ����˵����FTM0���벶׽�жϷ�����
*  ����˵������
*  �������أ���
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
*
*************************************************************************/
void FTM0_IRQHandler()
{


}

/*************************************************************************
*                             �Ĭ�Ƽ�DEMOK Kinetis����С��
*
*  �������ƣ�FTM1_IRQHandler
*  ����˵����FTM1���벶׽�жϷ�����
*  ����˵������
*  �������أ���
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸ģ��ο����еĴ�������Լ��Ĺ���
*
*************************************************************************/
void FTM1_IRQHandler()
{
    u8 s = FTM1_STATUS;             //��ȡ��׽�ͱȽ�״̬  All CHnF bits can be checked using only one read of STATUS.
    u8 n;
    FTM1_STATUS = 0x00;               //���жϱ�־λ

    n = 0;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //��ֹ���벶׽�ж�
        /*     �û�����       */
        //LED_turn(LED1);                             //��תLED1
        printf("\nFTM1�����ж�\n");

        /*********************/
        //�����������￪�����벶׽�жϣ�������main�����������Ҫ������
        //ͨ�� CH0��CH1��Ch2��Ch3 ���˲���
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //�������벶׽�ж�
        //delayms(10);        //��Ϊ������ź�������̲��ȶ������״���������벶׽�����������ʱ
        //�����ǵ��жϲ�Ӧ�ù�����ʱ�����Կ����벶׽�жϾͷ���main�����������Ҫ������
    }

    n = 1;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //��ֹ���벶׽�ж�
        /*     �û�����       */


        /*********************/
        //�����������￪�����벶׽�ж�
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //�������벶׽�ж�
    }

}

void  LPT_Handler(void)
{
    LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //���LPTMR�Ƚϱ�־
    LPT_INT_count++;                    //�ж������1
}




