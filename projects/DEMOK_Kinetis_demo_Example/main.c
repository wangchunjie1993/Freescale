

#include "common.h"
#include "include.h"

#define point1 22
#define point2 31
#define point3 39
#define point4 46
#define point5 42
#define point6 47
#define point7 51
#define point8 54
#define point9 56
#define point10 57
double average=0;

s16 tenpoint();

void shache();
void GOON();  


u8 ImageBuf[ROW][COL];
extern s16 mid[ROW/4];
extern u8 miss_left_count,miss_right_count;                //丢失左右线次数
void cameradata(void);
void sevorcontrol1();
void print_image();
void display_image();
volatile u8 VSYN = 1;
volatile u32 rowCnt = 0;

u8 line_need_scan[10][4]={{65,75,90,105},{70,80,95,110},{80,90,105,120},{90,110,135,140},{100,120,140,145},
{110,125,150,170},{120,140,160,165},{130,155,185,190},{145,165,190,195},{160,180,205,210}};
u8 choice=7;
//u8 line_need_scan[4]={110,125,150,170};
s16 mid_need[4]={160,160,160,160};




u32 i,j;


void main()
{

   DisableInterrupts;
   sccb_init();
    
    //-----------SCCB恢复默认出厂设置----------//
    //--PCLK:70ns   HREF:63us   VSYN:33.33ms--//
    //--原分辨率为640*480  
    //--在每两个HREF之间有1280个PCLK---U Y V Y U Y V Y 
    //--在每两个VSYN之间有240个HREF    //OV7620是隔行采集
    //sccb_regWrite(0x42,0x11,0x00);   
    //sccb_regWrite(0x42,0x14,0x04);
    //sccb_regWrite(0x42,0x28,0x20);
    //---------------------------------------//

    //----------SCCB寄存器配置---------------//
   for(u8 m=0;m<4;m++)
   {
    sccb_regWrite(0x42,0x11,0x03);    //地址0X11-中断四分频(640*240)           PCLK:166ns   HREF:254.6us   VSYN:133.6ms
    sccb_regWrite(0x42,0x14,0x24);      //地址0X14-QVGA(320*120)                  PCLK:332ns   HREF:509.6us   VSYN:133.6ms
    sccb_regWrite(0x42,0x28,0x20);      //地址0X28-连续采集模式(320*240)              PCLK:666ns   HREF:509.6us   VSYN:133.6ms
    sccb_wait();
   }
    
    //----初始化图像数组----//
    for(i=0; i<ROW; i++)
    {
      mid[i]=COL/2;
      for(j=0;j<COL ;j++)
      {
        ImageBuf[i][j] = 0;
      }
    }
    
    //----初始化串口------//
    uart_init (UART1, 115200);
    
    
    //----初始化外部中断---//
    exti_init(PORTA, 28, rising_down);       //HREF----PORTA3 端口外部中断初始化 ，上升沿触发中断，内部下拉
    exti_init(PORTA, 29, rising_down);        //VSYN----PORTA5 端口外部中断初始化 ，上升沿触发中断，内部下拉
    
    pit_init_ms(PIT0,10);//10MS中断1次
    
    FTM_PWM_init(FTM0, CH0,12000,0);//电机正转  频率10KHZ
    
    FTM_PWM_init(FTM1, CH0,50,90);   //舵机   50HZ
    
    
    gpio_init  (PORTE, 26, GPO, 0);     //PTE26  低
    gpio_init  (PORTE, 24, GPO, 1);     //PTE24  高
    
   

    
    lptmr_counter_init(LPT0_ALT2,800,2,LPT_Rising);//LPTMR  脉冲累计器  800次触发中断
/*********************************GPIO****************************************************/  

   // keyinit();
    
    
    
    EnableInterrupts;
    while(1)
    {
         
    
   /*while(!scan_any_mid(line_need_scan[choice],mid_need))
   {
     if(choice>=7)
     choice=7;
     else
       choice++;
     EnableInterrupts;
   }*/
      scan_any_mid(line_need_scan[choice],mid_need);
   AUTOcontrol3();
      //keyscan();
       //scan_mid();
      //white_line_mid();
     //display_image();
      //print_image();    
      EnableInterrupts;
     
    }
}
/***************10点去平均值**************************/
s16 tenpoint()
{
     u8 point10_he=0;//10次累计的和
     s8 leijia=0;     //与平均值相减累加
     for(u8 i=1;i<11;i++)
     {
          point10_he+=mid[i];
     } 
     average=point10_he/10;
     for(u8 j=1;j<11;j++)
     {
          leijia+=mid[j]-average;
     }
     return(leijia);
     
     
}





/*****************************************/


