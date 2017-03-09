#pragma config(Sensor, dgtl1,  ArmEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port1,           ClawL,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           LiftLD,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           LiftRD,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           DriveL1,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           DriveL2,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           DriveL3,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           DriveR1,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           DriveR2,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           DriveR3,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          ClawR,         tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = false;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  bLCDBacklight = true;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  // User control code here, inside the loop
  bool closeSwitch = false;
	int toggle = 1;
	int clawTick = 0;

  wait1Msec(2000);  // 2 Second Delay

  //Clear Encoders
  SensorValue[ArmEncoder] = 0;

  while (true)
  {

    int value = SensorValue[ArmEncoder];
    displayLCDNumber(0, 0, value);

    int l = (vexRT[Ch3] + vexRT[Ch1]);
		int r = (vexRT[Ch3] - vexRT[Ch1]);

		float flForward = vexRT[Ch3];
		float flSide = vexRT[Ch1];

		int clawSpeed = 127;
		//Left
		motor[DriveL1] = l;
		motor[DriveL2] = l;
		motor[DriveL3] = l;
		//Right
		motor[DriveR1] = r;
		motor[DriveR2] = r;
		motor[DriveR3] = r;
		//Arm
		if (vexRT[Btn5U]) //Up
		{
			motor[LiftRD] = 127;
			motor[LiftLD] = 127;
		}
		else if (vexRT[Btn5D]) //Down
		{
			motor[LiftRD] = -127;
			motor[LiftLD] = -127;
		}
		else //Stop
		{
			motor[LiftRD] = 0;
			motor[LiftLD] = 0;
		}
		//Claw
		if (vexRT[Btn6U]) //Open
		{
			if(clawTick > 1000)
			{
				clawSpeed -= MIN(50, clawTick);
			}
			motor[ClawR] = clawSpeed;
			motor[ClawL] = clawSpeed;
			closeSwitch = false;
			clawTick += 1;

		}
		else if (vexRT[Btn6D]) //Close
		{
			if(clawTick > 1000)
			{
				clawSpeed -= MIN(50, clawTick);
			}
			motor[ClawR] = -clawSpeed;
			motor[ClawL] = -clawSpeed;
			//closeSwitch = true;
			clawTick += 1;

		}
		else //Stop
		{
			clawTick = 0;
			if (closeSwitch == false)
			{
				motor[ClawR] = 0;
				motor[ClawL] = 0;
			}

		if (vexRT(Btn7U))
		{
			motor[ClawR] = -127;
			motor[ClawL] = -127;
		}
			/*else
			{
				motor[ClawR] = -60;
				motor[ClawL] = -60;
			}
			*/
		}
  }
}
