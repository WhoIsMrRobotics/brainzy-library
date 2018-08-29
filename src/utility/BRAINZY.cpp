/**
 * @file        BRAINZY.cpp
 * @author      Olivier Lévêque
 * @license     This project is released under the GPL-3.0 License
 * @copyright   (c) 2018 Mr. Robotics
 * @date        June 2018
 * @brief
 *
 */

#include "BRAINZY.h"

//Trigometric tools
#define _PI         3.14159265359 //M_PI
#define _2PI_3      2.09439510239 //2*M_PI/3
#define _4PI_3      4.18879020479 //4*M_PI/3
#define DEG2RAD(X)  (0.01745329251 * (X))
#define RAD2DEG(X)  (57.2957795131 * (X))

//Motor identificator numbers
#define LEFTMOTOR   0
#define RIGHTMOTOR  1
#define FRONTMOTOR  2

//Global variables
volatile long _cptencoder[3] = {0L,0L,0L};
  /*
    _cptencoder[0] => Left encoder counter
    _cptencoder[1] => Right encoder counter
    _cptencoder[2] => Front encoder counter
  */
volatile float _angularmotor[3] = {0L,0L,0L};
volatile uint8_t _buttonrising = 0;
volatile uint8_t _buttonfalling = 0;
volatile bool _isledon[2] = {false,false};
  /*
    _isledon[0] => Led state
    _isledon[1] => Led button state
  */
volatile bool _iscontroldone[2] = {true,true};
volatile bool _firstloopcontrol[2] = {true,true};
volatile bool _isspeedset = false;
volatile float _coordinates[4] = {0.,0.,90.,0.};
  /*
    _coordinates[0] => X position
    _coordinates[1] => Y position
    _coordinates[2] => Angular position
    _coordinates[3] => Distance traveled
  */
uint8_t _numberofmotors = 0;
float _velocity[3] = {0.,0.,0.};
  /*
    _velocity[0] => Linear velocity
    _velocity[1] => Angular velocity
    _velocity[2] => Direction of moving
  */
float _target[2] = {90.,0.};
  /*
    _target[0] => Angular position target
    _target[1] => Distance traveled target
  */

void leftInterruptEncA(void) { //Left encoder chanel A
  noInterrupts();
  if (digitalRead(ENC1_A) == digitalRead(ENC1_B)) _cptencoder[LEFTMOTOR]--;
  else _cptencoder[LEFTMOTOR]++;
  interrupts();
}

void leftInterruptEncB(void) { //Left encoder chanel B
  noInterrupts();
  if (digitalRead(ENC1_A) == digitalRead(ENC1_B)) _cptencoder[LEFTMOTOR]++;
  else _cptencoder[LEFTMOTOR]--;
  interrupts();
}

void rightInterruptEncA(void) { //Right encoder chanel A
  noInterrupts();
  if (digitalRead(ENC2_A) == digitalRead(ENC2_B)) _cptencoder[RIGHTMOTOR]--;
  else _cptencoder[RIGHTMOTOR]++;
  interrupts();
}
  
void rightInterruptEncB(void) { //Right encoder chanel B
  noInterrupts();
  if (digitalRead(ENC2_A) == digitalRead(ENC2_B)) _cptencoder[RIGHTMOTOR]++;
  else _cptencoder[RIGHTMOTOR]--;
  interrupts();
}

void frontInterruptEncA(void) { //Front encoder chanel A
  noInterrupts();
  if (digitalRead(ENC3_A) == digitalRead(ENC3_B)) _cptencoder[FRONTMOTOR]--;
  else _cptencoder[FRONTMOTOR]++;
  interrupts();
}
  
void frontInterruptEncB(void) { //Front encoder chanel B
  noInterrupts();
  if (digitalRead(ENC3_A) == digitalRead(ENC3_B)) _cptencoder[FRONTMOTOR]++;
  else _cptencoder[FRONTMOTOR]--;
  interrupts();
}

void clickUpdate(void) { //Call when button state change
  static unsigned long OLDTIME_RELEASE = 0UL;
  static unsigned long OLDTIME_PRESS = 0UL;

  if (millis()-OLDTIME_RELEASE > DEBOUNCE_PERIOD && digitalRead(BUILTIN_BTN) == HIGH) { //Button released
    OLDTIME_RELEASE = millis();
    _buttonrising++;
  }

  if (millis()-OLDTIME_PRESS > DEBOUNCE_PERIOD && digitalRead(BUILTIN_BTN) == LOW) { //Button pressed
    OLDTIME_PRESS = millis();
    _buttonfalling++;
  }
}

