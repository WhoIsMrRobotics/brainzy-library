/**
 * @file        WidgetSonar.h
 * @author      Olivier Lévêque
 * @license     This project is released under the GPL-3.0 License
 * @copyright   (c) 2018 Mr. Robotics
 * @date        June 2018
 * @brief
 *
 */

#ifndef __WIDGET_SONAR_H
#define __WIDGET_SONAR_H

class WidgetSonar {
  public:
    WidgetSonar(int port) {
    	_address = port;
    }

    bool isConnected() {
      Widgets.beginTransmission(_address);
      return Widgets.endTransmission(true) == 0;
    }

    float distanceRead() {
      float distance = -1.;
    	Widgets.requestFrom(_address,4,true);
      if (Widgets.available() > 0) {
        for (int i=0; i<4; i++) {
          *((unsigned char*)&distance + i) = Widgets.read();
        }
      } 
  		return distance;
  	}

  private:
    int _address;
};

#endif //__WIDGET_SONAR_H