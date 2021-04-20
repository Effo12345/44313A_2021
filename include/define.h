#include "main.h"

#ifndef DEFINE_H
#define DEFINE_H

extern pros::Controller master;
extern pros::Motor driveFL;
extern pros::Motor driveBL;
extern pros::Motor driveFR;
extern pros::Motor driveBR;
extern pros::Motor intakeL;
extern pros::Motor intakeR;
extern pros::Motor outB;
extern pros::Motor outT;

extern pros::Imu imuSens;
extern pros::Distance distSens;
extern pros::ADIEncoder encoder;

//extern bool left;
//extern bool right;

//extern bool onePtLR;
//extern bool onePT;
//extern bool twoPT;

//extern bool useRightAuto;

extern double inToDegCF;
typedef void(*FnPtr) ();
extern void (*onePtLR) (), (*onePt) (), (*twoPt) (), (*none) ();
extern FnPtr autonPointers[];

extern int auton;

#endif
