#include "main.h"
#include "define.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern void OnLeftButton();
extern void OnCenterButton();
extern void OnRightButton();

extern float InToDeg(float in);

extern void DriveTrain(int speed/*, int rotation*/);
extern void Intakes(int speed/*, int rotation*/);
extern void Turn(int speed, int delay);
extern void Outtakes(int speed1, int speed2);

extern void OnePtLR();
extern void OnePt();
extern void TwoPt();
extern void None();

#endif
