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
int rotate(int degrees)
{
	clearEncoders(); //customary first code for every function using encoders
	/*
		392/90 = x/degrees // degrees * 392 = 90x // (degrees * 392)/ 90  = x
	*/
	rotTicks = (degrees * turnTicks)/90;

	if ((rotTicks + rotTicks)/ 2 == rotTicks) //if rotTicks is positive
	{
		while(((nMotorEncoder[rightMotor]) <= rotTicks) && (nMotorEncoder[leftMotor] >= -(rotTicks)))
		{
		motor[rightMotor] = turnSpeed;
		motor[leftMotor] = -turnSpeed;
		}
	}
	return 0;
}

task main()
{
	rotate(180);


}
