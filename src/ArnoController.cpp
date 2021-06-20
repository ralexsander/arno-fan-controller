#include "ArnoController.h"

ArnoController::ArnoController(byte pin, byte device) {
    this->pin = pin;
    this->device = device;
    init();
}   //  ArnoController

int hex2int (char c) {
    if (c >= '0' && c <= '9')
        return c - '0' ;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
}   //  hex2int

void ArnoController::init() {
    pinMode(pin, OUTPUT);
}   //  sendRaw

void ArnoController::setDevice(int device) {
    this->device = device;
}   //  setDevice

void ArnoController::sendRaw (const char code[]) {
    sendRaw (code, 3);
}   //  sendRaw

void ArnoController::sendRaw (const char code[], int repeat) {
    init();
    int length = strlen (code);
    digitalWrite(pin, LOW);
    delayMicroseconds(500);
    //
    for (int i=0; i<repeat; i++) {
        for (int j=0; j<length; j++) {
            int converted = hex2int (code [j]);
            //
            digitalWrite(pin, (converted & B1000) > 0 ? HIGH : LOW);
            delayMicroseconds(500);
            digitalWrite(pin, (converted & B0100) > 0 ? HIGH : LOW);
            delayMicroseconds(500);
            digitalWrite(pin, (converted & B0010) > 0 ? HIGH : LOW);
            delayMicroseconds(500);
            digitalWrite(pin, (converted & B0001) > 0 ? HIGH : LOW);
            delayMicroseconds(500);        
        }
    }
    //  Clear transmission
    pinMode(pin, DISABLED);
}   //  sendRaw

void ArnoController::send(Command cmd) {
    const char * code;
    switch (cmd) {
        default:
        case LIGHT:  code = light_code; break;
        case FAN:    code = fan_code;   break;
        case LESS:   code = less_code;  break;
        case MORE:   code = more_code;  break;
        case SLEEP:  code = sleep_code; break;
        case MODE:   code = mode_code;  break;
        case TIMER:  code = timer_code; break;
    }

    //  Concatenate preffix and code
    strcpy(buffer,preffix_code);

    int device_code = (int)device;
    strcat(buffer,((device_code & B1000) > 0 ? "7" : "1"));
    strcat(buffer,((device_code & B0100) > 0 ? "7" : "1"));
    strcat(buffer,((device_code & B0010) > 0 ? "7" : "1"));
    strcat(buffer,((device_code & B0001) > 0 ? "7" : "1"));
    strcat(buffer,code);
    //
    sendRaw (buffer);
}   //  send
