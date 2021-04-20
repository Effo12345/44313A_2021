#include "main.h"
#include "define.h"
#include "functions.h"

//lv_obj_t * myButton;



/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	//pros::lcd::set_text(1, "Hello PROS User!");
	pros::lcd::register_btn0_cb(OnLeftButton);
	pros::lcd::register_btn1_cb(OnCenterButton);
	pros::lcd::register_btn2_cb(OnRightButton);

	imuSens.reset();
	encoder.reset();
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
	autonPointers[auton]();

	//move_voltage(12000)
	//move_velocity
	//move_relative(how far to go (degrees), how fast to go (rpm))
	//move_absolute
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
void opcontrol()
{
	while (true)
	{
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 0,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 2);

		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		driveFL.move(left);
		driveBL.move(left);
		driveFR.move(right);
		driveBR.move(right);

		if(master.get_digital(DIGITAL_L1))
		{
		 	Intakes(600); //600 because the motor moves at 600 rpm
		}
		else if(master.get_digital(DIGITAL_L2))
		{
			Intakes(-600);
		}
		else
		{
			Intakes(0);
		}

		if(master.get_digital(DIGITAL_R1))
		{
			Outtakes(200, 600);
		}
		else if(master.get_digital(DIGITAL_R2))
		{
			Outtakes(-200, -600);
		}
		else
		{
			Outtakes(0, 0);
		}

		//frontLeftWheelMotor = backLeftWheelMotor = left;
		//frontRightWheelMotor = backRightWheelMotor = right;
		pros::delay(20);
	}
}
