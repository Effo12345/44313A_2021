#include "main.h"
#include "define.h"

void OnLeftButton()
{
	//If left button has been clicked before...
	if(auton == 1)
	{
		//...then run left 1 point autonomous
		auton = 3;
		pros::lcd::set_text(3, "1 point");
	}
	//If right button was clicked before this...
  else if(auton == 2)
  {
		//...then run right 1 point autonomous
		auton = 4;
    pros::lcd::set_text(2, "1 pt");
  }
	//If this is the first button being pressed...
	else if(auton == 0)
	{
		//..then set the value to left
		auton = 1;
		pros::lcd::set_text(2, "Left selected");
	}
}

void OnCenterButton()
{
	//If left button was clicked before this...
	if(auton == 1)
	{
		//Then run left 2 point autonomous
		auton = 6;
		pros::lcd::set_text(3, "2 point");
	}
	//If right button was pressed before this...
	else if(auton == 2)
	{
		//Then run right 2 point autonomous
		auton = 7;
		pros::lcd::set_text(3, "2 point");
	}
	//If this is the first button being pressed...
	else if(auton == 0)
	{
		//...then set the value to left
		auton = 5;
		pros::lcd::set_text(2, "Center selected");
		//pros::lcd::set_text(2, "Center selected \n 1 point");
		pros::lcd::set_text(3, "1 point");
	}
}

void OnRightButton()
{
	//Set the value to right (this button currently has no other function)
	auton = 2;
	pros::lcd::set_text(2, "Right selected");
}

float InToDeg(float in)
{
	return (in * inToDegCF);
}

void PID(int setpoint, const std::vector<pros::Motor> & motors)
{
	float kP = 0.5;
	float kI = 0.008;
	float kD = 0.015;

  int prevError;
	int error = 6;

  while(std::abs(error) > 3)
  {
    error = setpoint - encoder.get_value();
    int integral = integral + error;

    if(error == 0)
      integral = 0;

    if(integral > 12000)
		{
			integral = 0;
		}

    int derivative = error - prevError;
    prevError = error;
    float power = (error*kP) + (integral*kI) + (derivative*kD);

    for(pros::Motor m : motors) {m.move_velocity(power);}

		std::cout << error << "-";
		//pros::lcd::set_text(5, std::to_string(error));

		pros::delay(15);
  }

	for(pros::Motor m : motors) {m.move_velocity(0);}

	pros::lcd::set_text(5, "Setpoint: " + std::to_string(setpoint));
	pros::lcd::set_text(6, "Encoder value: " + std::to_string(encoder.get_value()));
}

void DriveTrain(int speed/*, int rotation*/)
{
	//driveFL.move_relative(rotation, speed);
	//driveBL.move_relative(rotation, speed);
	//driveFR.move_relative(rotation, speed);
	//driveBR.move_relative(rotation, speed);
	driveFL.move_velocity(speed);
	driveBL.move_velocity(speed);
	driveFR.move_velocity(speed);
	driveBR.move_velocity(speed);

	/*if(wait)
	{
		while(driveBL.is_stopped() != true || driveBR.is_stopped() != true) {
			pros::delay(20);
		}
	}*/
}


void Intakes(int speed/*, int rotation*/)
{
	//intakeL.move_relative(rotation, speed);
	//intakeR.move_relative(rotation, speed);
	intakeL.move_velocity(speed);
	intakeR.move_velocity(speed);

	/*if(wait)
	{
		while(intakeL.is_stopped() != true || intakeR.is_stopped() != true) {
			pros::delay(20);
		}
	}*/
}


void Outtakes(int speed1, int speed2)
{
	outB.move_velocity(speed1);
	outT.move_velocity(speed2);
}

void NewDriveTrain(float in, int speed, bool wait)
{
	std::vector<pros::Motor> motors {driveFL, driveBR, driveBL, driveFR};

	PID(InToDeg(in), motors);
}

