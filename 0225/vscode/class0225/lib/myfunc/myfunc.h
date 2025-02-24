#ifndef MYFUNC_H
#define MYFUNC_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Ping.h>
#include <driver/gpio.h>

#define SSID "Your_SSID" // WiFi SSID
#define WIFI_PW "YOUR_WIFI_PW" // WiFi 密碼

// 打印 "Hello, World!" 的函數
void say_hello_world(void);

// Ping 主機的函數，返回是否成功
bool ping_host(const char *hostname);

// 啟動 WiFi 的函數
void start_wifi(void);

// 獲取天氣數據的函數，返回天氣數據字符串
String get_weather_data(void);

#endif // MYFUNC_H