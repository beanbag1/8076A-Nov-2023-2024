#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void controllerControl(void *ignore) {
	Controller master (E_CONTROLLER_MASTER);
	master.clear();
	while (true) {
		master.print(0, 0, "Cata: %s", cataReady() ? "Ready    " : "Loading");
		delay(50);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	Task cataTask (cataControl);
	setCataTarg(0);
	Task controllerTask(controllerControl);
	IMU inertial (19);
	inertial.reset(true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	Task baseTask (baseControl);
	farSafe();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	Controller master(pros::E_CONTROLLER_MASTER);
	Motor L1 (9, E_MOTOR_GEAR_BLUE, false);
	Motor L2 (8, E_MOTOR_GEAR_BLUE, false);
	Motor L3 (7, E_MOTOR_GEAR_BLUE, false);
	Motor R1 (4, E_MOTOR_GEAR_BLUE, true);
	Motor R2 (3, E_MOTOR_GEAR_BLUE, true);
	Motor R3 (2, E_MOTOR_GEAR_BLUE, true);

	Motor intake(13, false);

	int currentCataState = 1;
	#define left_curve_scale 6
	bool currWingState = false;

	while (true) {
		double throttle = (powf(2.718, -(left_curve_scale / 10)) + powf(2.718, (fabs(double(master.get_analog(ANALOG_RIGHT_Y))) - 127) / 10) * (1 - powf(2.718, -(left_curve_scale / 10)))) * master.get_analog(ANALOG_RIGHT_Y);
		double yaw = (powf(2.718, -(left_curve_scale / 10)) + powf(2.718, (fabs(double(master.get_analog(ANALOG_LEFT_X))) - 127) / 10) * (1 - powf(2.718, -(left_curve_scale / 10)))) * master.get_analog(ANALOG_LEFT_X);

		L1.move(throttle + yaw);
		L2.move(throttle + yaw);
		L3.move(throttle + yaw);
		R1.move(throttle - yaw);
		R2.move(throttle - yaw);
		R3.move(throttle - yaw);

		if (master.get_digital(DIGITAL_L1)) {
			intake.move(127);
		} else if (master.get_digital(DIGITAL_L2)) {
			intake.move(-127);
		} else intake.move(20);
		
		if (master.get_digital(DIGITAL_R1)) {
			fireCata();
		}

		if (master.get_digital_new_press(DIGITAL_A)) {
			currentCataState++;
			if (currentCataState > 3) {
				currentCataState = 1;
			}
			switch (currentCataState) {
				case 1:
				setCataControlState(automatic);
				break;

				case 2:
				setCataControlState(score);
				break;

				case 3:
				setCataControlState(climb);
				break;
			}
		}

		if (master.get_digital_new_press(DIGITAL_R2)) {
			currWingState = !currWingState;
			setWingState(currWingState);
		}
		delay(10);
	}
}