void ledUpdate(void) {
  if (!_isledon[0]) { //Led is off
    digitalWrite(BUILTIN_LED, HIGH);
    _isledon[0] = true;
  }
  else { //Led is on
    digitalWrite(BUILTIN_LED, LOW);
    _isledon[0] = false;
  }
}

void ledButtonUpdate(void) {
  if (!_isledon[1]) { //Led button is off
    digitalWrite(BUILTIN_LED_BTN, HIGH);
    _isledon[1] = true;
  }
  else { //Led button is on
    digitalWrite(BUILTIN_LED_BTN, LOW);
    _isledon[1] = false;
  }
}

void odometryUpdate(void) {
  //Get angular motor positions
  noInterrupts();
  float deltaL = (float)_cptencoder[LEFTMOTOR]/NUMTICKS;
  float deltaR = (float)_cptencoder[RIGHTMOTOR]/NUMTICKS;
  float deltaF = (float)_cptencoder[FRONTMOTOR]/NUMTICKS;
  _cptencoder[LEFTMOTOR] = 0L;
  _cptencoder[RIGHTMOTOR] = 0L;
  _cptencoder[FRONTMOTOR] = 0L;
  interrupts();

  //Save angular motor positions
  _angularmotor[LEFTMOTOR] += deltaL;
  _angularmotor[RIGHTMOTOR] += deltaR;
  _angularmotor[FRONTMOTOR] += deltaF;

  //Odometric routine for omnidirectional mode
  float d;
  if (_numberofmotors == 3) {
    d =  -(
      DEG2RAD(deltaL)*cosf(DEG2RAD(_coordinates[2] - _velocity[2])+_4PI_3) +
      DEG2RAD(deltaR)*cosf(DEG2RAD(_coordinates[2] - _velocity[2])) +
      DEG2RAD(deltaF)*cosf(DEG2RAD(_coordinates[2] - _velocity[2])+_2PI_3)
    )*(DIAMETER_OMNI/3.);
    _coordinates[3] += d;
    _coordinates[2] -= (deltaL + deltaR + deltaF)*(DIAMETER_OMNI/WIDTH_OMNI/3.);
    _coordinates[1] -= (
      DEG2RAD(deltaL)*sinf(DEG2RAD(_coordinates[2])+_4PI_3) +
      DEG2RAD(deltaR)*sinf(DEG2RAD(_coordinates[2])) +
      DEG2RAD(deltaF)*sinf(DEG2RAD(_coordinates[2])+_2PI_3)
    )*(DIAMETER_OMNI/3.);
    _coordinates[0] -= (
      DEG2RAD(deltaL)*cosf(DEG2RAD(_coordinates[2])+_4PI_3) +
      DEG2RAD(deltaR)*cosf(DEG2RAD(_coordinates[2])) +
      DEG2RAD(deltaF)*cosf(DEG2RAD(_coordinates[2])+_2PI_3)
    )*(DIAMETER_OMNI/3.);
  }

  //Odometric routine for differential mode
  else {
    d = (DEG2RAD(deltaL - deltaR))*(DIAMETER_DIFF/4.);
    _coordinates[3] += d;
    _coordinates[2] -= (deltaL + deltaR)*(DIAMETER_DIFF/WIDTH_DIFF/2.);
    _coordinates[1] += d * sinf(DEG2RAD(_coordinates[2]));
    _coordinates[0] += d * cosf(DEG2RAD(_coordinates[2]));
  }

  //Set robot speed
  noInterrupts();
  bool setrobotspeed = _isspeedset;
  interrupts();
  if (setrobotspeed && _numberofmotors > 0) {
    int16_t speedLeft, speedRight;

    if (_numberofmotors == 3) {
      float a = cosf(DEG2RAD(_coordinates[2] - _velocity[2])+_4PI_3);
      float b = cosf(DEG2RAD(_coordinates[2] - _velocity[2]));
      float c = cosf(DEG2RAD(_coordinates[2] - _velocity[2])+_2PI_3);
      speedLeft = (int16_t)constrain(-a*_velocity[0] - _velocity[1], -255., 255.);
      speedRight = (int16_t)constrain(-b*_velocity[0] - _velocity[1], -255., 255.);
      int16_t speedFront = (int16_t)constrain(-c*_velocity[0] - _velocity[1], -255., 255.);
      setMotorSpeed(speedFront, FRONTMOTOR);
    }
    else {
      speedLeft = (int16_t)constrain(_velocity[0] - _velocity[1], -255., 255.);
      speedRight = (int16_t)constrain(-_velocity[0] - _velocity[1], -255., 255.);
    }
    setMotorSpeed(speedLeft, LEFTMOTOR);
    setMotorSpeed(speedRight, RIGHTMOTOR);
  }
}