void shache()
{
       gpio_set(PORTE,26,1);
       gpio_set(PORTE,24,0);
}
void GOON()
{
       gpio_set(PORTE,26,0);
       gpio_set(PORTE,24,1);
}



void cameradata()
{     
      uart_putchar(UART1,0xFF);  //图像头

      for(i=0; i<ROW; i++)
      {
        for(j=0;j<COL ;j++)
         {
          if(ImageBuf[i][j] == 0xFF) ImageBuf[i][j]--;
          uart_putchar(UART1,ImageBuf[i][j]);
         }
      }
}

void display_image()
{
  u32 i,j;
  
  for(i=0;i<ROW;i++)
  {
    for(j=0;j<COL-2;j+=2)
    {
      
      //if(ImageBuf[i][j]<THRESHOLD&&ImageBuf[i][j+1]<THRESHOLD&&ImageBuf[i][j+2]<THRESHOLD)
      //if(white_black(&ImageBuf[i][j],&ImageBuf[i][j+1])||black_white(&ImageBuf[i][j],&ImageBuf[i][j+1]))
      if(turn_black(&ImageBuf[i][j]))
      uart_putchar(UART1,'0');
      else if((j==mid[i])||(j+1)==mid[i])
	  uart_putchar(UART1,'0');
	  else
      uart_putchar(UART1,'1');
    }
    uart_putchar(UART1,0x0d);
    uart_putchar(UART1,0x0a);
  }
  uart_putchar(UART1,0x0d);
  uart_putchar(UART1,0x0a);  
}

void print_image()
{
   
   unsigned int i,j; 

   for(i=0;i<ROW;i++) 
      { 
      for(j=0;j<COL-4;j+=2) 

       { 
         if(ImageBuf[i][j]<THRESHOLD&&ImageBuf[i][j+1]<THRESHOLD&&ImageBuf[i][j+2]<THRESHOLD) 
         uart_putchar(UART1,'0'); 
        else   uart_putchar(UART1,'1'); 
      } 
      uart_putchar(UART1,0x0d);
  uart_putchar(UART1,0x0a);
      }
      uart_putchar(UART1,0x0d);
  uart_putchar(UART1,0x0a);  

}

/*void sevorcontrol1()//////////////////////////////////////
{
  u8 count;
  signed int diff_offset=0;
  signed char diff_xielv=0;
  diff_xielv=mid[30]-mid[37];
  diff_offset=mid[30]-160;
       if(diff_xielv<=-22)
       {
            count=58;
            FTM_PWM_Duty(FTM1,CH0,count);
            if((diff_offset>OFFSET)&&(count<92))
            {
              count+=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else if(diff_xielv<=-14)
       {
            count=63;
            FTM_PWM_Duty(FTM1,CH0,count);
            if((diff_offset>OFFSET)&&(count<92))
            {
              count+=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            else if((diff_offset<(0-OFFSET))&&(count>58))
            {
              count-=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }        
      else if(diff_xielv<=-7)
       {
            count=68;
            FTM_PWM_Duty(FTM1,CH0,count);
            if((diff_offset>OFFSET)&&(count<92))
            {
              count+=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
           else if((diff_offset<(0-OFFSET))&&(count>58))
            {
              count-=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else if(diff_xielv<=-3)
       {
             count=72;
             FTM_PWM_Duty(FTM1,CH0,count);
             if((diff_offset>OFFSET)&&(count<92))
            {
              count+=(diff_offset/2);             
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            else if((diff_offset<(0-OFFSET))&&(count>58))
            {
              count-=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       } 
      else if(diff_xielv<=3)
       {
             count=75;
             FTM_PWM_Duty(FTM1,CH0,count);
             if((diff_offset>OFFSET)&&(count<92))
            {
              count+=(diff_offset/2);             
              FTM_PWM_Duty(FTM1,CH0,count);
            }
             else if((diff_offset<(0-OFFSET))&&(count>58))
            {
              count-=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       } 
      else if(diff_xielv<=7)
       {
            count=78;
            FTM_PWM_Duty(FTM1,CH0,count);
              if((diff_offset>OFFSET)&&(count<92))
            {
              count+=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            else if((diff_offset<(0-OFFSET))&&(count>58))
            {
              count-=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else if(diff_xielv<=14)
       {
            count=82;
            FTM_PWM_Duty(FTM1,CH0,count);
            if((diff_offset>OFFSET)&&(count<92))
            {
              count+=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            else if((diff_offset<(0-OFFSET))&&(count>58))
            {
              count-=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else if(diff_xielv<=22)
       {
            count=87;
            FTM_PWM_Duty(FTM1,CH0,count);
            if((diff_offset>OFFSET)&&(count<92))
            {
              count+=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            else if((diff_offset<(0-OFFSET))&&(count>58))
            {
              count-=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else
       {
            count=92;
            FTM_PWM_Duty(FTM1,CH0,count);
            if((diff_offset<(0-OFFSET))&&(count>58))
            {
              count-=(diff_offset/2);
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
        
}*/



