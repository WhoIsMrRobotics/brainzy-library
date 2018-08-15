/**
 * @file 		Widgets.h
 * @author 		Olivier Lévêque
 * @license 	This project is released under the GPL-3.0 License
 * @copyright 	(c) 2018 Mr. Robotics
 * @date 		June 2018
 * @brief
 *
 */

#define Widgets Wire

//Sensor identificator ports
#define WIDGET_PORT_1 0x01
#define WIDGET_PORT_2 0x02
#define WIDGET_PORT_3 0x03
#define WIDGET_PORT_4 0x04
#define WIDGET_PORT_5 0x05
#define WIDGET_PORT_6 0x06

//Widget libraries
#include <Wire.h>
#include "utility/WidgetSonar.h"
//#include "utility/WidgetRGB.h"