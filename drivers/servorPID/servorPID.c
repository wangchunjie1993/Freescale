#include"PID.h"
 
long int servoruiGoalvalue1=0,servorspeed;
typedef struct servorPID
{
	int  SetPoint; 			//  设定目标 Desired Value
	long SumError;			//	误差累计 
		
	double  Proportion;     //  比例常数 Proportional Const
	double  Integral;       //  积分常数 Integral Const
	double  Derivative;     //  微分常数 Derivative Const
	double  Tams;            //  采样周期 

	double LastError;         	//  Error[-1]
	double PrevError;          //  Error[-2]

} servorPID;
servorPID	 servorsPID;
servorPID	 *servorsptr = &servorsPID;

//函数功能：PID初始化(pid所用到的RAM清零)
void servorPIDInit(void)
{
    servorsptr->LastError  = 0;			//Error[-1]
    servorsptr->PrevError  = 0;			//Error[-2]
    servorsptr->Proportion = 0;			//比例常数 Proportional Const
    servorsptr->Integral   = 0;			//积分常数 Integral Const
    servorsptr->Derivative = 0;			//微分常数 Derivative Const
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

float servorIncPIDCalc(int NextPoint)    //重要PID计算函数
{
  
      	servorPIDSetKp(0.85);  //设置比例系数
        servorPIDSetKi(0);    //设置积分系数 0.71
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
