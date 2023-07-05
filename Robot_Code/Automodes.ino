/**
 * Team 14 Plasma Dragon automode functions
 * @author Lucas Therrien, aka LazerWolf21 on Discord
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 *
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
 */

#include "Automodes.h"
#include "Robot_Code.h"

// Automode auxiliary functions

void curvatureDriveTimed(float throttle, float rotation, int ms) {
    drivetrain.curvatureDrive(throttle, rotation);
    delay(ms);
    //drivetrain.curvatureDrive(0,0);
}

void autoIntake(){
    leftIntakeMotor.set(-INTAKE_POWER);
    rightIntakeMotor.set(-INTAKE_POWER);
    delay(500);
    leftIntakeMotor.set(0);
    rightIntakeMotor.set(0);
}

void autoOuttake(){
    leftIntakeMotor.set(INTAKE_POWER);
    rightIntakeMotor.set(INTAKE_POWER);
    delay(500);
    leftIntakeMotor.set(0);
    rightIntakeMotor.set(0);
}

void lookForCube(){
    //TODO, Dependant on actually training a good model for the pico
}

void driveForwardAuto(){
    curvatureDriveTimed(1.0,0,2000);
}

// Automodes

void oneCubeAuto(){
    curvatureDriveTimed(0.75,0,0.200);
    armServo.write(ARM_SCORE_POS);
    wristServo.write(WRIST_MID_POS);
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
    curvatureDriveTimed(-1.0,0,500);
    autoOuttake();
    armServo.write(ARM_FLOOR_POS);
    wristServo.write(WRIST_FLOOR_POS);
    curvatureDriveTimed(1.0,0,2500);
    curvatureDriveTimed(0.5, 0.2, 250);
    //lookForCube();
    autoIntake();
    armServo.write(ARM_HP_POS);
    wristServo.write(WRIST_HP_POS);
    curvatureDriveTimed(-0.5, -0.2, 250);
    curvatureDriveTimed(-1.0,0,3000);
    armServo.write(ARM_SCORE_POS);
    wristServo.write(WRIST_MID_POS);
    autoOuttake();
}

void chargeStationAuto(){
    curvatureDriveTimed(1.0,0,3000);
}
