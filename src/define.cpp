#include "main.h"
#include "functions.h"

//Motor and controller delcarations (with port declaration)
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor driveFL(11);
pros::Motor driveBL(12);
pros::Motor driveFR(19, true);
pros::Motor driveBR(20, true);
pros::Motor intakeL(1);
pros::Motor intakeR(10, true);
pros::Motor outB(9);
pros::Motor outT(2, MOTOR_GEARSET_6, true);

pros::Imu imuSens(18);
pros::Distance distSens(5);
pros::ADIEncoder encoder (1, 2, false);

//Global variable delcarations (with initialized values)
typedef void(*FnPtr) ();
void (*onePtLR) (){&OnePtLR}, (*onePt) (){&OnePt}, (*twoPt) (){&TwoPt}, (*none) (){None};
FnPtr autonPointers[] {none, none, none, onePtLR, onePtLR, onePt, twoPt, twoPt};
int auton = 0;

//float pi = 3.14159;
double inToDegCF = 26.96274;
