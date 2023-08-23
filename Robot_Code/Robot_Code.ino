/**
 * Team 14 Plasma Dragon main robot code
 * @author Lucas Therrien, aka LazerWolf21 on Discord
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 *
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
 */

#include "Robot_Code.h"
#include "Automodes.h"

void setup() {
    bluetooth.begin("PlasmaDragon_14");
    AlfredoConnect.begin(bluetooth);
    bluetooth.println("ArcadeBotGamepad started");

    frontLeftMotor.setInverted(false);
    frontRightMotor.setInverted(true);
    rearLeftMotor.setInverted(false);
    rearRightMotor.setInverted(true);

    frontLeftMotor.setMaximumOutput(DRIVETRIAN_MAX_POWER);
    frontRightMotor.setMaximumOutput(DRIVETRIAN_MAX_POWER);
    rearLeftMotor.setMaximumOutput(DRIVETRIAN_MAX_POWER);
    rearRightMotor.setMaximumOutput(DRIVETRIAN_MAX_POWER);

    leftIntakeMotor.setInverted(false);
    rightIntakeMotor.setInverted(false);

    drivetrain.setMinimumOutput(0.3);
    drivetrain.setInputDeadband(0.1);
    drivetrain.setInputExponent(1.5);
    //drivetrain.setMaximumOutput(0.85);

    scoring = true;

    armServo.write(ARM_START_POS);
    wristServo.write(WRIST_START_POS);

    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}

void loop() {
// Here we define the variables we use in the loop
    int throttle = 0;
    int rotation = 0;

// Here we decide what the throttle and rotation direction will be based on gamepad inputs   
    if (AlfredoConnect.getGamepadCount() >= 1) {
        if(AlfredoConnect.buttonHeld(ATK3,CUBE_AUTO_BUTTON)){
            oneCubeAuto();
        } else if (AlfredoConnect.buttonHeld(ATK3,FORWARD_AUTO_BUTTON)) {
            driveForwardAuto();
        } else if (AlfredoConnect.buttonHeld(ATK3,STATION_AUTO_BUTTON)) {
            chargeStationAuto();
        } else {
            float throttle = AlfredoConnect.getAxis(ATK3, THROTTLE_AXIS);
            float rotation = -AlfredoConnect.getAxis(ATK3, ROT_AXIS);
            rotation = constrain(rotation,-MAX_TURN_POWER,MAX_TURN_POWER);
            drivetrain.curvatureDrive(throttle, rotation);
        }
        RSL::setState(RSL_ENABLED);
    } else {
        RSL::setState(RSL_DISABLED);
    }

// Arm/Wrist Servo Control

/* POSITION LIST
Intake Ground
Intake human player station
Score Cube Top Row
Score Cube Middle Row
Score Cube Bottom Row
Cone Scoring Positions?
*/

    if(AlfredoConnect.buttonHeld(ATK3,FLOOR_BUTTON)){
        scoring = false;
        armServoAngle = ARM_FLOOR_POS;
        wristServoAngle = WRIST_FLOOR_POS;
    } else if(AlfredoConnect.buttonHeld(ATK3,BOT_BUTTON)) {
        scoring = true;
        armServoAngle = ARM_BOT_POS;
        wristServoAngle = WRIST_BOT_POS;
    } else if(AlfredoConnect.buttonHeld(ATK3,TOP_BUTTON)) {
        scoring = true;
        armServoAngle = ARM_TOP_POS;
        wristServoAngle = WRIST_TOP_POS;
    } else if(AlfredoConnect.buttonHeld(ATK3,MID_BUTTON)) {
        scoring = true;
        armServoAngle = ARM_SCORE_POS;
        wristServoAngle = WRIST_MID_POS;
    } else if(AlfredoConnect.buttonHeld(ATK3,CONE_PICKUP_BUTTON)) {
        scoring = false;
        armServoAngle = ARM_FLOOR_POS-20;
        wristServoAngle = 160;//WRIST_BOT_POS;
    } else if(AlfredoConnect.buttonHeld(ATK3,MID_CONE_BUTTON)) {
        scoring = true;
        armServoAngle = ARM_MID_CONE_POS;
        wristServoAngle = WRIST_MID_CONE_POS;
    }

// Intake control
    if(AlfredoConnect.buttonHeld(ATK3,INTAKE_BUTTON)){
        if(scoring){
            leftIntakeMotor.set(INTAKE_POWER);
            rightIntakeMotor.set(INTAKE_POWER);
        } else {
            leftIntakeMotor.set(-INTAKE_POWER);
            rightIntakeMotor.set(-INTAKE_POWER);
        }
    } else {
        leftIntakeMotor.set(0);
        rightIntakeMotor.set(0);
    }

// Here we set the drivetrain motor speeds and servo angle based on what we found in the above code
    armServo.write(armServoAngle);
    wristServo.write(wristServoAngle);

// No need to mess with this code
    AlfredoConnect.update();
    RSL::update();
}
