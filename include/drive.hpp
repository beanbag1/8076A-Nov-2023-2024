#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

void set(double left, double right);

double getEncdL();

double getEncdR();

void baseTimer(int left, int right, int time);

void setMaxRPM(double max);

void setTurnConstants(double kp, double kd);

void baseMove(double dist);

void baseTurn(double bearing);

void waitMove(double cutoff);

void waitTurn(double cutoff);

void baseControl(void* ignore);


#endif