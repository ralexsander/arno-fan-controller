/**
 *  This example allows you to control your fan over WiFi. The default
 *   device is 0, same as all 4 switchs on remote control down. You need
 *   to change the default device (DEVICE_ID), the WiFi credentials (Router_SSID
 *    and Router_Pass) and finally the IP address (IPAddress).
 * 
 *  e.g. turn on/off the lights on default device:
 *       http://10.10.10.166/rc?cmd=light
 * 
 *  e.g. turn on/off the fan on default device 4 (0100):
 *       http://10.10.10.166/rc?cmd=fan&device=4
 * 
 *  Este exmplo permite controlar o ventilar via WiFi. O dispositivo padrão é o 0,
 *    como se no controle remoto todas as chaves ficam para baixo. Você precisa configurar
 *    os dados do seu WiFi abaixo (Router_SSID and Router_Pass) e o IP (IPAddress).
 * 
 *  ex. ligar/desligar as luzes:
 *       http://10.10.10.166/rc?cmd=light
 * 
 *  ex. ligar/desligar o ventilador com ID 4 (0100):
 *       http://10.10.10.166/rc?cmd=fan&device=4
 */
#include <WiFi.h>
#include <WiFiClient.h>

String Router_SSID = "Seu Wifi - Your Wireless Networkd";
String Router_Pass = "Senha - Password";

#include <WebServer.h>
WebServer server(80);

#include "ArnoController.h"
#define RF_PIN 25
#define DEVICE_ID 0

ArnoController controller (RF_PIN, DEVICE_ID);

void handleRC() {
    String xcmd = server.arg("cmd");
    int device = (server.hasArg("device")) ? server.arg("device").toInt() : 0;
    //
    Command cmd = UNKOWN;
    if ( !strcmp(xcmd.c_str(), "light"))      cmd = LIGHT;
    else if ( !strcmp(xcmd.c_str(), "fan"))   cmd = FAN;
    else if ( !strcmp(xcmd.c_str(), "more"))  cmd = MORE;
    else if ( !strcmp(xcmd.c_str(), "less"))  cmd = LESS;
    else if ( !strcmp(xcmd.c_str(), "sleep")) cmd = SLEEP;
    else if ( !strcmp(xcmd.c_str(), "mode"))  cmd = MODE;
    else if ( !strcmp(xcmd.c_str(), "timer")) cmd = TIMER;
    //
    if (cmd == UNKOWN) {
        server.send(401, "text/html", "Error, unkown command");
        return;
    }

    // Control a different device
    if (server.hasArg("device"))
        controller.setDevice(device);
    
    controller.send(cmd);
    server.send(200, "text/html", "Success, rc code sent");
}

void setup() {
    Serial.begin(115200);

    // Change the IP address
    IPAddress _ip, _gw, _nm, _dns1, _dns2;
    _ip.fromString ("10.10.10.166");
    _gw.fromString ("10.10.10.1");
    _nm.fromString ("255.255.255.0");
    _dns1.fromString ("10.10.10.1");
    _dns2.fromString ("10.10.10.2");

    WiFi.mode (WIFI_MODE_STA);
    WiFi.config (_ip, _gw, _nm, _dns1, _dns2);
    tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, "arnocontroller");

    //  Restart in case of disconecction
    WiFi.begin (Router_SSID.c_str(), Router_Pass.c_str());

    delay(1000);
    
    Serial.print("Connecting to WiFi.");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("connected");

    server.on("/rc", handleRC);
    server.begin();  
}

void loop() {
    // handle server
    server.handleClient();
    delay (200);
}