void Turn(int rotation, int speed)
{
	imuSens.tare_rotation();

	if(rotation > 0)
	{
		driveFL.move_velocity(speed);
		driveFR.move_velocity(-speed);
		driveBL.move_velocity(speed);
		driveBR.move_velocity(-speed);

		while(imuSens.get_rotation() < rotation)
			pros::delay(10);
	}
	else
	{
		driveFL.move_velocity(-speed);
		driveFR.move_velocity(speed);
		driveBL.move_velocity(-speed);
		driveBR.move_velocity(speed);

		while(imuSens.get_rotation() > rotation)
			pros::delay(10);
	}

	driveFL.move_velocity(0);
	driveFR.move_velocity(0);
	driveBL.move_velocity(0);
	driveBR.move_velocity(0);
}

void NewIntakes(int rotation, int speed, bool wait)
{
	intakeL.tare_position();
	intakeR.tare_position();

	intakeL.move_relative(rotation, speed);
	intakeR.move_relative(rotation, speed);

	if(wait)
	{
		while(!((intakeL.get_position() < (rotation + 5)) && intakeL.get_position() > (rotation - 5))) {
			pros::delay(10);
		}
	}
}

void NewOuttakes(int rotation, bool wait)
{
	outB.tare_position();
	outT.tare_position();

	outB.move_relative(rotation, 200);
	outT.move_relative(rotation, 600);

	if(wait)
	{
		while(!((outB.get_position() < (rotation + 5)) && outT.get_position() > (rotation - 5))) {
			pros::delay(20);
		}
	}
}

void NewNewDriveTrain(float in)
{
	std::vector<pros::Motor> motors {driveBL, driveBR, driveFL, driveFR};

	PID(InToDeg(in /*- (in * .083)*/), motors);
}


void OnePtLR()
{
	NewDriveTrain(22, 100, true);

	if(auton == 3)
	{
		Turn(-125, 100);
	}
	else
	{
		Turn(125, 100);
	}

	NewDriveTrain(23.5, 100, false);
	NewIntakes(2160, 200, false);
	pros::delay(1500);
	NewOuttakes(6000, true);

	NewIntakes(-3600, 200, false);
	pros::delay(500);
	NewDriveTrain(-10, 100, true);
}

void OnePt()
{
	DriveTrain(-50);
	pros::delay(500);
	DriveTrain(0);
}

void TwoPt()
{
	NewDriveTrain(-3.0, 100, true);
	NewDriveTrain(15.0, 100, true);

	if(auton == 6)
	{
		Turn(-50, 100);
	}
	else
	{
		Turn(50, 100);
	}

	NewDriveTrain(6.0, 100, false);
	NewIntakes(3600, 200, false);
	NewOuttakes(3600, true);

	NewDriveTrain(-3.0, 100, true);
	NewIntakes(1080, -200, true);

	/*DriveTrain(-50);
	pros::delay(500);
	DriveTrain(0);

	DriveTrain(100);
	pros::delay(1400);
	DriveTrain(0);


	pros::delay(200);
	if(auton == 6)
	{
		Turn(-50, 100);
	}
	else
	{
		Turn(50, 100);
	}

	pros::delay(1000);
	Intakes(200);
	Outtakes(600, 200);
	DriveTrain(100);
	pros::delay(900);
	DriveTrain(0);

	pros::delay(1000);
	DriveTrain(-50);
	pros::delay(250);
	DriveTrain(50);
	pros::delay(250);
	DriveTrain(0);

	pros::delay(1000);
	DriveTrain(-50);
	pros::delay(250);
	DriveTrain(50);
	pros::delay(250);
	DriveTrain(0);

	//Outtakes(600, 200);
	pros::delay(1000);
	Intakes(0);
	pros::delay(2000);
	Outtakes(0, 0);

	//DriveTrain(75);

	//Intakes(200);
	//pros::delay(300);
	//DriveTrain(0);
	//pros::delay(1200);
	//Intakes(0);

	DriveTrain(-150);
	pros::delay(800);
	DriveTrain(0);

	Intakes(-200);
	Outtakes(600, 200);
	pros::delay(2000);
	Intakes(0);
	Outtakes(0, 0);*/
}

void None()
{
	pros::lcd::set_text(2, "No auton selected");
	/*NewDriveTrain(12.0, 100, true);
	Intakes(200);
	pros::delay(9000);
	Intakes(0);*/

	NewNewDriveTrain(37);
}
