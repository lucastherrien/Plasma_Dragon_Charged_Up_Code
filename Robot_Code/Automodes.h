/**
 * Team 14 Plasma Dragon automode header file
 * @author Lucas Therrien, aka LazerWolf21 on Discord
 * The NoU2 library can be found at https://github.com/AlfredoElectronics/Alfredo-NoU2.
 *
 * Detailed instructions can be found at https://github.com/AlfredoElectronics/AlfredoConnect-Receive/.
 */

#ifndef AUTOMODES_H
#define AUTOMODES_H

// Auxiliary Auto Functions
void curvatureDriveTimed(float throttle, float rotation, int ms);
void autoIntake();
void autoOuttake();
void lookForCube();

// Automodes
void driveForwardAuto();
void oneCubeAuto();
void twoCubeAuto();
void chargeStationAuto();

#endif
