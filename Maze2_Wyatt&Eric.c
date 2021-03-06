#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port8,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           clawMotor,     tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//used in the turnLeft() and turnRight() functions and controls the speed of the turn
int turnSpeed = 70; 
//number of encoder ticks in one rotation
int rotationTicks = 351; 
//distance that one rotation goes
float wheelDistance = 4*PI; 
//width of tile in inches
int tileWidth = 22; 
//number of ticks for a 90 degree turn
int turnTicks = 392; 
//distance in ticks that is calculated later
float firstForward; 
//default motor speed
int startForwardSpeed = 30; 
//variable we use later
int rotTicks; 

//clears Encoders values
void clearEncoders(){ 
	//sets value of leftMotor's encoder to 0
	nMotorEncoder[leftMotor] = 0;
	//sets value of rightMotor's encoder to 0
	nMotorEncoder[rightMotor] = 0;

}


/*------------------------------------------------------

	The following functions are for turning

------------------------------------------------------*/


void turnLeft (int speed){
	//clear the encoders
	clearEncoders();
	//while the avergae of the encoder values is less than then the turn value 
	while ((abs(nMotorEncoder[rightMotor]) + abs(nMotorEncoder[leftMotor])) / 2 < 392)
	{
		//We used the function abs() to determine whether the parameter is negative or positive 
		if (abs(nMotorEncoder[leftMotor]) > abs(nMotorEncoder[rightMotor])){
			//changes speed to account for change (increase)
			motor[leftMotor] = speed++;
			motor[rightMotor] = speed++;

		}
		else if (abs(nMotorEncoder[leftMotor]) < abs(nMotorEncoder[rightMotor])){
			/*
				changes speed to account for change (decrease) - actually makes one motor go faster because it is already
				using a negative value
			*/
			motor[rightMotor] = speed--;
			motor[leftMotor] = speed--;

		}
		//sets speeds equal
		else {
			motor[rightMotor] = speed;
			motor[leftMotor] = speed;
		}

	}

}

/*
	Simply reversed the PID intervals here because its turning right versus turning left
	this functions can be called to make the robot make a 90 degree right turn
*/

void turnRight (int speed){
	clearEncoders();
	while ((abs(nMotorEncoder[rightMotor]) + abs(nMotorEncoder[leftMotor])) / 2 < 392)
	{
		//checks to see the left motor has gone farther than the right motor
		if (abs(nMotorEncoder[leftMotor]) > abs(nMotorEncoder[rightMotor])){
			//following 2 lines change the speed (subtract)
			motor[leftMotor] = speed--;
			motor[rightMotor] = speed--;

		}
		//checks to see if the right motor has gone farther than the left motor
		else if (abs(nMotorEncoder[leftMotor]) < abs(nMotorEncoder[rightMotor])){
			//following two lines change speed (add)
			motor[rightMotor] = speed++;
			motor[leftMotor] = speed++;

		}
		/*
			if the motor have gone the same distance set them to the same speed - this is imperative otherwise 
			the motor will speed up or decrease rapidly and not hold the same speed (We learned this through 
			troubleshooting)
			
		*/
		else {
			//sets speed equal
			motor[rightMotor] = speed;
			motor[leftMotor] = speed;
		}

	}

}


/*------------------------------------------------------

	Encoder straightening Function
	tileDistance is the distance that you want to move
	speed is the chosen speed of the robot

------------------------------------------------------*/
void move(int tileDistance, int speed)
{
	//clear the encoders
	clearEncoders();
	//calculates number of encoder ticks from the number of tiles specified in the parameter
	int ticks = (((tileWidth*tileDistance)/ wheelDistance) *rotationTicks);
	//while the average of the encoder values is less than the distance they need to go 
	while(((nMotorEncoder[leftMotor] + nMotorEncoder[rightMotor]) / 2 ) <= ticks ){
	//checks to see if the left motor has gone farther than the right motor
	if(nMotorEncoder[leftMotor] > nMotorEncoder[rightMotor]) {
		//changes speed by interval of 3
		motor[leftMotor] = speed -3;
		motor[rightMotor]=speed +3;
	}
	//checks to see if the right motor has gone farther than the left motor
	else if(nMotorEncoder[leftMotor] < nMotorEncoder[rightMotor]){
		//slows the left motor by 3 and increases the speed of the right motor by three
		motor[leftMotor] = speed -3;
		motor[rightMotor]=speed +3;
	}
	else
	{
		//sets motor speeds equal to maintain order and the correct speed
		motor[rightMotor] = speed;
		motor[leftMotor] = speed;
	}

	}
	//clear the encoders
	clearEncoders();
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

/*----------------------------------------------------

								PID - straightening code

----------------------------------------------------*/
	//move forward 2.5 tiles at a speed of 50
	move(2.5, 50);
	//turn left 90 degrees at speed 50
	turnLeft(50);
	//move forward 2.9 tiles at a speed of 50
	move(2.9, 50);
	//turn right 90 degrees at speed 50
	turnRight(50);
	//move forward 2.15 tiles at a speed of 50
	move(2.15, 50);
	//turn left 90 degrees at speed 50
	turnLeft(50);
	//move forward 2.85 tiles at a speed of 50
	move(2.85, 50);
	//rotate 45 degrees
	rotate(45);
	//move forward 1.1 tiles at a speed of 50
	move(1.1, 50);
	//rotate 45 degrees
	rotate(45);
	//move forward 3 tiles at a speed of 50
	move(3, 50);

}

/*------------------------------------------------------

	This code was created by Wyatt Johnson and Eric Bowden

	Robotics specifications
	Wheel Diameter - 4"
	One rotation is 4pi inches or roughly 12.5"(about a foot)
	forwards(speed) - function for going forward (ONLY IN THIS PROGRAM)
	One full rotation for these motors in the encoders is between 350-353, so to go 1 rot encoders = 351
	1 tile is 2ft, but because of the loss of mesh is roughly 22"

------------------------------------------------------*/