void controlUpdate(void) {
  static float Kp[2] = {K_ROTATION,K_TRANSLATE};
  static float Ki[2] = {I_ROTATION*CONTROL_PERIOD,I_TRANSLATE*CONTROL_PERIOD};
  static float Kd[2] = {D_ROTATION/CONTROL_PERIOD,D_TRANSLATE/CONTROL_PERIOD};
  static float accelerationrobot[2] = {ACCELERATION_ROTATION,ACCELERATION_TRANSLATE};
  static float speedrobot[2] = {SPEED_ROTATION,SPEED_TRANSLATE};

  static float t, t0[2], t1[2], t2[2], tf[2], targetorigin[2];
  static bool istrapezoidalprofil[2];
  static float olderror[2], sumerror[2];

  float currenttarget[2];
  float command[2];

  for (uint8_t k=0; k < 2; k++) {
    //Initialization
    if (_firstloopcontrol[k]) {
      _firstloopcontrol[k] = false;

      currenttarget[k] = 0.;

      sumerror[k] = 0.;
      olderror[k] = 0.;

      noInterrupts();
      targetorigin[k] = _coordinates[k+2];
      interrupts();

      t = 0.;
      t0[k] = sqrtf(fabsf(_target[k]-targetorigin[k]) / accelerationrobot[k]);
      t1[k] = speedrobot[k] / accelerationrobot[k];
      t2[k] = fabsf(_target[k]-targetorigin[k]) / speedrobot[k];

      if (t1[k] < t0[k]) {
        istrapezoidalprofil[k] = true;
        tf[k] = t1[k] + t2[k];
      }
      else {
        istrapezoidalprofil[k] = false;
        tf[k] = t0[k] * 2.;
      }
    }

    //Robot speed profil
    t += (float)CONTROL_PERIOD;
    if (t < tf[k]) {
      //Trapezoidal profil
      if (istrapezoidalprofil[k]) {
        if (t < t1[k]) currenttarget[k] = (accelerationrobot[k]/2.) * powf(t,2.);
        else if (t < t2[k]) currenttarget[k] = (accelerationrobot[k]/2.) * powf(t1[k],2.) + speedrobot[k] * (t - t1[k]);
        else currenttarget[k] = fabsf(_target[k]-targetorigin[k]) - (accelerationrobot[k]/2.) * powf(tf[k] - t,2.);
      }
      //Triangular profil
      else {
        if (t < t0[k]) currenttarget[k] = accelerationrobot[k]/2. * powf(t,2.);
        else currenttarget[k] = fabsf(_target[k]-targetorigin[k]) - (accelerationrobot[k]/2.) * powf(t - tf[k],2.);
      }
      if (_target[k]-targetorigin[k] < 0.) currenttarget[k] = -currenttarget[k];
    }
    else {
      currenttarget[k] = _target[k]-targetorigin[k];
      _iscontroldone[k] = true;
    }
    currenttarget[k] += targetorigin[k];
    //DEBUG: currenttarget[k] = _target[k];

    //PID controller
    noInterrupts()
    float error = currenttarget[k] - _coordinates[k+2];
    interrupts();
    sumerror[k] += error;
    sumerror[k] = constrain(sumerror[k],-255.,255.);
    command[k] = Kp[k]*error + Ki[k]*sumerror[k]+ Kd[k]*(error - olderror[k]);
    command[k] = constrain(command[k], -255., 255.);
    olderror[k] = error;
  }

  //Set speed commands
  noInterrupts();
  _isspeedset = true;
  _velocity[0] = command[1];
  _velocity[1] = command[0];
  interrupts();
}

/* ------------------- 
  Function handles
------------------- */

