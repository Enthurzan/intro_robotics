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

int startForwardSpeed = 30; //default motor speed
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

/*------------------------------------------------------

	Encoder straightening Function
	tileDistance is the distance that you want to move
	speed is the chosen speed of the robot

------------------------------------------------------*/
int move(int tileDistance, int speed)
{
	clearEncoders();
	int ticks = (((tileWidth*tileDistance)/ wheelDistance) *rotationTicks);

	while(((nMotorEncoder[leftMotor] + nMotorEncoder[rightMotor]) / 2 ) <= ticks ){

	if(nMotorEncoder[leftMotor] > nMotorEncoder[rightMotor]) {
		motor[leftMotor] = speed -3;
		motor[rightMotor]=speed +3;
	}
	else if(nMotorEncoder[leftMotor] < nMotorEncoder[rightMotor]){
		motor[leftMotor] = speed -3;
		motor[rightMotor]=speed +3;
	}
	else
	{
		motor[rightMotor] = speed;
		motor[leftMotor] = speed;
	}

	}
	clearEncoders();
	return 0;
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
	//customary first code for every function using encoders
	clearEncoders(); 
	/*
		392/90 = x/degrees // degrees * 392 = 90x // (degrees * 392)/ 90  = x
	*/
	rotTicks = abs((degrees * turnTicks)/90); //finds the absolute value so ticks is always positive

	while((abs(nMotorEncoder[rightMotor]) + abs(nMotorEncoder[leftMotor]))/2 < rotTicks )
	if (abs(nMotorEncoder[leftMotor]) > abs(nMotorEncoder[rightMotor])){
		//so if the number is negative
		if (degrees + abs(degrees) == 0){ 
			motor[leftMotor] = speed++;
			motor[rightMotor] = speed++;
		}
		else if (degrees + abs(degrees) != 0){
			motor[leftMotor] = speed--;
			motor[rightMotor] = speed--;
			/*
				logically this makes since because on a left turn, the left motor is going backwards
			so subtracting is going to make it go faster and vise versa for the right motor
			*/
		}

	}
	else if (abs(nMotorEncoder[leftMotor]) < abs(nMotorEncoder[rightMotor])){
		//if number is negative
		if (degrees + abs(degrees) == 0){ 
			motor[leftMotor] = speed--;
			motor[rightMotor] = speed--;

	}
		//if number is positive
		else if (degrees + abs(degrees) != 0){ 
			motor[leftMotor] = speed++;
			motor[rightMotor] = speed++;

		}
	}
	else {
		motor[leftMotor] = speed;
		motor[rightMotor] = speed;

	}

}

/* ----------------------------------------------------

	TASK MAIN - all of the functional code goes here.
	If you want the robot to go forward, turn, etc, put it here

------------------------------------------------------*/

task main()
{

/*------------------------------------------------------

	PID Code - still needs work
	move(2.5, 30);
	turnLeft();
	move(2.9, 50);
	turnRight();
	move(2.15, 50);
	turnLeft();

------------------------------------------------------*/



/*------------------------------------------------------

									Non-PID Section

------------------------------------------------------*/

	forwardDistance(2.25); //go forward 2.25 tiles
	turnLeft(); //functions to turn 90 degrees to the left  - no parameters
	forwardDistance(2.84); //go forward 2.84 tiles
	turnRight(); //turn right
	forwardDistance(2.35); //go forward 2.35 tiles
	turnLeft(); //turn left
	forwardDistance(3); //move forward three tiles
	
	//rotate(45); //rotate tank turn at 45 degrees
	//forwardDistance(1);
	//rotate(45);
	//forwardDistance(2.25)

/*------------------------------------------------------

								End Non-PID Section

------------------------------------------------------*/



}
