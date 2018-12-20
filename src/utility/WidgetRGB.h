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

    bool isConnected() {
      Widgets.beginTransmission(_address);
      return Widgets.endTransmission(true) == 0;
    }

    void colorWrite(uint8_t red, uint8_t green, uint8_t blue, uint8_t id = 255) {
    	Widgets.beginTransmission(_address);
      Widgets.write(red);
      Widgets.write(green);
      Widgets.write(blue);
      Widgets.write(id);
      Widgets.endTransmission();
    }

    /*void colorWrite(uint32_t color, uint8_t id = 255) {
      uint8_t red, green, blue;
      hex2rgb(color, &red, &green, &blue);
      colorWrite(red, green, blue, id);
    }*/

    void brightness(byte bt) {
      Widgets.beginTransmission(_address);
      Widgets.write(bt);
      Widgets.endTransmission();
    }

    int size(void) {
      return _numPixels;
    }

    void clear(void) {
      colorWrite(0, 0, 0, 255);
    }

  private:
    int _address = 0x00;
    int _numPixels = 16;
    uint8_t _red = 0x00;
    uint8_t _green = 0x00;
    uint8_t _blue = 0x00;

    /*uint32_t rgb2hex(uint8_t red, uint8_t green, uint8_t blue) {
      uint32_t rgb = 0x000000;
      rgb |= (uint32_t)red << 16;
      rgb |= (uint32_t)green << 8;
      rgb |= (uint32_t)blue;
      return rgb;
    }

    void hex2rgb(uint32_t hex, uint8_t *red, uint8_t *green, uint8_t *blue) {
      uint32_t R = 0xFF0000 & hex;
      uint32_t G = 0x00FF00 & hex;
      uint32_t B = 0x0000FF & hex;
      *red = (uint8_t)(R >> 16);
      *green = (uint8_t)(G >> 8);
      *blue = (uint8_t)B;
    }*/
};

#endif //__WIDGET_RGB_H