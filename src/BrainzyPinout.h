/**
 * @file 		BrainzyPinout.h
 * @author 		Olivier Lévêque
 * @license 	This project is released under the GPL-3.0 License
 * @copyright	(c) 2018 Mr. Robotics
 * @date		June 2018
 * @brief		This file define the BRAINZY Board v3.2 pinout
 *
 */

#ifndef __BRAINZY_CONFIG_H
#define __BRAINZY_CONFIG_H

#define EEPROM_SIZE 4095 //Teensy 3.5 (MK64FX512) --> 4096 bytes

/* ------------------- 
  Config Teensy 3.2
------------------- */

//Left motor
#define MOT1_1 		23
#define MOT1_2 		22
#define ENC1_A 		21
#define ENC1_B 		16

//Right motor
#define MOT2_1 		20
#define MOT2_2 		6
#define ENC2_A 		14
#define ENC2_B 		2

//Serial
#define SerialUSB 		Serial
#define SerialBluetooth Serial1
#define SerialWifi		Serial3

//SPI
#define SPI_MOSI 	11
#define SPI_MISO 	12
#define SPI_SCK  	13
#define SPI_CS1  	15
#define SPI_CS2  	9
#define SPI_CS3  	10

//I2C
#define I2C_SDA 	18
#define I2C_SCL 	19
//#define I2C 		Wire

//Others
#define BUILTIN_BTN 	4
#define BUILTIN_LED_BTN 17
#define BUILTIN_LED 	5
#define BUILTIN_BUZZER	3

/* ------------------- 
  Config Teensy 3.5
------------------- */

//Front motor
#define MOT3_1 	36 //255 if not exists
#define MOT3_2 	35 //255 if not exists
#define ENC3_A 	37 //255 if not exists
#define ENC3_B 	38 //255 if not exists

//Power monitoring
#define BATT1 	A22 //255 if not exists
#define BATT2 	A21 //255 if not exists
#define BATT3 	A20 //255 if not exists

//Digital pins
#define D1 		28
#define D2 		30
#define D3		26
#define D4		27
#define D5		25
#define D6		24

//Others
#define SerialEXT1 	Serial4
#define SerialEXT2	Serial5

#endif //__BRAINZY_CONFIG_H