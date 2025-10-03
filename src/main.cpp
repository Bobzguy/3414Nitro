/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       BOBZGUY                                                   */
/*    Created:      4/4/2025, 6:47:36 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "Logo.h"

using namespace vex;

// ----- CONFIG -----

competition Competition;
brain Brain;
controller Controller1 = controller(primary);

// ----- LEFT MG ----- 
motor LA = motor(PORT16, ratio6_1, true);
motor LB = motor(PORT17, ratio6_1, true);
motor_group LD = motor_group(LA, LB);


// ----- RIGHT MG -----
motor RA = motor(PORT19, ratio6_1, false);
motor RB = motor(PORT20, ratio6_1, false);
motor_group RD = motor_group(RA, RB);

// ----- INTAKE ROLLERS -----
motor ROLLERA = motor(PORT11, ratio6_1, false);
motor ROLLERB = motor(PORT6, ratio6_1, true);
motor_group ROLLERS = motor_group(ROLLERA, ROLLERB);

// ----- ARM -----
motor ARMR = motor(PORT2, ratio6_1, false);
motor ARML = motor(PORT1, ratio6_1, true);
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

  // ----- MAIN DRIVER LOOP (every 20 ms) -----
  while (true) {
    if (!RemoteCodeEnabled) return;

    // ----- CONTROLLER INPUTS -----
    bool L1_pressed = Controller1.ButtonL1.pressing();
    bool L2_pressed = Controller1.ButtonL2.pressing();
    bool R1_pressed = Controller1.ButtonR1.pressing();
    bool R2_pressed = Controller1.ButtonR2.pressing();

    // ----- DT CONTROL -----
    // left = Axis3 + Axis1
    // right = Axis3 - Axis1
    int leftSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
    int rightSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
    
    // TODO: Implement deadband
    LD.setVelocity(leftSpeed, percent);
    LD.spin(forward);

    RD.setVelocity(rightSpeed, percent);
    RD.spin(forward);
  
    // ----- ARM -----
    if (L1_pressed) {
      ARM.spin(forward, 100, pct);
    } else if (L2_pressed) {
      ARM.spin(reverse, 100, pct);
    } else {
      ARM.stop();
    }

    // ----- ROLLERS -----
    if (R1_pressed) {
      ROLLERS.spin(forward, 100, pct);
    } else if (R2_pressed) {
      ROLLERS.spin(reverse, 100, pct);
    } else {
      ROLLERS.stop();
    }
    drawLogo();
    wait(5, msec);
  }
}


int main() {
  // ----- REGISTER CALLBACKS -----
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // ----- INFINITELY BLOCK CODE (aka life support) -----
  while (true) {
    wait(100, msec);
  }
}
