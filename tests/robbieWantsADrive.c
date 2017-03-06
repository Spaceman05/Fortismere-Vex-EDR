#pragma config(Motor,  port1,           ClawR,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           DriveRD,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           DriveLD,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           DriveRS,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           DriveLS,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           LiftR1,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           LiftR2,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           LiftL1,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           LiftL2,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          ClawL,         tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	bool closeSwitch = false;

	while (true){
		int l = vexRT[Ch3] + vexRT[Ch1];
		int r = vexRT[Ch3] - vexRT[Ch1];
		//Left
		motor[DriveLD] = l;//Double
		motor[DriveLS] = l;//Single
		//Right
		motor[DriveRD] = r; //Double
		motor[DriveRS] = r;//Single
		//Arm
		if (vexRT[Btn5U]) //Up
		{
			motor[LiftR1] = 127;
			motor[LiftR2] = 127;
			motor[LiftL1] = 127;
			motor[LiftL2] = 127;
		}
		else if (vexRT[Btn5D]) //Down
		{
			motor[LiftR1] = -127;
			motor[LiftR2] = -127;
			motor[LiftL1] = -127;
			motor[LiftL2] = -127;
		}
		else //Stop
		{
			motor[LiftR1] = 0;
			motor[LiftR2] = 0;
			motor[LiftL1] = 0;
			motor[LiftL2] = 0;
		}
		//Claw
			if (vexRT[Btn6U]) //Open
		{
			motor[ClawR] = 127;
			motor[ClawL] = 127;
			closeSwitch = false;

		}
		else if (vexRT[Btn6D]) //Close
		{
			motor[ClawR] = -127;
			motor[ClawL] = -127;
			closeSwitch = true;

		}
		else //Stop
		{
			if (closeSwitch == false)
			{
				motor[ClawR] = 0;
				motor[ClawL] = 0;
			}
			else
			{
				motor[ClawR] = -60;
				motor[ClawL] = -60;
			}



		}
	}

}