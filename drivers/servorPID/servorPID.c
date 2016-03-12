#include"PID.h"
 
long int servoruiGoalvalue1=0,servorspeed;
typedef struct servorPID
{
	int  SetPoint; 			//  �趨Ŀ�� Desired Value
	long SumError;			//	����ۼ� 
		
	double  Proportion;     //  �������� Proportional Const
	double  Integral;       //  ���ֳ��� Integral Const
	double  Derivative;     //  ΢�ֳ��� Derivative Const
	double  Tams;            //  �������� 

	double LastError;         	//  Error[-1]
	double PrevError;          //  Error[-2]

} servorPID;
servorPID	 servorsPID;
servorPID	 *servorsptr = &servorsPID;

//�������ܣ�PID��ʼ��(pid���õ���RAM����)
void servorPIDInit(void)
{
    servorsptr->LastError  = 0;			//Error[-1]
    servorsptr->PrevError  = 0;			//Error[-2]
    servorsptr->Proportion = 0;			//�������� Proportional Const
    servorsptr->Integral   = 0;			//���ֳ��� Integral Const
    servorsptr->Derivative = 0;			//΢�ֳ��� Derivative Const
    servorsptr->SetPoint   = 0;
    servorsptr->SumError   = 0;
    servorsptr->Tams       = 0;
}

void servorPIDSetPoint(int setpoint)
{
	  servorsptr->SetPoint = setpoint;
}
int servorPIDGetSetpoint(void)
{	
          return(servorsptr->SetPoint);	
}
void servorPIDSetKp(double dKpp)
{	
          servorsptr->Proportion = dKpp;	
}
double servorPIDGetKp(void)
{	
          return(servorsptr->Proportion);	
}
void servorPIDSetKi(double dKii)
{
          servorsptr->Integral = dKii;
}
double servorPIDGetKi(void)
{
          return(servorsptr->Integral);	
}
void servorPIDSetKd(double dKdd)
{	
          servorsptr->Derivative = dKdd;	
}
double servorPIDGetKd(void)
{	
          return(servorsptr->Derivative);	
}
void servorPIDSetTams(double tams) 
{
          servorsptr->Tams = tams;
}

float servorIncPIDCalc(int NextPoint)    //��ҪPID���㺯��
{
  
      	servorPIDSetKp(0.85);  //���ñ���ϵ��
        servorPIDSetKi(0);    //���û���ϵ�� 0.71
        servorPIDSetKd(0); //0.26
        double servoriError, servoriIncpid;
        servoriError = servorsptr->SetPoint - NextPoint;
        servoriIncpid =servorsptr->Proportion * servoriError - servorsptr->Integral * servorsptr->LastError + servorsptr->Derivative * servorsptr->PrevError;
        servorsptr->PrevError = servorsptr->LastError;
  	servorsptr->LastError = servoriError;
  	return(servoriIncpid);
	 
}

double PIDservor()
{
        double rise=0;
        rise=servorIncPIDCalc(mid[30]);
        return(rise);
}