/*void sevorcontrol1()                  
{
  signed char diff=0;
  u8 duty=75;
  if(((diff=(mid[55]-mid[70]))>-18)&&diff<18)
  {
    duty=75+(diff);
    FTM_PWM_Duty(FTM1,CH0,duty);  
  }
  else if(diff<-18)
    FTM_PWM_Duty(FTM1,CH0,57);
  else 
    FTM_PWM_Duty(FTM1,CH0,93);
}*/


void sevorcontrol1()//////////////////////////////////
{
  u8 count;
       if((mid[30]-mid[37])<=-22)
       {
            count=58;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[30]-160>OFFSET)&&(count<92))
            {
              count+=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else if((mid[30]-mid[37])<=-14)
       {
            count=63;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[30]-160>OFFSET)&&(count<92))
            {
              count+=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[30]>OFFSET)&&(count>58))
            {
              count-=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }        
      else if((mid[30]-mid[37])<=-7)
       {
            count=68;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[30]-160>OFFSET)&&(count<92))
            {
              count+=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[30]>OFFSET)&&(count>58))
            {
              count-=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else if((mid[30]-mid[37])<=-3)
       {
             count=72;
             FTM_PWM_Duty(FTM1,CH0,count);
             while((mid[30]-160>OFFSET)&&(count<92))
            {
              count+=1;             
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[30]>OFFSET)&&(count>58))
            {
              count-=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       } 
      else if((mid[30]-mid[37])<=3)
       {
             count=75;
             FTM_PWM_Duty(FTM1,CH0,count);
             while((mid[30]-160>OFFSET)&&(count<92))
            {
              count+=1;             
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[30]>OFFSET)&&(count>58))
            {
              count-=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       } 
      else if(((mid[30]-mid[37])<=7))
       {
            count=78;
            FTM_PWM_Duty(FTM1,CH0,count);
             while((mid[30]-160>OFFSET)&&(count<92))
            {
              count+=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[30]>OFFSET)&&(count>58))
            {
              count-=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else if((mid[30]-mid[37])<=14)
       {
            count=82;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[30]-160>OFFSET)&&(count<92))
            {
              count+=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[30]>OFFSET)&&(count>58))
            {
              count-=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else if((mid[30]-mid[37])<=22)
       {
            count=87;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[30]-160>OFFSET)&&(count<92))
            {
              count+=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[30]>OFFSET)&&(count>58))
            {
              count-=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      else
       {
            count=92;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((160-mid[30]>OFFSET)&&(count>58))
            {
              count-=1;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
        
}


/*void sevorcontrol1()
{
  u8 count;
       if((mid[120]-mid[150])<=-16)
       {
            count=57;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[120]-160>30)&&(count<92))
            {
              count+=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      if((((mid[120]-mid[150])<=-12))&&(((mid[120]-mid[150])>-16)))
       {
            count=63;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[120]-160>30)&&(count<92))
            {
              count+=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[120]>30)&&(count>58))
            {
              count-=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }        
      if((((mid[120]-mid[150])<=-5))&&(((mid[120]-mid[150])>-12)))
       {
            count=70;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[120]-160>30)&&(count<92))
            {
              count+=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[120]>30)&&(count>58))
            {
              count-=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
      if(((mid[120]-mid[150]))>=16)
       {
            count=94;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((160-mid[120]>30)&&(count>58))
            {
              count-=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
       if((((mid[120]-mid[150])>=12))&&(((mid[120]-mid[150])<16)))
       {
            count=87;
            FTM_PWM_Duty(FTM1,CH0,count);
            while((mid[120]-160>30)&&(count<92))
            {
              count+=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[120]>30)&&(count>58))
            {
              count-=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
       if((((mid[120]-mid[150])>=5))&&(((mid[120]-mid[150])<12)))
       {
            count=80;
            FTM_PWM_Duty(FTM1,CH0,count);
             while((mid[120]-160>30)&&(count<92))
            {
              count+=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[120]>30)&&(count>58))
            {
              count-=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }
       if((((mid[120]-mid[150])>-5))&&(((mid[120]-mid[150])<5)))
       {
             count=75;
             FTM_PWM_Duty(FTM1,CH0,count);
             while((mid[120]-160>30)&&(count<92))
            {
              count+=2;             
              FTM_PWM_Duty(FTM1,CH0,count);
            }
            while((160-mid[120]>30)&&(count>58))
            {
              count-=2;
              FTM_PWM_Duty(FTM1,CH0,count);
            }
       }      
}*/



