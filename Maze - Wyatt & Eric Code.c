#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port8,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           clawMotor,     tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------

This code was created by Wyatt Johnson and Eric Bowden

Robotics specifications
Wheel Diameter - 4"
One rotation is 4pi inches or roughly 12.5"(about a foot)
forwards(speed) - function for going forward (ONLY IN THIS PROGRAM)
One full rotation for these motors in the encoders is between 350-353, so to go 1 rot encoders = 351
1 tile is 2ft, but because of the loss of mesh is roughly 22"

------------------------------------------------------*/

// Speed Variables
int turnSpeed = 70; //used in the turnLeft() and turnRight() functions and controls the speed of the turn

//Distance Variables
int rotationTicks = 351; //number of encoder ticks in one rotation
float wheelDistance = 4*PI; //distance that one rotation goes
int tileWidth = 22; //width of tile in inches
int turnTicks = 392; //number of ticks for a 90 degree turn
float firstForward; //distance in ticks that is calculated later


int clearEncoders(){ //clears Encoders values
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	return 0;

}

//Forward Speed Variables(Troubleshooting)

int startForwardSpeed = 50; //default motor speed
int rotTicks; //variable we use later

//Speed are arranged like this so that they can be changed individually

int forwardLeft = startForwardSpeed;
int forwardRight = startForwardSpeed;

int forward() { //tells robot to move forward at a certain speed for a certain time
	motor[rightMotor] = forwardRight;
	motor[leftMotor] = forwardLeft;
	return 0;

}
/*------------------------------------------------------

The following functions are for turning

------------------------------------------------------*/


int turnLeft() //use this function to turn left
{
	clearEncoders();

	while((nMotorEncoder[rightMotor] <= turnTicks) && (nMotorEncoder[leftMotor] >= -(turnTicks))){
		motor[leftMotor] = -turnSpeed;
		motor[rightMotor] = turnSpeed;
	}
	return 0;
}


int turnRight () //use this function to turn right
{
	clearEncoders();
	while(nMotorEncoder[rightMotor] >= -(turnTicks) && nMotorEncoder[leftMotor] <= turnTicks){
		motor[leftMotor] =  turnSpeed; //left motor goes backwards
		motor[rightMotor] = -(turnSpeed); //right motor goes forward
	}
	return 0;

}

/*------------------------------------------------------

This function can be used to make the robot use encoders to move forward a certain distance
The integer distance parameter is the tile distance.
Later versions of this function may use inches parameter versus tile distance because that would be easier
to measure
This function automatically clears encoders, calculates the number of ticks to count, and
moves the robot that distance

------------------------------------------------------*/

int forwardDistance(float distance){
	clearEncoders(); //clear the encoders
	firstForward = (((tileWidth*distance)/ wheelDistance) *rotationTicks); //calculates distance
	while((nMotorEncoder[rightMotor] <= firstForward) &&(nMotorEncoder[leftMotor] <= firstForward) ){
		forward(); //robot moves forward
	}
	return 0;
}

/* ----------------------------------------------------

TASK MAIN - all of the functional code goes here.
If you want the robot to go forward, turn, etc, put it here

------------------------------------------------------*/

task main()
{

	forwardDistance(2.25); //go forward 2.25 tiles
	turnLeft(); //functions to turn 90 degrees to the left  - no parameters
	forwardDistance(2.84); //go forward 2.84 tiles
	turnRight(); //turn right
	forwardDistance(2.05); //go forward 2.35 tiles
	turnLeft(); //turn left
	forwardDistance(1.35); //move forward three tiles
	//Turning Code
	motor[rightMotor] = turnSpeed; //set right motor to turnSpeed
	motor[leftMotor] = -(turnSpeed); //set left motor to the opposite of turn speed
	wait1Msec(750);
	//forward 3 tiles
	forwardDistance(3);
	//45 degree turn roughly
	motor[rightMotor] = turnSpeed;
	motor[leftMotor] = -(turnSpeed);
	wait1Msec(750);
	//forward 2.5 tiles
	forwardDistance(2.5);

}
