#ifndef _PID_H_
#define _PID_H_
#include "include.h"
void PIDInit(void);
void PIDSetPoint(int setpoint);
int PIDGetSetpoint(void);
void PIDSetKp(double dKpp);
double PIDGetKp(void);
void PIDSetKi(double dKii);
double PIDGetKi(void);
void PIDSetKd(double dKdd);
double PIDGetKd(void);
void PIDSetTams(double tams);
float IncPIDCalc(int NextPoint);    //重要PID计算函数
void PIDmotor();

#endif