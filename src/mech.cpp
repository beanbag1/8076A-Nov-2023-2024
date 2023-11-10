#include "main.h"

#define catakP 0.08
#define cataThreshold 800

cataControlType cataControlState = automatic;

double cataTarg = 0;
bool firing = false;
bool cataDown = false;
double cataMin = 55;

void cataControl(void *ignore) {
    Motor cata (12, E_MOTOR_GEAR_RED, true);
    cata.set_brake_mode(E_MOTOR_BRAKE_COAST);
    Rotation cataRot (20, true);
    double cataCurr = 0;
    double error = 999;

    while (true) {
        cataCurr = cataRot.get_angle();
        if (cataCurr >= cataTarg) {
            error = cataCurr - cataTarg;
            error = abs(error) + 0;
        } else if (cataCurr < cataTarg) {
            error = cataCurr - cataTarg + 36000;
            error = abs(error) + 0;
        }

        if (error < cataThreshold) {
            cataDown = true;
        }

        if ((cata.get_actual_velocity() < 20) && !cataDown) {
            cataMin += 0.2;
        } // to help stalls

        if (cataDown || cataControlState == pause) {
            cata.move(0);
        } else if ((error*catakP) < cataMin) {
            cata.move(cataMin);
        } else {
            cata.move(error*catakP);
        }
        if (firing && cataControlState != pause) {
            cata.move(127);
            delay(500);
            firing = false;
            cataDown = false;
            if (cataControlState == automatic) cataMin = 55;
            else cataMin = 10;
        }
        delay(10);
    }
}

void setCataTarg(double targ) {
    if (targ != cataTarg) {
        cataDown = false;
    }
    cataTarg = targ;
}

void fireCata() {
    firing = true;
}

bool cataReady() {
    return cataReady;
}

void setCataControlState(cataControlType state) {
    cataControlState = state;
    if (state == automatic) {
        cataMin = 55;
        setCataTarg(0);
    } else if (state == climb) {
        cataMin = 10;
        setCataTarg(9000);
    } else if (state == score) {
        cataMin = 10;
        setCataTarg(2000);
    }
}

void runIntake(double speed) {
    Motor intake(13, false);
    intake.move(speed);
}

ADIDigitalOut wings (7, false);
bool wingState = false;

void setWingState(bool state) {
    wingState = state;
    wings.set_value(wingState);
}