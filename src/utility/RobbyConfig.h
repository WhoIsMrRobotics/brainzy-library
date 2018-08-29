/**
 * @file 		RobbyConfig.h
 * @author 		Olivier Lévêque
 * @license 	This project is released under the GPL-3.0 License
 * @copyright 	(c) 2018 Mr. Robotics
 * @date		June 2018
 * @brief		This file define the robot specifications - Robby version N
 *
 */

#ifndef __ROBOT_CONFIG_H
#define __ROBOT_CONFIG_H

/* ------------------- 
  Robot geometry
------------------- */

//Dimensions in millimeters
#define WIDTH_OMNI	  268.
#define WIDTH_DIFF	  240.
#define DIAMETER_OMNI 58.
#define DIAMETER_DIFF 59.5

/* ------------------- 
  Control settings
------------------- */

#define NUMTICKS	11. //Number of ticks per degree

#define CONTROL_PERIOD 10 	//ms
#define BATTERY_PERIOD 50 	//ms
#define ODOMETRY_PERIOD 5 	//ms
#define DEBOUNCE_PERIOD 100 //ms

#define K_TRANSLATE		30.
#define K_ROTATION		30.
#define I_TRANSLATE		0.
#define I_ROTATION		0.
#define D_TRANSLATE		1000.//500.
#define D_ROTATION		1000.//600.

#define SPEED_TRANSLATE 		0.3
#define SPEED_ROTATION         	0.15
#define ACCELERATION_TRANSLATE 	0.0001
#define ACCELERATION_ROTATION  	0.00005

#endif //__ROBOT_CONFIG_H