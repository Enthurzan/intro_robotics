#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port8,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           clawMotor,     tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
#pragma config(DatalogSeries, 0, "rightIEM", Sensors, Sensor, I2C_1, 50)
#pragma config(DatalogSeries, 1, "leftIEM", Sensors, Sensor, I2C_2, 50)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int turnTicks = 392;
float rotTicks;
int turnSpeed = 50;


void clearEncoders ()
{
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;

}

/*------------------------------------------------------

	 Super Easy to use rotating (tank turn) function:
	 first parameter is the degrees you want to rotate
	 second parameter is the speed you want do this
	 uses the absolute value of what the motorEncoders read to
	 determine PID and straightening
	 Program is smarter in that it can negative if the input parameter is negative by using the abs() cmd
	 to see if a + abs(a) is 0 (if its negative) or not (if its positive)

------------------------------------------------------*/

void rotate(int degrees, int speed)
{
	clearEncoders(); //customary first code for every function using encoders
	/*
		392/90 = x/degrees // degrees * 392 = 90x // (degrees * 392)/ 90  = x
	*/
	rotTicks = abs((degrees * turnTicks)/90); //finds the absolute value so ticks is always positive

	while((abs(nMotorEncoder[rightMotor]) + abs(nMotorEncoder[leftMotor]))/2 < rotTicks )
	if (abs(nMotorEncoder[leftMotor]) > abs(nMotorEncoder[rightMotor])){
		if (degrees + abs(degrees) == 0){ //so if the number is negative
			motor[leftMotor] = speed++;
			motor[rightMotor] = speed++;
		}
		else if (degrees + abs(degrees) != 0){
			motor[leftMotor] = speed--;
			motor[rightMotor] = speed--;
			/*
				logically this makes since because on a left turn, the left motor is going backwards
			so 
	}
	else if (abs(nMotorEncoder[leftMotor]) < abs(nMotorEncoder[rightMotor])){
		if (degrees + abs(degrees) == 0){ //if number is negative
			motsubtracting is going to make it go faster and vise versa for the right motor

			*/
		}
or[leftMotor] = speed--;
			motor[rightMotor] = speed--;

	}
		else if (degrees + abs(degrees) != 0){ //if number is positive
			motor[leftMotor] = speed++;
			motor[rightMotor] = speed++;

		}
	}
	else {
		motor[leftMotor] = speed;
		motor[rightMotor] = speed;

	}

}

task main()
{
	rotate(180);


}
