#include "main.h"

void nearAWP() {
    setMaxRPM(450);
    delay(100);
    setWingState(true);
    delay(500);
    baseTurn(-43);
    waitTurn(2000);
    delay(1000);
    setWingState(false);
    setMaxRPM(300);
    baseMove(38);
    runIntake(-127);
    waitMove(90000);
    delay(5000);
    runIntake(0);
}

void nearDeny() {
    
}

void farSafe() {
    runIntake(30);
    baseMove(46);
    waitMove(2000);
    delay(300);
    baseTurn(90);
    waitTurn(2000);
    runIntake(-127);
    delay(500);
    baseTurn(230);
    waitTurn(2000);
    delay(300);
    runIntake(127);
    baseMove(22);
    waitMove(2000);
    delay(500);
    baseMove(-22);
    waitMove(2000);
    baseTurn(90);
    waitTurn(2000);
    runIntake(-127);
    baseTimer(80, 80, 500);
}

void farRush() {

}