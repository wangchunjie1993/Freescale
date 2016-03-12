#ifndef _SERVORPID_H_
#define _SERVORPID_H_
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
double PIDservor();
extern s16 mid[60];

#endif