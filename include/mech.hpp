#ifndef _MECH_HPP_
#define _MECH_HPP_

enum cataControlType {
    automatic,
    pause,
    climb,
    score
};

void cataControl(void *ignore);

void setCataTarg(double targ);

void fireCata();

bool cataReady();

void setCataControlState(cataControlType state);

void runIntake(double speed);

void setWingState(bool state);

#endif