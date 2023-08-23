/**
 * Team 14 Plasma Dragon main robot header file
 * @author Lucas Therrien aka LazerWolf21 on Discord
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 *
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
 */

#ifndef ROBOT_CODE_H
#define ROBOT_CODE_H

#include <AlfredoConnect.h>
#include <BluetoothSerial.h>
#include <Alfredo_NoU2.h>

/* Robot Subsystems */

// Bluetooth
BluetoothSerial bluetooth;

// Drive Motors
NoU_Motor frontLeftMotor(1);
NoU_Motor frontRightMotor(2);
NoU_Motor rearLeftMotor(3);
NoU_Motor rearRightMotor(4);

// Intake Motors
NoU_Motor leftIntakeMotor(5);
NoU_Motor rightIntakeMotor(6);

// Servos
NoU_Servo armServo(1);
NoU_Servo wristServo(4);

// Drivetrain
NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &rearLeftMotor, &rearRightMotor);

/* Robot Control Constants */

// Intake constants
const double INTAKE_POWER = 1.0;

// Arm Servo constants
const int ARM_FLOOR_POS = 172;
const int ARM_BOT_POS = 135;
const int ARM_TOP_POS = 80;
const int ARM_SCORE_POS = 0;
const int ARM_START_POS = 165;
const int ARM_MID_CONE_POS = 80;

// Wrist Servo constants
const int WRIST_FLOOR_POS = 70;
const int WRIST_TOP_POS = 150;
const int WRIST_MID_POS = 50;
const int WRIST_BOT_POS = 180;
const int WRIST_START_POS = 180;
const int WRIST_MID_CONE_POS = 180;

/* Joystick constants */

// Joystick device number
const int ATK3 = 0;

// Joystick axes
const int ROT_AXIS = 0;
const int THROTTLE_AXIS = 1;

// Joystick buttons
const int INTAKE_BUTTON = 0;
const int FLOOR_BUTTON = 1;
const int TOP_BUTTON = 2;
const int BOT_BUTTON = 3;
const int MID_BUTTON = 4;
const int MID_CONE_BUTTON = 5;
const int CONE_PICKUP_BUTTON = 6;
const int CUBE_AUTO_BUTTON = 7;
const int FORWARD_AUTO_BUTTON = 8;
const int STATION_AUTO_BUTTON = 9;


/* Misc */

//Scoring Boolean
bool scoring;

//Servo Positions
int armServoAngle = ARM_START_POS;
int wristServoAngle = WRIST_START_POS;

//Drivetrain power limiters
const float DRIVETRIAN_MAX_POWER = 1.0;
const float MAX_TURN_POWER = 0.85;

#endif