void setMotorSpeed(int16_t speed, int8_t motorid) {
  speed = constrain(speed, -255, 255);

  //Left motor
  if (motorid == LEFTMOTOR) {
    if (speed > 0) {
      analogWrite(MOT1_1, speed);
      analogWrite(MOT1_2, 0);
    }
    else {
      analogWrite(MOT1_1, 0);
      analogWrite(MOT1_2, -speed);
    }
  }

  //Right motor
  if (motorid == RIGHTMOTOR) {
    if (speed > 0) {
      analogWrite(MOT2_1, speed);
      analogWrite(MOT2_2, 0);
    }
    else {
      analogWrite(MOT2_1, 0);
      analogWrite(MOT2_2, -speed);
    }
  }

  //Front motor
  if (motorid == FRONTMOTOR) {
    if (speed > 0) {
      analogWrite(MOT3_1, speed);
      analogWrite(MOT3_2, 0);
    }
    else {
      analogWrite(MOT3_1, 0);
      analogWrite(MOT3_2, -speed);
    }
  }
}

/* ------------------- 
  Public functions
------------------- */

BRAINZY::BRAINZY(void) {
  //Declare led pins
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(BUILTIN_LED_BTN, OUTPUT);

  //Declare button pin
  pinMode(BUILTIN_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUILTIN_BTN), clickUpdate, CHANGE);

  //Declare battery pins
  if (BATT1 != 255) pinMode(BATT1, INPUT);
  if (BATT2 != 255) pinMode(BATT2, INPUT);
  if (BATT3 != 255) pinMode(BATT3, INPUT);
  analogReference(DEFAULT);

  //Declare buzzer pin
  pinMode(BUILTIN_BUZZER, OUTPUT);

  //Play a little melody on start
  playNote(NOTE_g,4,100UL);
  delay(100UL);
  playNote(NOTE_g,5,100UL);
  delay(100UL);
  playNote(NOTE_g,6,100UL);
  delay(100UL);
  playNote(NOTE_g,7,100UL);
  delay(100UL);
  noTone(BUILTIN_BUZZER);
}

void BRAINZY::setMode(uint8_t modeid) {
  if (modeid == DIFFERENTIAL || modeid == OMNIDIRECTIONAL) {
    //Declare the number of motors
    _numberofmotors = modeid;

    //Declare left motor pins
    pinMode(MOT1_1, OUTPUT);
    pinMode(MOT1_2, OUTPUT);
    analogWriteFrequency(MOT1_1, 234375); //Change PWM frequency to avoid noise (Timer FTM0)

    //Declare right motor pins
    pinMode(MOT2_1, OUTPUT);
    pinMode(MOT2_2, OUTPUT);
    analogWriteFrequency(MOT2_1, 234375); //Change PWM frequency to avoid noise (Timer FTM0)

    if (modeid == OMNIDIRECTIONAL) {
      if (MOT3_1 != 255) pinMode(MOT3_1, OUTPUT);
      if (MOT3_2 != 255) pinMode(MOT3_2, OUTPUT);
      if (MOT3_1 != 255) analogWriteFrequency(MOT3_1, 234375); //Change PWM frequency to avoid noise (Timer FTM3)
    }

    //Declare left encoder pins
    pinMode(ENC1_A, INPUT);
    pinMode(ENC1_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC1_A), leftInterruptEncA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC1_B), leftInterruptEncB, CHANGE);

    //Declare right encoder pins
    pinMode(ENC2_A, INPUT);
    pinMode(ENC2_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC2_A), rightInterruptEncA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC2_B), rightInterruptEncB, CHANGE);

    //Declare front encoder pins
    if (modeid == OMNIDIRECTIONAL) {
      if (ENC3_A != 255) pinMode(ENC3_A, INPUT);
      if (ENC3_B != 255) pinMode(ENC3_B, INPUT);
      if (ENC3_A != 255) attachInterrupt(digitalPinToInterrupt(ENC3_A), frontInterruptEncA, CHANGE);
      if (ENC3_B != 255) attachInterrupt(digitalPinToInterrupt(ENC3_B), frontInterruptEncB, CHANGE);
    }

    //Start odometry routine
    _odometryTimer.begin(odometryUpdate, 1000*ODOMETRY_PERIOD);
    _odometryTimer.priority(0);
  }
}

bool BRAINZY::slaved(void) {
  _controlTimer.priority(1);
  return _controlTimer.begin(controlUpdate, 1000*CONTROL_PERIOD);
}

