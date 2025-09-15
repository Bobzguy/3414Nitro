/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       BOBZGUY                                                   */
/*    Created:      4/4/2025, 6:47:36 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LA = motor(PORT16, ratio6_1, true);
motor LB = motor(PORT19, ratio6_1, true);
motor_group LD = motor_group(LA, LB);

motor RA = motor(PORT11, ratio6_1, false);
motor RB = motor(PORT15, ratio6_1, false);
motor_group RD = motor_group(RA, RB);

drivetrain Drivetrain = drivetrain(LD, RD);

motor ROLLERA=motor(PORT6, ratio6_1, false);
motor ROLLERB=motor(PORT4, ratio6_1, true);
motor_group ROLLERS=motor_group(ROLLERA, ROLLERB);

motor ARMR=motor(PORT12, ratio6_1, false);
motor ARML=motor(PORT9, ratio6_1, true);
motor_group ARM=motor_group(ARMR, ARML);


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
// define variable for remote controller enable/disable


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
  // process the controller input every 20 milliseconds
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position() ;
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position()  ;
      
      // // check if the value is inside of the deadband range
      // if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
      //   // check if the left motor has already been stopped
      //   if (DrivetrainLNeedsToBeStopped_Controller1) {
      //     // stop the left drive motor
      //     LeftDrivetrain.stop();
      //     // tell the code that the left motor has been stopped
      //     DrivetrainLNeedsToBeStopped_Controller1 = false;
      //   }
      // } else {
      //   // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
      //   DrivetrainLNeedsToBeStopped_Controller1 = true;
      // }
      // // check if the value is inside of the deadband range
      // if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
      //   // check if the right motor has already been stopped
      //   if (DrivetrainRNeedsToBeStopped_Controller1) {
      //     // stop the right drive motor
      //     RightDrivetrain.stop();
      //     // tell the code that the right motor has been stopped
      //     DrivetrainRNeedsToBeStopped_Controller1 = false;
      //   }
      // } else {
      //   // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
      //   DrivetrainRNeedsToBeStopped_Controller1 = true;
      // }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LD.setVelocity(drivetrainLeftSideSpeed, percent);
        LD.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RD.setVelocity(drivetrainRightSideSpeed, percent);
        RD.spin(forward);
      }
      // check the ButtonL1/ButtonL2 status to control Intake
        // Arm control with buttons L1 and L2
      // Arm control with buttons L1 and L2

   
      // ClampSet trigger, Button X to set true, Button B to set false

// Trigger to ClampSet
   
    // wait before repeating the processprocess
    wait(20, msec);
    //Right Arrow Key = Clear: False, LEFT = Out
    if (Controller1.ButtonL1.pressing()) {
      ARM.spin(forward,100, pct);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (Controller1.ButtonL2.pressing()) {
      ARM.spin(reverse,100,pct);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (!Controller1LeftShoulderControlMotorsStopped) {
      ARM.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1LeftShoulderControlMotorsStopped = true;
    }
    // check the ButtonR1/ButtonR2 status to control lady_brown
    if (Controller1.ButtonR1.pressing()) {
      ROLLERS.spin(forward,100, pct);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (Controller1.ButtonR2.pressing()) {
      ROLLERS.spin(reverse,100,pct);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (!Controller1LeftShoulderControlMotorsStopped) {
      ROLLERS.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1LeftShoulderControlMotorsStopped = true;
    }
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1RightShoulderControlMotorsStopped = true;
  


    wait(5, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
    }}}
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
