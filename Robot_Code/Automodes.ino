/**
 * Team 14 Plasma Dragon automode functions
 * @author Lucas Therrien, aka LazerWolf21 on Discord
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 *
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
 */

#include "Automodes.h"
#include "Robot_Code.h"
#include <Pixy2UART.h>
Pixy2UART pixy;

// Automode auxiliary functions

void curvatureDriveTimed(float throttle, float rotation, int ms) {
    drivetrain.curvatureDrive(throttle, rotation);
    delay(ms);
    //drivetrain.curvatureDrive(0,0);
}

void autoIntake(){
    leftIntakeMotor.set(-INTAKE_POWER);
    rightIntakeMotor.set(-INTAKE_POWER);
    curvatureDriveTimed(-0.85,0,500);
    //delay(500);
    leftIntakeMotor.set(0);
    rightIntakeMotor.set(0);
    curvatureDriveTimed(0.85,0,500);
}

void autoOuttake(){
    leftIntakeMotor.set(INTAKE_POWER);
    rightIntakeMotor.set(INTAKE_POWER);
    delay(750);
    leftIntakeMotor.set(0);
    rightIntakeMotor.set(0);
}

void lookForCube(char cubeDirection){
  // robot cube scan turn power
  float turn_power = 0.75;
  // tracks how many milliseconds the robot has turned for, negative = left positive = right
  int turn_tracker = 0;
  // Initial turn to look for cube
  if(cubeDirection == 'l'){
    curvatureDriveTimed(0,-turn_power,100);
    turn_tracker -= 100;
  }
  else if(cubeDirection == 'r'){
    curvatureDriveTimed(0,turn_power,100);
    turn_tracker += 100;
  }
  // grab blocks
  pixy.ccc.getBlocks();
  // If there are blocks (i.e. we see a cube/cone)
  for(int i = 0; i < pixy.ccc.numBlocks; i++){
      pixy.ccc.blocks[i].print();
      // finds biggest cube, biggest signatures are ALWAYS listed first in blocks[]
      if(pixy.ccc.blocks[i].m_signature == 1){
        // get cube angle
        int angle = pixy.ccc.blocks[i].m_angle;
        // get ourselves lined up with the cube based on the obtained angle and keep track of how much were turning
        int dir = angle/abs(angle);
        int turn_ms = abs(angle)*10; // Arbitrarily 10 ms per degree off for now
        curvatureDriveTimed(0,dir*turn_power,turn_ms);
        turn_tracker += dir*turn_ms;
        // grab the cube
        autoIntake();
        // turn back to face goal, gotta admit this implementation is super ghetto
        dir = turn_tracker/abs(turn_tracker);
        turn_tracker = abs(turn_tracker);
        curvatureDriveTimed(0,dir*turn_power,turn_tracker);
        return;
      }
  }
}

// Automodes

void driveForwardAuto(){
    curvatureDriveTimed(1.0,0,2000);
}

void oneCubeAuto(){
    armServo.write(ARM_BOT_POS);
    curvatureDriveTimed(0,0,500);
    curvatureDriveTimed(0.75,0,200);
    armServo.write(ARM_SCORE_POS);
    wristServo.write(WRIST_MID_POS);
    curvatureDriveTimed(0,0,500);
    autoOuttake();
    armServo.write(ARM_FLOOR_POS);
    wristServo.write(WRIST_FLOOR_POS);
    armServoAngle = ARM_FLOOR_POS;
    wristServoAngle = WRIST_FLOOR_POS;
    curvatureDriveTimed(0,0,1000);
    curvatureDriveTimed(-0.85,0,2000);
    //drivetrain.curvatureDrive(0,0);
}

void twoCubeAuto(){
    armServo.write(ARM_BOT_POS);
    curvatureDriveTimed(0,0,500);
    curvatureDriveTimed(0.75,0,200);
    armServo.write(ARM_SCORE_POS);
    wristServo.write(WRIST_MID_POS);
    curvatureDriveTimed(0,0,500);
    autoOuttake();
    armServo.write(ARM_FLOOR_POS);
    wristServo.write(WRIST_FLOOR_POS);
    armServoAngle = ARM_FLOOR_POS;
    wristServoAngle = WRIST_FLOOR_POS;
    curvatureDriveTimed(0,0,1000);
    curvatureDriveTimed(-0.85,0,2000);
    lookForCube('l');
    curvatureDriveTimed(0.85,0,2000);
    armServo.write(ARM_SCORE_POS);
    wristServo.write(WRIST_MID_POS);
    curvatureDriveTimed(0,0,500);
    autoOuttake();
}

void chargeStationAuto(){
    curvatureDriveTimed(1.0,0,3000);
}
