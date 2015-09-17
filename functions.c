/**
 * @file functions.c
 * @brief This file contains all functions to be used by
 * the competition code.
 *
 * @warning DO NOT compile this file
 * by itself, it will not work. Instead, save it
 * and compile main.c
 *
 * Also, you must include your motor and sensor setup somewhere in this file.
 *
 * @author	 Sean Kelley      sgtkode01@gmail.com
 * @author   Bernard Suwirjo  bsuwirjo@gmail.com
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Table of Contents
//
//			Function Name              Arguments  *x is defualt for motor speed
//
// 			drive()--------------------bool half
//			clearMotor()---------------None
//			motorcheck()---------------None
//			fullStop()-----------------int x=118,int direction=0, bool fancy=false
//			forwardSeconds()-----------float s, float x=118
//			backwardSeconds()----------float s, float x=118
//			fancyTurnRightDegrees()----int degrees, bool forward=true, int x=80
//			fancyTurnLeftDegrees()-----int degrees, bool forward=true, int x=80
//			turnRightDegrees()---------float degree, float x=90
//			turnLeftDegrees()----------float degree, float x=90
//			turnRightSeconds()---------float seconds, float x=118
//			turnLeftSeconds()----------float seconds, float x=118
//
//
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 DRIVETRAIN
//
/////////////////////////////////////////////////////////////////////////////////////////

/**
* Gives drive control to VexNET controller
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @param  half  determines if motors should be running at half speed
*/
void drive(bool half=false)
{
			if (half==false)//Check if drive toggles half speed.
			{
				motor[BR] = vexRT[Ch2]; //give drive direct control.
				motor[FR] = vexRT[Ch2];
				motor[BL] = vexRT[Ch3];
				motor[FL] = vexRT[Ch3];
			}
			else if(half ==true)
			{
				motor[BR] = vexRT[Ch2]/3;//give drive control but all motor maxes are a third of their orignal max.
				motor[FR] = vexRT[Ch2]/3;
				motor[BL] = vexRT[Ch3]/3;
				motor[FL] = vexRT[Ch3]/3;
			}
}


/**
* Clears all the motors
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*/
void clearMotor()
{
	//Set all motor values to 0
	motor[FR]=0;
	motor[BR]=0;
	motor[FL]=0;
	motor[BL]=0;
}

/**
* Runs each motor for 1.5 seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*/
void motorcheck()
{
	motor[FR]=118;//Set individual motor
	wait(1.5); //Wait 1.5 seconds
	clearMotor(); //clear motor(s)
	motor[BR]=118;
	wait(1.5);
	clearMotor();
	motor[FL]=118;
	wait(1.5);
	clearMotor();
	motor[BL]=118;
	wait(1.5);
	clearMotor();
}

