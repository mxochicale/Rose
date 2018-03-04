/*
 * ServoController.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: jochenalt
 */

#include <assert.h>
#include <iostream>
#include "basics/util.h"
#include <servo/ServoController.h>

using namespace std;

ServoController::ServoController() {
}

ServoController::~ServoController() {
}


void ServoController::setup() {
	const int i2cBus = 1; 			// /dev/ic2-1
	const int i2cAddress = 0x40; 	// i2c address of pca 9685
	const int servoFrequency = 100; // [Hz]

	// initialize PCA 9685 board
	pca9685.setup(i2cBus,i2cAddress);

	// KST Servos can work with 100 Hz
	pca9685.setPWMFreq(servoFrequency);

	servo[0].setup(&pca9685, 0, servoFrequency, false, -85, 60, 0);
	servo[1].setup(&pca9685, 1, servoFrequency, true, -85, 60, 0);
	servo[2].setup(&pca9685, 2, servoFrequency, false, -85, 60, 0);
	servo[3].setup(&pca9685, 3, servoFrequency, true, -85, 60, 0);
	servo[4].setup(&pca9685, 4, servoFrequency, false, -85, 60, 0);
	servo[5].setup(&pca9685, 5, servoFrequency, true, -85, 60, 0);

	servo[6].setup(&pca9685, 6, servoFrequency, false, -85, 60, 0);
	servo[7].setup(&pca9685, 7, servoFrequency, true, -85, 60, 0);
	servo[8].setup(&pca9685, 8, servoFrequency, false, -85, 60, 0);
	servo[9].setup(&pca9685, 9, servoFrequency, true, -85, 60, 0);
	servo[10].setup(&pca9685, 10, servoFrequency, false, -85, 60, 0);
	servo[11].setup(&pca9685, 11, servoFrequency, true, -85, 60, 0);
}

double ServoController::getMinAngle(int servoNo) {
	assert ((servoNo>= 0) && (servoNo < numServos));
	return servo[servoNo].minAngle;
}
double ServoController::getMaxAngle(int servoNo) {
	assert ((servoNo>= 0) && (servoNo < numServos));

	return servo[servoNo].maxAngle;
}

double ServoController::getNullAngle(int servoNo) {
	assert ((servoNo>= 0) && (servoNo < numServos));

	return servo[servoNo].nullAngle;
}

void ServoController::setMinAngle(int servoNo, double newValue) {
	assert ((servoNo>= 0) && (servoNo < numServos));

	servo[servoNo].minAngle = newValue;
}
void ServoController::setMaxAngle(int servoNo, double newValue) {
	assert ((servoNo>= 0) && (servoNo < numServos));

	servo[servoNo].maxAngle = newValue;
}

void ServoController::setNullAngle(int servoNo, double newValue) {
	assert ((servoNo>= 0) && (servoNo < numServos));

	servo[servoNo].nullAngle = newValue;
}



void ServoController::calibrateViaKeyBoard() {
	setup();
	int currentStewart = 0;
	int currentServo = 0;
	int currentAngle = 0;
	cout << "select stewart patform: (a,b)" << endl
		 << "select servo          : (0,1,2,3,4,5)" << endl
	     << "set null value        : n" << endl
	     << "change angle          : +/-" << endl;

    while (true) {

    	if (kbhit()) {
			char inp = getch();
			cout << ((currentStewart == 0)?"A":"B") << "/" << currentServo << ">" << endl;

			switch (inp) {
			case 'a':
				currentStewart = 0;
				break;
			case 'b':
				currentStewart = 1;
				break;
			case '0'-'5':
				currentServo = inp - '0';
				break;
			case '+':
				currentAngle += 1;
				servo[currentServo + currentStewart*6].setAngle(currentAngle);
				break;
			case 'n':
				setNullAngle(currentServo + currentStewart*6, currentAngle - getNullAngle(currentServo + currentStewart*6));
				break;
			case '-':
				currentAngle += 1;
				servo[currentServo + currentStewart*6].setAngle(currentAngle);
				break;
			}
    	}
    }
}
