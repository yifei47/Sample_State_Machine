
#include <stdio.h>

class CSensor 
{
private:
	int sensor_data[10]; // stores sensor data
public:
	CSensor(void);
	bool Calibrate(void); // calibrates the sensor
	void ReadData(int data[]); // reads the data from the sensor	
	int CalDistance(void); // calculate the distance the motor should move
};

class CMotor
{
private:
	int position; // the current position of the motor
public:
	CMotor(void); 
	void ResetMotor(void); // moves motor to the starting position
	void MoveMotor(int distance); // moves motor to the measurement position
};

class CDoorLatch
{
private:
	bool doorlock; // the current state of the door latch
public:
	CDoorLatch(void);
	bool GetDoorStatus(void); // read the current state of the door latch
	void Lock(void); // lock the door
	void UnLock(void); //unlock the door
};

class CStateMachine
{
private:
	int currentstate; //represent the different states with integers, 0 for initial state, 1 for check door status, 2 for read sensor, 3 for move motor
	int nextstate; // the next state
	int data[10];
	CSensor sensor1;
	CMotor motor1;
	CDoorLatch door1;
public:
	CStateMachine(void);
	void SwitchStates(void); // switch to next state
	void GetNextState(void); // determine the next state
};



