#include "include.h"
volatile u8 keydata1;//PD
volatile u8 keydata2;//PE
extern u8 line_need_scan[4];

void keyinit()
{
    for(u8 aa=7;aa<15;aa++)
    {  
      gpio_init(PORTD,aa,GPI,HIGH);    //D口输入初始化  
    }
  
    for(u8 aa=0;aa<7;aa++)
    {  
      gpio_init(PORTE,aa,GPI,HIGH);    //D口输入初始化  
    }
}
void keyscan()
{
    keydata1= GPIO_GET_8bit(PORTD,8);
    keydata2= GPIO_GET_8bit(PORTE,0);
    switch(keydata1)
     {
       // case 0x7f:FTM_PWM_Duty(FTM0,CH0,0);break;  
        case 0x7d:FTM_PWM_Duty(FTM0,CH0,0);break;
        case 0x7b:FTM_PWM_Duty(FTM0,CH0,40);break;
        case 0x77:FTM_PWM_Duty(FTM0,CH0,50);break;
        case 0x6f:FTM_PWM_Duty(FTM0,CH0,60);break;
        case 0x5f:FTM_PWM_Duty(FTM0,CH0,70);break;
        case 0x3f:FTM_PWM_Duty(FTM0,CH0,80);break;
     }
    switch(keydata2)
     {
        case 0x7e:line_need_scan[0]=80;
                  line_need_scan[1]=100;
                  line_need_scan[2]=110;
                  line_need_scan[0]=125; break;  
                  
        case 0x7d:line_need_scan[0]=60;
                  line_need_scan[1]=75;
                  line_need_scan[2]=80;
                  line_need_scan[0]=120;break;
                  
        case 0x7b: line_need_scan[0]=40;
                  line_need_scan[1]=50;
                  line_need_scan[2]=60;
                  line_need_scan[0]=75;break;
                  
        case 0x77: line_need_scan[0]=120;
                  line_need_scan[1]=150;
                  line_need_scan[2]=130;
                  line_need_scan[0]=155;break;
                  
        case 0x6f: line_need_scan[0]=130;
                  line_need_scan[1]=160;
                  line_need_scan[2]=150;
                  line_need_scan[0]=185;break;
                  
        case 0x5f: line_need_scan[0]=60;
                  line_need_scan[1]=90;
                  line_need_scan[2]=160;
                  line_need_scan[0]=190;break;
        case 0x3f: uart_sendStr (UART1,"PE6");PIDSetKp(3);break;
     }
} 