#include "main.h"

Motor L1 (9, E_MOTOR_GEAR_BLUE, false);
Motor L2 (8, E_MOTOR_GEAR_BLUE, false);
Motor L3 (7, E_MOTOR_GEAR_BLUE, false);
Motor R1 (4, E_MOTOR_GEAR_BLUE, true);
Motor R2 (3, E_MOTOR_GEAR_BLUE, true);
Motor R3 (2, E_MOTOR_GEAR_BLUE, true);

Motor_Group drive ({L1, L2, L3, R1, R2, R3});

double abscap(double a, double b) {
    if (a > b) return b;
    else if (a < -b) return -b;
    else return a;
}

void set(double left, double right) {
    L1.move(left);
	L2.move(left);
	L3.move(left);
	R1.move(right);
	R2.move(right);
	R3.move(right);
}

double getEncdL() {
    return (L1.get_position() + L2.get_position() + L3.get_position())/3;
}
double getEncdR() {
    return (R1.get_position() + R2.get_position() + R3.get_position())/3;
}

IMU inertial (19);

#define kPstraight 0.12
#define kDstraight 0.1
#define kPturn 1.3
#define kDturn 0
#define slewPow 2.5
#define inchesPerDeg 0.02399827721/1.2

bool turning = false;
bool manual = false;
double outputL = 0, outputR = 0;
double targEncdL = 0, targEncdR = 0, targBearing = 0;
double errorEncdL = 99, errorEncdR = 99, errorBearing = 999;
double perrorEncdL = 0, perrorEncdR = 0, perrorBearing = 0;
double maxV = 127;

void baseTimer(int left, int right, int time) {
    manual = true;
    outputL = left;
    outputR = right;
    delay(time);
    manual = false;
    targEncdL = getEncdL();
    targEncdR = getEncdR();
    targBearing = inertial.get_rotation();
    perrorEncdL = 0, perrorEncdR = 0, perrorBearing = 0;
}

void setMaxRPM(double max) {
    maxV = max/600*127;
}

void baseMove(double dist) {
    turning = false;
    targEncdL += dist/inchesPerDeg;
    targEncdR += dist/inchesPerDeg;
    delay(200);
}

void baseTurn(double bearing) {
    turning = true;
    targBearing = bearing;
    delay(100);
}

void waitMove(double cutoff) {
    double start = millis();
    while (((fabs(errorEncdL) > 15) || (fabs(errorEncdR) > 15)) && millis() < (start + cutoff)) {
        delay(10);
    }
    drive.tare_position();
    targEncdL = 0;
    targEncdR = 0;
    delay(200);
}

void waitTurn(double cutoff) {
    double start = millis();
    while ((errorBearing > 1) && millis() < (start + cutoff)) {
        delay(10);
    }
    drive.tare_position();
    targEncdL = 0;
    targEncdR = 0;
    delay(200);
}

void baseControl(void* ignore) {
    drive.tare_position();
    drive.set_brake_modes(MOTOR_BRAKE_HOLD);
    double targL = 0, targR = 0;
    while (competition::is_autonomous()) {
        if (turning) {
            errorBearing = targBearing - inertial.get_rotation();
            targL = errorBearing * kPturn + (errorBearing - perrorBearing) * kDturn;
            targR = -targL;
            perrorBearing = errorBearing;
        } else if (!manual) {
            errorEncdL = targEncdL - getEncdL();
            errorEncdR = targEncdR - getEncdR();
            double combinedError = (errorEncdL + errorEncdR)/2;
            targL = combinedError * kPstraight + (errorEncdL - perrorEncdL) * kDstraight;
            targR = combinedError * kPstraight + (errorEncdR - perrorEncdR) * kDstraight;
            perrorEncdL = errorEncdL;
            perrorEncdR = errorEncdR;
        }

        if (!manual) {
            double changeL = targL - outputL;
            outputL += abscap(changeL, slewPow);
            double changeR = targR - outputR;
            outputR += abscap(changeR, slewPow);
        } 
        // else if (turning && !manual) {
        //     outputL = targL;
        //     outputR = targR;
        // }

        outputL = abscap(outputL, maxV);
        outputR = abscap(outputR, maxV);

        set(outputL, outputR);
        delay(10);
    }
}