void BRAINZY::noSlaved(void) {
  noInterrupts();
  _isspeedset = false;
  interrupts();
  _controlTimer.end();
}

const char* BRAINZY::sendAT(HardwareSerial &Serialx, const char *command, unsigned long timeout, bool debug) {
  String response;

  Serialx.print(command);
  Serialx.print("\r\n");

  unsigned long OLDTIME = millis();
  while(millis()-OLDTIME < timeout) {
    while(Serialx.available()) {
      char rxbyte = Serialx.read();
      response += rxbyte;
      if(debug) {
        if (!SerialUSB) SerialUSB.begin(115200);
        SerialUSB.print(rxbyte);
      }
    }
  }
  return response.c_str();
}

void BRAINZY::leftMotorWrite(int16_t velocity) {
  noInterrupts();
  _isspeedset = false;
  interrupts();
  if(_numberofmotors > 0) setMotorSpeed(velocity, LEFTMOTOR);
}

void BRAINZY::rightMotorWrite(int16_t velocity) {
  noInterrupts();
  _isspeedset = false;
  interrupts();
  if(_numberofmotors > 0) setMotorSpeed(velocity, RIGHTMOTOR);
}

void BRAINZY::frontMotorWrite(int16_t velocity) {
  noInterrupts();
  _isspeedset = false;
  interrupts();
  if(_numberofmotors > 0) setMotorSpeed(velocity, FRONTMOTOR);
}

void BRAINZY::speedWrite(int16_t linearvelocity, int16_t angularvelocity, float direction) {
  noInterrupts();
  _isspeedset = true;
  _velocity[0] = (float)linearvelocity;
  _velocity[1] = (float)angularvelocity;
  _velocity[2] = direction;
  interrupts();
}

float BRAINZY::leftMotorPositionRead(void) {
  noInterrupts();
  float pos = _angularmotor[LEFTMOTOR];
  interrupts();
  return pos;
}

float BRAINZY::rightMotorPositionRead(void) {
  noInterrupts();
  float pos = _angularmotor[RIGHTMOTOR];
  interrupts();
  return pos;
}

float BRAINZY::frontMotorPositionRead(void) {
  noInterrupts();
  float pos = _angularmotor[FRONTMOTOR];
  interrupts();
  return pos;
}

void BRAINZY::resetWheelAngularPositions(void) {
  noInterrupts();
  _angularmotor[LEFTMOTOR] = 0.;
  _angularmotor[RIGHTMOTOR] = 0.;
  _angularmotor[FRONTMOTOR] = 0.;
  interrupts();
}

void BRAINZY::xPositionWrite(float X) {
  noInterrupts();
  _coordinates[0] = X;
  interrupts();
  stop();
}

void BRAINZY::yPositionWrite(float Y) {
  noInterrupts();
  _coordinates[1] = Y;
  interrupts();
  stop();
}

void BRAINZY::angularPositionWrite(float theta) {
  noInterrupts();
  _coordinates[2] = theta;
  interrupts();
  stop();
}

float BRAINZY::xPositionRead(void) {
  noInterrupts();
  float coord = _coordinates[0];
  interrupts();
  return coord;
}

float BRAINZY::yPositionRead(void) {
  noInterrupts();
  float coord = _coordinates[1];
  interrupts();
  return coord;
}

float BRAINZY::angularPositionRead(void) {
  noInterrupts();
  float coord = _coordinates[2];
  interrupts();
  return coord;
}

float BRAINZY::voltageBattRead(void) {
  return _voltage[0]+_voltage[1]+_voltage[2];
}

float BRAINZY::voltageCell1Read(void) {
  return _voltage[0];
}

float BRAINZY::voltageCell2Read(void) {
  return _voltage[1];
}

float BRAINZY::voltageCell3Read(void) {
  return _voltage[2];
}

void BRAINZY::alarmBattOn(float threshold) {
  _battalarm = true;
  _battalarmthreshold = threshold;
}

void BRAINZY::alarmBattOff(void) {
  _battalarm = false;
}

