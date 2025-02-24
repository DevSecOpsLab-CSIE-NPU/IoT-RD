#ifndef MYFUNC_H
#define MYFUNC_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Ping.h>
#include <driver/gpio.h>

#define SSID ".1_AugChaoLab"
#define WIFI_PW "0921680824!@"

void say_hello_world(void);
bool ping_host(const char *hostname);
void start_wifi(void);
String get_weather_data(void);

#endif // MYFUNC_H