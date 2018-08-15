/*
 *   ____    _____               _____   _   _   ______ __     __     
 *  |  _ \  |  __ \      /\     |_   _| | \ | | |___  / \ \   / /     
 *  | |_) | | |__) |    /  \      | |   |  \| |    / /   \ \_/ /      
 *  |  _ <  |  _  /    / /\ \     | |   | . ` |   / /     \   /       
 *  | |_) | | | \ \   / ____ \   _| |_  | |\  |  / /__     | |        
 *  |____/  |_|  \_\ /_/    \_\ |_____| |_| \_| /_____|    |_|        
 *
 * @file        BRAINZY.h
 * @author      Olivier Lévêque
 * @license     This project is released under the GPL-3.0 License
 * @copyright   (c) 2018 Mr. Robotics
 * @date        June 2018
 * @brief       https://github.com/WhoIsMrRobotics/brainzy-library
 *              https://www.mr-robotics.com/docs
 */

#ifndef __BRAINZY_H
#define __BRAINZY_H

/* ------------------- 
  Libraries
------------------- */

#include <math.h>       //The AVR math library
#include <Arduino.h>    //Main include file for the Arduino SDK
#include <Wire.h>       //This library allows you to communicate with I2C/TWI devices
#include <SPI.h>        //This library allows to communicate with SPI
#include <SD.h>         //This library allows for reading from and writing to SD cards
#include <EEPROM.h>     //This library provides an easy to use interface to interact with the internal non-volatile storage

/* ------------------- 
  Parameters
------------------- */

#if defined(TEENSYDUINO)
    #if defined(__MK64FX512__)           //MK64FX512 processor (Teensy 3.5)
        #include "BrainzyPinout.h"       //BRAINZY Board v3.2
        #include "utility/RobbyConfig.h" //Robby version N
    #else
        //For a custom architecture, comment the following line and include your custom configuration files
        #error "Sorry, BRAINZY library only supports BRAINZY Board using Teensy 3.5. Make sure you have selected: Tools > Board > Teensy 3.5"
    #endif
#else
    #error "You must install Teensyduino >> https://www.pjrc.com/teensy/td_download.html"
#endif

/* ------------------- 
  Macros
------------------- */

#define FIRMWARE_VERSION "1.0.0"

//Kinematic modes
#define DIFFERENTIAL	2
#define OMNIDIRECTIONAL 3

//Note frequency identificator numbers
#define NOTE_c 	1
#define NOTE_cS 2
#define NOTE_d  3
#define NOTE_dS 4
#define NOTE_e  5
#define NOTE_f  6
#define NOTE_fS 7
#define NOTE_g  8
#define NOTE_gS 9
#define NOTE_a  10
#define NOTE_aS 11
#define NOTE_b  12

/* ------------------- 
  Function handles
------------------- */

void setMotorSpeed(int16_t speed, int8_t motorid);

/* ------------------- 
  BRAINZY Class
------------------- */

class BRAINZY {
  public:

    BRAINZY(void);

    /*--- Setting ---*/
    void setMode(uint8_t modeid);
    bool slaved(void);
    void noSlaved(void);

    void nameWrite(const char *text) {eepromWrite(text, 8, 0);}
    void nameRead(char *container) {eepromRead(container, 8, 0);}

    void serialNumber(char *container) {eepromRead(container, 11, EEPROM_SIZE-10);}
    const char* firmwareVersion(void) {String version = FIRMWARE_VERSION; return version.c_str();}

    const char* sendAT(HardwareSerial &Serialx, const char *command, unsigned long timeout = 1000UL, bool debug = false);

    /*--- Speed control ---*/
    void leftMotorWrite(int16_t velocity);
    void rightMotorWrite(int16_t velocity);
    void frontMotorWrite(int16_t velocity); //Only for omnidirectional mode
    void speedWrite(int16_t linearvelocity, int16_t angularvelocity, float direction = 90.); //Third argument is only for omnidirectional mode

    /*--- Odometry ---*/
    float leftMotorPositionRead(void);
    float rightMotorPositionRead(void);
    float frontMotorPositionRead(void); //Only for omnidirectional mode
    
    void resetWheelAngularPositions(void);

    void xPositionWrite(float X);
    void yPositionWrite(float Y);
    void angularPositionWrite(float theta);

    float xPositionRead(void);
    float yPositionRead(void);
    float angularPositionRead(void);

    /*--- Battery monitoring ---*/
    float voltageBattRead(void);
    float voltageCell1Read(void);
    float voltageCell2Read(void);
    float voltageCell3Read(void);
    void alarmBattOn(float threshold = 3.1);
    void alarmBattOff(void);
    void checkBattProcess(void);

    /*--- LED button ---*/
    bool isButtonPressed(void);
    bool isButtonReleased(void);
    bool ledButtonBlink(unsigned long duration);
    void ledButtonNoBlink(void);
    void ledButtonOn(void);
    void ledButtonOff(void);
    bool isLedButtonOn(void);

    /*--- LED builtin ---*/
    bool ledBlink(unsigned long duration);
    void ledNoBlink(void);
    void ledOn(void);
    void ledOff(void);
    bool isLedOn(void);

    /*--- Buzzer ---*/
    void playNote(uint8_t noteid, uint8_t octaveid = 4, unsigned long duration = 500UL);
    void playMelody(const char *script);
    void playFile(const char *filename);
    void playMelodyProcess(void);

    /*--- Position control ---*/
    void stop(void);
    void goTo(float X, float Y); //Only for omnidirectional mode
    void translate(float distance, float direction = 90.); //Second argument is only for omnidirectional mode
    void pointTo(float angle);
    void turn(float angle, int8_t rounds = 0);
    //TODO: void turnAround(float angle, float Xc, float Yc);
    //TODO: void turnAround(float angle, float radius);

    bool isActionDone(void);
    void waitActionDone(void);
    void waitActionDone(void (*function)(void));

    /*--- SD Card ---*/
    bool beginSD(void) {return SD.begin(BUILTIN_SDCARD);}

  private:
    //Battery variables
    bool _battalarm = false;
    float _battalarmthreshold;
    float _voltage[3] = {0.,0.,0.};

    //LED variables
    IntervalTimer _ledTimer, _ledButtonTimer;

    //BUZZER variables
    bool _ismelodyplaying = false;
    const char *_melody = NULL;
    const uint16_t _notefreq[48] = { //Note frequencies (Hz)
    	262 ,277 ,294 ,311 ,330 ,349 ,370 ,392 ,415 ,440 ,466 ,494 , //Octave 4
    	523 ,554 ,587 ,622 ,659 ,698 ,740 ,784 ,831 ,880 ,932 ,988 , //Octave 5
    	1046,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976, //Octave 6
    	2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951  //Octave 7
    };

    //Control variables
    IntervalTimer _odometryTimer, _controlTimer;
    void (*user_callbackfunc)(void);
    void resetVariables(void);

    //EEPROM functions
    void eepromWrite(const char *text, int length, int address);
    void eepromRead(char *container, int length, int address);
};

/* ------------------- 
  Instantiate Object
------------------- */

extern BRAINZY Robby;

#endif //__BRAINZY_H