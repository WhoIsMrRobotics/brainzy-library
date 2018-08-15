/**
 * @file        WidgetRGB.h
 * @author      Olivier Lévêque
 * @license     This project is released under the GPL-3.0 License
 * @copyright   (c) 2018 Mr. Robotics
 * @date        June 2018
 * @brief
 *
 */

#ifndef __WIDGET_RGB_H
#define __WIDGET_RGB_H

class WidgetRGB {
  public:
    WidgetRGB(int port) {
    	_address = port;
    }

    void colorWrite(byte red, byte green, byte blue, uint8_t id = 255) {
    	Widgets.beginTransmission(_address);
      Widgets.write(id);
      Widgets.write(red);
      Widgets.write(green);
      Widgets.write(blue);
      Widgets.endTransmission();
    }

    void colorWrite(unsigned long color, uint8_t id = 255) {
      byte red, green, blue;
      hex2rgb(color, &red, &green, &blue);
      colorWrite(red, green, blue, id);
    }

    void brightness(uint8_t bt) {

    }

    int numLed(void) {
      return _numled;
    }

  private:
    int _address = 0x00;
    int _numled = 16;
    byte _red = 0x00;
    byte _green = 0x00;
    byte _blue = 0x00;

    unsigned long rgb2hex(byte red, byte green, byte blue) {
      unsigned long rgb = 0x000000;
      rgb |= (unsigned long)red << 16;
      rgb |= (unsigned long)green << 8;
      rgb |= (unsigned long)blue;
      return rgb;
    }

    void hex2rgb(unsigned long hex, byte *red, byte *green, byte *blue) {
      unsigned long R = 0xFF0000 & hex;
      unsigned long G = 0x00FF00 & hex;
      unsigned long B = 0x0000FF & hex;
      *red = (byte)(R >> 16);
      *green = (byte)(G >> 8);
      *blue = (byte)B;
    }
};

#endif //__WIDGET_RGB_H