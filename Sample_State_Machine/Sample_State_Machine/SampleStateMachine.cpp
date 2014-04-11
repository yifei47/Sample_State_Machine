#include "SampleStateMachine.h"
#include <iostream>
#include <windows.h>
using namespace std;

// constructor
CStateMachine::CStateMachine(void)
{
	currentstate = 0; // initial state
	nextstate = 0;
	// the given sensor data as constant
	data[0] = data[5] = data[9] = 100;
	data[1] = 101;
	data[2] = 105;
	data[3] = data[7] = 110;
	data[4] = 210;
	data[6] = 102;
	data[8] = 150;
}

// switch to next state
void CStateMachine::SwitchStates(void)
{
	currentstate = nextstate;
}

// determine the next state
void CStateMachine::GetNextState(void)
{
	if(currentstate == 0)
	{
		nextstate = 1;
		cout << "Initial State\n";
		Sleep(2000); // sleep function used to slow down the rate of switching states for demenstration purposes
	}
	else if(currentstate == 1)  // check door status, true for closed, false for open
	{
		cout << "Check Door Status\n";
		if(door1.GetDoorStatus() == true)  // if door closed, proceed to next state
		{
			cout << "Door is closed, continue\n";
			nextstate = 2;			
		}
		else  // if door open, wait for it to close
		{
			cout << "Door is open, wait for door close\n";
			nextstate = 1;
			door1.Lock();
		}		
		Sleep(2000);
	}
	else if(currentstate == 2)  // calibrate and read data from sensor
	{
		cout << "Calibrate Sensor\n";
		while(sensor1.Calibrate() == false){};
		cout << "Read Sensor Data\n";
		sensor1.ReadData(data);
		nextstate = 3;		
		Sleep(2000);
	}
	else if(currentstate == 3)  // move the motor according to the data read
	{
		cout << "Calculate target position\n";
		int distance = sensor1.CalDistance();
		cout << "Move Motor\n";
		motor1.MoveMotor(distance);
		cout << "The Motor is now at "<<distance<<"\n";
		nextstate = 1;
		Sleep(2000);
		cout << "Open the door for testing purposes\n";
		door1.UnLock();
		cout << "Reset the motor to starting position\n";
		motor1.ResetMotor();
	}
}

CSensor::CSensor(void)
{
	for(int i=0;i<10;i++)
	{
		sensor_data[i] = 0;
	}
}

bool CSensor::Calibrate(void)
{
	// insert sensor calibration processs here, for this sample code it is empty
	return true;
}

void CSensor::ReadData(int data[])
{
	for(int i=0;i<10;i++)
	{
		sensor_data[i] = data[i];
	}
}

int CSensor::CalDistance(void)  // calculate the distance by average all the sensor data
{
	int sum = 0;
	int average = 0;
	for(int i=0;i<10;i++)
	{
		sum += sensor_data[i];
	}
	average = sum/10;
	return average;
}

CMotor::CMotor(void)
{
	position = 0;
}

void CMotor::ResetMotor(void)  // reset motor
{
	position = 0;
}

void CMotor::MoveMotor(int distance)  // move motor
{
	position = distance;
}

CDoorLatch::CDoorLatch(void)
{
	doorlock = false;
}

bool CDoorLatch::GetDoorStatus(void)  // retrieve door status
{
	return doorlock;
}

void CDoorLatch::Lock(void) // close the door
{
	doorlock = true;
}

void CDoorLatch::UnLock(void) // open the door
{
	doorlock = false;
}

int main(void) // main program
{
	cout << "Starting Program\n";

	CStateMachine statemachine1;
	while(1)
	{
		statemachine1.GetNextState();
		statemachine1.SwitchStates();
	}

	return 0;
}