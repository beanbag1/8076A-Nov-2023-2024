#include "main.h"

void nearAWP() {
    setMaxRPM(600);
    setTurnConstants(1, 0);
    delay(100);

    baseMove(-18);
    waitMove(2000);
    baseTurn(45);
    waitTurn(1000);
    baseTimer(-70, -70, 1000);
    baseMove(11);
    waitMove(2000);
    baseTurn(0);
    waitTurn(1000);
    baseMove(18);
    waitMove(1000);

    setWingState(true);
    delay(500);
    baseTimer(-40, 40, 290);
    delay(1000);
    setMaxRPM(300);
    baseMove(36);
    runIntake(-127);
    delay(500);
    setWingState(false);
    waitMove(90000);
    delay(5000);
    runIntake(0);
}

void nearDeny() {
    setMaxRPM(600);
    runIntake(127);
    baseMove(40);
    waitMove(2000);
    delay(500);
    baseMove(-10);
    waitMove(2000);
    baseTurn(-110);
    waitTurn(2000);
    setCataControlState(score);
    runIntake(60);
    delay(500);
    setTurnConstants(1, 0);
    baseTurn(-170);
    waitTurn(2000);
    setTurnConstants(0.7, 1);
    baseMove(28);
    waitMove(2000);
    baseMove(-40);
    waitMove(2000);
    setTurnConstants(1, 0);
    baseTurn(-100);
    waitTurn(2000);
    runIntake(-127);
    baseTimer(90, 90, 1000);
    runIntake(0);
    baseTimer(-40, -40, 500);
    baseTurn(0);
    waitTurn(2000);
    baseMove(-52);
    waitMove(1000);
    baseTurn(80);
    waitTurn(2000);
    baseTimer(-40, -40, 500);

}

void farSafe() {
    setMaxRPM(450);
    setTurnConstants(0.7, 0);
    runIntake(30);
    baseMove(42);
    waitMove(2000);
    baseTurn(90);
    waitTurn(500);
    runIntake(-127);
    baseMove(-5);
    waitMove(500);
    baseTurn(235);
    waitTurn(2000);
    runIntake(80);
    baseMove(22);
    waitMove(2000);
    baseTurn(190);
    waitTurn(500);

    baseMove(-14);
    waitMove(1000);
    setWingState(true);
    runIntake(40);
    baseTurn(275);
    waitTurn(2000);
    baseTimer(-80, -80, 600);
    baseMove(10);
    waitMove(700);
    setWingState(false);
    baseTurn(90);
    waitTurn(2000);
    runIntake(-127);
    baseTimer(80, 80, 600);
    runIntake(0);
    baseTimer(-40, -40, 500);
    delay(200);
    baseTurn(270);
    waitTurn(2000);

    // baseMove(-22);
    // waitMove(1000);
    // baseTurn(90);
    // waitTurn(5000);
    // runIntake(-127);
    // baseTimer(80, 80, 500);
    // baseMove(-24);
    // waitMove(1000);
    // baseTurn(-45);
    // waitTurn(2000);
    // runIntake(127);
    // baseMove(15);
    // waitMove(2000);
    // setMaxRPM(600);
    // baseTurn(-90);
    // waitTurn(500);
    // setWingState(true);
    // baseTimer(-80, -80, 1000);
    // baseMove(10);
    // waitMove(2000);
    // baseTurn(90);
    // waitTurn(2000);
    // runIntake(-127);
    // baseTimer(80, 80, 1000);
    // runIntake(0);
    // baseTimer(-40, -40, 500);

}

void farRush() {

}