void BRAINZY::checkBattProcess(void) {
  static unsigned long OLDTIME_BATTERY = 0UL;

  if (millis()-OLDTIME_BATTERY > BATTERY_PERIOD) {
    OLDTIME_BATTERY = millis();

    //Get raw values and remove noise using an exponential moving average
    float pin[3] = {BATT1,BATT2,BATT3};
    static uint16_t smoothValue[3] = {0,0,0};
    for (uint8_t k=0; k < 3; k++) {
      float newValue = (float)analogRead(pin[k]);
      float diff = abs(newValue - (float)smoothValue[k]);
      float snap = 1. / (diff * 0.001 + 1.);
      snap = (1. - snap)*2.;
      if(snap > 1.) snap = 1.;
      smoothValue[k] += (uint16_t)((newValue - (float)smoothValue[k]) * snap);
    }

    //Compute voltages
    _voltage[0] = (float)smoothValue[0]*0.00491082045;
    _voltage[1] = (float)smoothValue[1]*0.01566037735 - _voltage[0];
    _voltage[2] = (float)smoothValue[2]*0.01470449172 - _voltage[0] - _voltage[1];

    //Start alarm if battery is low
    if (_battalarm) {
      bool battconnected = 1<_voltage[0] || 1<_voltage[1] || 1<_voltage[2];
      bool battempty = battconnected && (_voltage[0]<_battalarmthreshold || _voltage[1]<_battalarmthreshold || _voltage[2]<_battalarmthreshold);
      if (battempty) {
        stop();
        ledNoBlink();
        ledButtonNoBlink();
        noTone(BUILTIN_BUZZER);
        noInterrupts();
        while (true) {
          //Do nothing
        }
      }
    }
  }
}

bool BRAINZY::isButtonPressed(void) {
  bool clicks = false;
  noInterrupts();
  if (_buttonfalling > 0) {
    _buttonfalling = 0;
    clicks = true;
  }
  interrupts();
  return clicks;
}

bool BRAINZY::isButtonReleased(void) {
  bool clicks = false;
  noInterrupts();
  if (_buttonrising > 0) {
    _buttonrising = 0;
    clicks = true;
  }
  interrupts();
  return clicks;
}

bool BRAINZY::ledButtonBlink(unsigned long duration) {
  return _ledButtonTimer.begin(ledButtonUpdate, 1000*duration);
}

void BRAINZY::ledButtonNoBlink(void) {
  _ledButtonTimer.end();
  ledButtonOff();
}

void BRAINZY::ledButtonOn(void) {
  digitalWrite(BUILTIN_LED_BTN, HIGH);
  noInterrupts();
  _isledon[1] = true;
  interrupts();
}

void BRAINZY::ledButtonOff(void) {
  digitalWrite(BUILTIN_LED_BTN, LOW);
  noInterrupts();
  _isledon[1] = false;
  interrupts();
}

bool BRAINZY::isLedButtonOn(void) {
  noInterrupts();
  bool state = _isledon[1];
  interrupts();
  return state;
}

bool BRAINZY::ledBlink(unsigned long duration) {
  return _ledTimer.begin(ledUpdate, 1000*duration);
}

void BRAINZY::ledNoBlink(void) {
  _ledTimer.end();
  ledOff();
}

void BRAINZY::ledOn(void) {
  digitalWrite(BUILTIN_LED, HIGH);
  noInterrupts();
  _isledon[0] = true;
  interrupts();
}

void BRAINZY::ledOff(void) {
  digitalWrite(BUILTIN_LED, LOW);
  noInterrupts();
  _isledon[0] = false;
  interrupts();
}

bool BRAINZY::isLedOn(void) {
  noInterrupts();
  bool state = _isledon[0];
  interrupts();
  return state;
}

void BRAINZY::playNote(uint8_t noteid, uint8_t octaveid, unsigned long duration) {
  uint8_t id = noteid-1+12*(octaveid-4);
  if (noteid < 13 && id < 48) tone(BUILTIN_BUZZER, _notefreq[id], duration);
  else noTone(BUILTIN_BUZZER);
}

void BRAINZY::playMelody(const char *script) {
  _ismelodyplaying = true;
  _melody = script;
}

void BRAINZY::playFile(const char *filename) {
  String melody;
  File myFile = SD.open(filename, FILE_READ);
  while (myFile.available()>0) {
    char rxbyte = myFile.read();
    melody += rxbyte;
  }
  myFile.close();
  playMelody(melody.c_str());
}