/**
* Completely stops all motors without drift
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @param x speed of motors
* @param direction 1=forwards, 2=backwards
* @param fancy use special stuff to stop???
*
*/
void fullStop(int x=118,int direction=0, bool fancy=false)
{
	if(fancy)
	{
		if(direction==1)
		{
			int FR = x;
			int FL = 0;
			int BR = x;
			int BL = 0;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
		else if(direction==2)
		{
			int FR = 0;
			int FL = x;
			int BR = 0;
			int BL = x;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
	}
	else
	{
		if(direction==1)
		{
			int FR = x;
			int FL = -x;
			int BR = x;
			int BL = -x;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
		else if(direction==2)
		{
			int FR = -x;
			int FL = x;
			int BR = -x;
			int BL = x;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
		else
		{
			int FR = x;
			int FL = x;
			int BR = x;
			int BL = x;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
	}
}

/**
* Moves bot forward for a given amount of seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @params  s  amount of seconds to move forward
*	@params  x  speed of motors
*
*/
void forwardSeconds(float s,float x=118)
{
	//Set all motors to target value
  motor[FL]=x;
	motor[FR]=x;
	motor[BL]=x;
	motor[BR]=x;
	wait1Msec(s*1000);//Wait given amount of time
	fullStop(x);//stop <-- kind of interchangeble with clearMotor()
}

/*
* Moves bot backward for a given amount of seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @params  s  amount of seconds to move backward
*	@params  x  speed of motors
*
*/
void backwardSeconds(float s, float x=118)
{
	//Set all motors to negative target value
  motor[FL]=-x;
	motor[FR]=-x;
	motor[BL]=-x;
	motor[BR]=-x;
	wait1Msec(s*1000);//Wait given amount of time
	fullStop(x); //Stop
}

/**
*
* Locks left side motors with PI loop
*
* @author Sean Kelley  sgtkode01@gmail.com
*
*/
task lockLeftSide()
{
	float target = 0;
	float pGain = .3;
	float iGain = .02;
	float error = target-SensorValue[encoderLeft];
	float errorSum=0;
	while(true){
		error=target-SensorValue[encoderLeft];
		errorSum+=error;
		motor[FL] = error*pGain+errorSum*iGain;
		  motor[BL] = error*pGain+errorSum*iGain;
	}
}
*/
/**
*
* Locks right side motors with PI loop
*
* @author Sean Kelley  sgtkode01@gmail.com
*
*/
task lockRightSide()
{
	float target = 0;
	float pGain = .3;
	float iGain = .02;
	float error = target-SensorValue[encoderRight];
	float errorSum=0;
	while(true){
		error=target-SensorValue[encoderRight];
		errorSum+=error;
		motor[FR] = error*pGain+errorSum*iGain;
	  motor[BR] = error*pGain+errorSum*iGain;
	}
}

/*
* Turns bot right only using left side motors
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @params   degrees   amount of degrees to turn right
* @params   forward   boolean if bot is turning forward or backward
* @params   x         speed of motors
*
*/
void fancyTurnRightDegrees(int degrees, bool forward=true, int x=80)
{
	// reset encoders
	degrees=degrees*10;
	// reset gyro
	//gyro takes degrees from 0-3600, so we multiply by 10 to get a gyro processable number
	SensorValue[gyro]=0;
	// turn forwards or backwards based on forward boolean
	if(forward)
	{
		while(abs(SensorValue[gyro]) < degrees) //While the gyro value is less than the target perform code below
		{
			//Set only the left side motors to the target value
			motor[FL] = x;
		  motor[BL] = x;
		}
		//breifly set the motor values opposite to ensure an actual stop
		motor[FL] = -10;
		motor[BL] = -10;
		wait1Msec(150);
		motor[FL] = 0;
		motor[BL] = 0;
	}
	else
	{
		while(abs(SensorValue[gyro]) < degrees)
		{
			//Set only the left side motors to the negative target value
			motor[FL] = -x;
		  motor[BL] = -x;
		}
		//Ensure actual stop
		motor[FL] = 10;
	  motor[BL] = 10;
	  wait1Msec(150);
	  motor[FL] = 0;
	  motor[BL] = 0;
	}

}

/*
* Turns bot left only using left side motors
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @params   degrees   amount of degrees to turn left
* @params   forward   boolean if bot is turning forward or backward
* @params   x         speed of motors
*
*/
void fancyTurnLeftDegrees(int degrees, bool forward=true, int x=80)
{
	// reset encoders
	degrees=degrees*10;
	// reset gyro
	//gyro takes degrees from 0-3600, so we multiply by 10 to get a gyro processable number
	SensorValue[gyro] = 0;
	if(forward)
	{
		while(abs(SensorValue[gyro]) < degrees)
		{
			//Set only the right side motors to the target value
			motor[FR] = x;
		  motor[BR] = x;
		}
		//Ensure actual stop
		motor[FR] = -10;
		motor[BR] = -10;
		wait1Msec(150);
		motor[FR] = 0;
		motor[BR] = 0;
	}
	else
	{
		while(abs(SensorValue[gyro]) < degrees)
		{
			//Set only the right side motors to the negative target value
			motor[FR] = -x;
		  motor[BR] = -x;
		}
		//Ensure actual stop
		motor[FR] = 10;
		motor[BR] = 10;
		wait1Msec(150);
		motor[FR] = 0;
		motor[BR] = 0;
	}
}






/**
* Turns bot right a given amount of degrees
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @params  degree  amount of degrees to turn right
*	@params	 x       speed of motors
*
*/
void turnRightDegrees(float degree, float x=90)
{
	//Reset gyro
	SensorValue[gyro]=0;
	//gyro takes degrees from 0-3600, so we multiply by 10 to get a gyro processable number
	degree=degree*10;
	//We want to slow down when we approach the target, so we calculate a first turn segment as 60% of the total
	float first=degree*.6;
	while(abs(SensorValue[gyro]) < first) //Turn the first 60%
	{
			//Since it's turn right, we want to set right motors backwards and left motors forward.
			motor[FL] = x;
    	motor[FR] = -x;
    	motor[BL] = x;
    	motor[BR] = -x;
	}
	while(abs(SensorValue[gyro]) <degree) //Turn the remainin amount.
	{
		//We don't want the motors to run too slow, so we set a a safety net. The motor can't have a power less than 40.
		if(x*.35<40)//If 35% of the motor power is less than 40, set the power to 40.
		{
			motor[FL] = 40;
    	motor[FR] = -40;
    	motor[BL] = 40;
    	motor[BR] = -40;
		}
		else //If not set it to 35%
		{
				motor[FL] = x*.35;
	    	motor[FR] = -x*.35;
	    	motor[BL] = x*.35;
	    	motor[BR] = -x*.35;
    }
	}
	clearMotor();
}

/**
* Turns bot left a given amount of degrees
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @params  degree  amount of degrees to turn left
*	@params	 x       speed of motors
*
*/
void turnLeftDegrees(float degree, float x=90)
{
	//Reset gyro
	SensorValue[gyro]=0;
	//gyro takes degrees from 0-3600, so we multiply by 10 to get a gyro processable number
	degree=degree*10;
	//We want to slow down when we approach the target, so we calculate a first turn segment as 60% of the total
	float first=degree*.6;
	while(abs(SensorValue[gyro]) < first)
	{
			//Since it's turn left, we want to set right motors forwards and left motors backwards.
				motor[FL] = -x;
  	    motor[FR] = x;
  	    motor[BL] = -x;
  	    motor[BR] = x;
	}
	while(abs(SensorValue[gyro]) < degree)
	{
		//We don't want the motors to run too slow, so we set a a safety net. The motor can't have a power less than 40.
		if(x*.35<40)//If 35% of the motor power is less than 40, set the power to 40.
		{
				motor[FL] = -40;
		    motor[FR] = 40;
		    motor[BL] = -40;
		    motor[BR] = 40;
		}
		else //If not set it to 35%
		{
				motor[FL] = -x*.35;
  	    motor[FR] = x*.35;
  	    motor[BL] = -x*.35;
  	    motor[BR] = x*.35;
    }
	}
	clearMotor();
}


/**
* Turns bot right a given amount of seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @params  seconds   amount of seconds to turn right
* @params	 x         speed of motors
*
*/
void turnRightSeconds(float seconds, float x=118)
{
	//Since turn right, we want to set left motors forwards and right motors backwards.
	motor[FL]=x;
	motor[BL]=x;
	motor[FR]=-x;
	motor[BR]=-x;
	wait1Msec(seconds*1000); //Wait desired amount of time
	fullStop(); //Stop
}

/**
* Turns bot left a given amount of seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @params  seconds   amount of seconds to turn left
* @params	 x         speed of motors
*
*/
void turnLeftSeconds(float seconds, float x=118)
{
	//Since turn left, we want to set the right motors forward and the left motors backwards
	motor[FL] = -x;
	motor[BL] = -x;
	motor[FR] = x;
	motor[BR] = x;
	wait1Msec(seconds*1000); //Wait desired amount of time
	fullStop(); //Stop
}
