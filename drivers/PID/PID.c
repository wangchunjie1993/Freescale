#include"PID.h"
extern  u8 xielv1;
double  iError;
long int uiGoalvalue1=0,speed;
u8 motorfirst_flag=0;
typedef struct PID
{
	int  SetPoint; 			//  �趨Ŀ�� Desired Value
	long SumError;			//	����ۼ� 
		
	double  Proportion;     //  �������� Proportional Const
	double  Integral;       //  ���ֳ��� Integral Const
	double  Derivative;     //  ΢�ֳ��� Derivative Const
	double  Tams;            //  �������� 

	double LastError;         	//  Error[-1]
	double PrevError;          //  Error[-2]

} PID;
PID	 sPID;
PID	 *sptr = &sPID;

//�������ܣ�PID��ʼ��(pid���õ���RAM����)
void PIDInit(void)
{
    sptr->LastError  = 0;			//Error[-1]
    sptr->PrevError  = 0;			//Error[-2]
    sptr->Proportion = 0;			//�������� Proportional Const
    sptr->Integral   = 0;			//���ֳ��� Integral Const
    sptr->Derivative = 0;			//΢�ֳ��� Derivative Const
    sptr->SetPoint   = 0;
    sptr->SumError   = 0;
    sptr->Tams       = 0;
}

void PIDSetPoint(int setpoint)
{
	  sptr->SetPoint = setpoint;
}
int PIDGetSetpoint(void)
{	
          return(sptr->SetPoint);	
}
void PIDSetKp(double dKpp)
{	
          sptr->Proportion = dKpp;	
}
double PIDGetKp(void)
{	
          return(sptr->Proportion);	
}
void PIDSetKi(double dKii)
{
          sptr->Integral = dKii;
}
double PIDGetKi(void)
{
          return(sptr->Integral);	
}
void PIDSetKd(double dKdd)
{	
          sptr->Derivative = dKdd;	
}
double PIDGetKd(void)
{	
          return(sptr->Derivative);	
}
void PIDSetTams(double tams) 
{
          sptr->Tams = tams;
}

float IncPIDCalc(int NextPoint)    //��ҪPID���㺯��
{
  
      	PIDSetKp(1.50);  //���ñ���ϵ��1.3
        PIDSetKi(0.85);    //���û���ϵ��0.85
        PIDSetKd(0.40); //0.36
        double iIncpid;
        iError = sptr->SetPoint - NextPoint;
       
        iIncpid =sptr->Proportion * iError - sptr->Integral * sptr->LastError + sptr->Derivative * sptr->PrevError;
        sptr->PrevError = sptr->LastError;
  	sptr->LastError = iError;
  	return(iIncpid);
	 
}
void PIDmotor()
{
        s16 var=0;
        u8 servo_rela_speed =xielv1;  //����ٶ��ܽǶȵ�����
        double K_servo_rela_speed=0.1;//���������� б��Ӱ�����ٶ�
        speed = LPTMR0_CNR;// �Ķ�  
        var=IncPIDCalc(speed);
        uiGoalvalue1 += var;
        
        if((uiGoalvalue1>=0)&&(uiGoalvalue1<=900))
        {
               GOON();
              if(motorfirst_flag==0)
              {
                    if(uiGoalvalue1>500)
                    {
                      FTM_PWM_Duty(FTM0,CH0,uiGoalvalue1);
                      delayms(500);
                      motorfirst_flag=1;
                    }
              }
              if(motorfirst_flag==1)
              FTM_PWM_Duty(FTM0,CH0,uiGoalvalue1);
        }
        else if(uiGoalvalue1>900)
        {
            GOON();
            uiGoalvalue1=900;
        }
        else if(uiGoalvalue1<0)
        {
            uiGoalvalue1=0;
            //shache();
            //FTM_PWM_Duty(FTM0,CH0,300);
           
        }
        else
        {
             //uiGoalvalue1=300;//printf("\n****�Ǹ�ֵ*****\r\n\n");
        }
        if( iError<=-30)
        {
              shache();
              FTM_PWM_Duty(FTM0,CH0,900);
              
              
        }
    
}