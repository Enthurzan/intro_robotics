#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port8,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           clawMotor,     tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)

//Distance Variables
int rotationTicks = 351; //number of encoder ticks in one rotation
float wheelDistance = 4*PI; //distance that one rotation goes
int tileWidth = 22; //width of tile in inches
int turnTicks = 392; //number of ticks for a 90 degree turn
float firstForward; //distance in ticks that is calculated later

void clearEncoders(){ //clears Encoders values
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;

}

void forward (int speed, int distance){
	clearEncoders();
	firstForward = (((tileWidth*distance)/ wheelDistance) *rotationTicks); //calculates distance
	while ((nMotorEncoder[rightMotor] + nMotorEncoder[leftMotor]) / 2 < firstForward){
		motor[rightMotor] = speed;
		motor[leftMotor] = speed;
	}
}

task main()
{
	forward(110, 2.45);
	motor(armMotor) = -127;
	wait1Msec(1000);


}
