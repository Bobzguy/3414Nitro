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

// ----- CONFIG -----

competition Competition;
brain Brain;
controller Controller1 = controller(primary);

// ----- LEFT MG ----- 
motor LA = motor(PORT16, ratio6_1, true);
motor LB = motor(PORT19, ratio6_1, true);
motor_group LD = motor_group(LA, LB);

// ----- RIGHT MG -----
motor RA = motor(PORT11, ratio6_1, false);
motor RB = motor(PORT15, ratio6_1, false);
motor_group RD = motor_group(RA, RB);

// ----- DT -----
drivetrain Drivetrain = drivetrain(LD, RD);

// ----- INTAKE ROLLERS -----
motor ROLLERA = motor(PORT6, ratio6_1, false);
motor ROLLERB = motor(PORT4, ratio6_1, true);
motor_group ROLLERS = motor_group(ROLLERA, ROLLERB);

// ----- ARM -----
motor ARMR = motor(PORT12, ratio6_1, false);
motor ARML = motor(PORT9, ratio6_1, true);
motor_group ARM = motor_group(ARMR, ARML);


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
  bool RemoteCodeEnabled = true;
  // define variables used for controlling motors based on controller inputs
  bool Controller1LeftShoulderControlMotorsStopped = true;
  bool Controller1RightShoulderControlMotorsStopped = true;
  bool DrivetrainLNeedsToBeStopped_Controller1 = true;
  bool DrivetrainRNeedsToBeStopped_Controller1 = true;

  // process the controller input every 20 milliseconds
  while (true) {
    if (!RemoteCodeEnabled) return;

    // calculate the drivetrain motor velocities from the controller joystick axies
    // left = Axis3 + Axis1
    // right = Axis3 - Axis1
    int leftSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
    int rightSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
    
    // TODO: Implement deadband
    LD.setVelocity(leftSpeed, percent);
    LD.spin(forward);

    RD.setVelocity(rightSpeed, percent);
    RD.spin(forward);
  
    //Right Arrow Key = Clear: False, LEFT = Out
    if (Controller1.ButtonL1.pressing()) {
      ARM.spin(forward, 100, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      ARM.spin(reverse, 100, pct);
    } else {
      ARM.stop();
    }

    // check the ButtonR1/ButtonR2 status to control lady_brown
    if (Controller1.ButtonR1.pressing()) {
      ROLLERS.spin(forward,100, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      ROLLERS.spin(reverse,100,pct);
    } else if (!Controller1LeftShoulderControlMotorsStopped) {
      ROLLERS.stop();
    }

    // Sleep to prevent wasted resources.
    wait(20, msec);
  }
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