void BRAINZY::playMelodyProcess(void) {
  static unsigned long OLDTIME_BUZZER = 0UL;
  static bool playingnote = false;
  static unsigned long noteduration;

  if (_ismelodyplaying) {
    if (playingnote) {
      if (millis()-OLDTIME_BUZZER > noteduration+50) playingnote = false;
    }
    else {
      if (*_melody=='#'||*_melody==',') {
        _melody++;
        noteduration = 100*(*_melody++ - '0');
        noteduration += 10*(*_melody++ - '0');
        noteduration += *_melody++ - '0';
        uint8_t note = *_melody++;
        switch(note) {
          case 'c': note = NOTE_c; break;        //Do
          case 'd': note = NOTE_d; break;        //Re
          case 'e': note = NOTE_e; break;        //Mi
          case 'f': note = NOTE_f; break;        //Fa
          case 'g': note = NOTE_g; break;        //Sol
          case 'a': note = NOTE_a; break;        //La
          case 'b': note = NOTE_b; break;        //Si
          case '-': note = 48; _melody--; break; //Mute
          default: note = 48; break;
        }
        if (*_melody == 'S') {
          _melody++;
          note++;
        }
        uint8_t noteoctave = *_melody++ - '0';
        noTone(BUILTIN_BUZZER);
        playNote(note, noteoctave, noteduration);
        playingnote = true;
        OLDTIME_BUZZER = millis();
      }
      else {
        _ismelodyplaying = false;
        noTone(BUILTIN_BUZZER);
      }
    }
  }
}

void BRAINZY::stop(void) {
  resetVariables();
  leftMotorWrite(0);
  rightMotorWrite(0);
  frontMotorWrite(0);
  noInterrupts();
  _iscontroldone[0] = true;
  _iscontroldone[1] = true;
  interrupts();
}

void BRAINZY::goTo(float X, float Y) {
	//resetVariables(); not usefull because goTo() uses tanslate()
  if (_numberofmotors == 3) { //Only for omnidirectionnal mode
    noInterrupts();
    float XX = X-_coordinates[0];
    float YY = Y-_coordinates[1];
    interrupts();
    float distance = sqrtf(powf(XX,2.)+powf(YY,2.));
    float direction = YY < 0. ? -90. : 90.;
    if (XX != 0.) direction = RAD2DEG(atanf(YY/XX));
    if (XX < 0.) distance *= -1.;
    translate(distance, direction);
  }
}

void BRAINZY::translate(float distance, float direction) {
	resetVariables();
  noInterrupts();
  _isspeedset = true;
  _velocity[2] = direction;
  _target[1] = distance;
  interrupts();
}

void BRAINZY::pointTo(float angle) {
	resetVariables();
  noInterrupts();
  _isspeedset = true;
  _coordinates[2] = fmodf(_coordinates[2], 360.);
  _target[0] = constrain(angle, 0., 360.);
  interrupts();
}

void BRAINZY::turn(float angle, int8_t rounds) {
	resetVariables();
  noInterrupts();
  _isspeedset = true;
  _target[0] = constrain(angle, -360., 360.) + (float)rounds*360. + _coordinates[2];
  interrupts();
}

bool BRAINZY::isActionDone(void) {
  noInterrupts();
  bool isdone = _iscontroldone[0] && _iscontroldone[1];
  interrupts();
  return isdone;
}

void BRAINZY::waitActionDone(void) {
  while(!isActionDone()) {
    //Do nothing
  }
}

void BRAINZY::waitActionDone(void (*function)(void)) {
  while(!isActionDone()) {
    function();
    delay(50);
  }
}

/* -------------------------------- 
  Private & protected functions
-------------------------------- */

void BRAINZY::resetVariables(void) {
  noInterrupts();
  _firstloopcontrol[0] = true;
  _firstloopcontrol[1] = true;
  _iscontroldone[0] = false;
  _iscontroldone[1] = false;
  _coordinates[3] = 0.;
  _target[0] = _coordinates[2];
  _target[1] = 0.;
  interrupts();
}

void BRAINZY::eepromWrite(const char *text, int length, int address) {
  for (int k=0; k < length; k++) {
    EEPROM.update(address+k, *(text+k)); //this function, instead of write(), can save cycles
  }
}

void BRAINZY::eepromRead(char *container, int length, int address) {
  for (uint8_t k=0; k < length; k++) {
    *(container+k) = EEPROM.read(address+k);
  }
}

/* --------------------- 
  Instantiate Object
--------------------- */

BRAINZY Robby;