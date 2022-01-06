/***
 *  This project is intended to controle Arno Fan models VX10 and VX12
 * 
 *  Este projeto tem como finalidade controlar os ventiladores da Arno
 *    modelos VX10 e VX12. O projeto teve como base os trabalhos feitos
 *    pelo Samuel Kato (https://github.com/samuelkato/arno-vx10).
 *  
 *  Exemplo do código para ligar o ventilador:
 *  
 *  Ação -----------------|
 *                        |
 *  Dispositivo ----|     |
 *                  |     |
 *  Cabeçalho -|    |     |
 *             V    V     V
 *  -------------- ---- -------- 
 *  FF333333331117 1111 71717171
 * 
 *  Author: Ricardo Santana <ralexsander@gmail.com>
 **/
#ifndef RF_H
#define RF_H
#include <Arduino.h>

//  Available commands
enum Command { LIGHT, FAN, LESS, MORE,  SLEEP, MODE, TIMER, UNKOWN };

class ArnoController {
  
  private:
    byte pin;
    byte device;
    char buffer[32];
    const char preffix_code [19] = "FF333333331117";
    const char light_code [9]    = "71717171";
    const char fan_code [9]      = "17171717";
    const char less_code [9]     = "11117777";
    const char more_code [9]     = "77771111";
    const char sleep_code [9]    = "71177117";
    const char mode_code [9]     = "77117711";
    const char timer_code [9]    = "11771177";
    
  public:
    // Setup pin connected to 433.93MHz transmitter and device ID
    ArnoController(byte pin, byte device);
    // Initialize the output
    void init();
    // Set device
    void setDevice (int device);
    // Send a raw hex code with 500 microseconds frequency, repeated 3x
    void sendRaw (const char code[]);
    // Send a raw hex code with 500 microseconds frequency
    void sendRaw (const char code[], int repeat);
    // Send a command
    void send (Command cmd);
};
#endif
