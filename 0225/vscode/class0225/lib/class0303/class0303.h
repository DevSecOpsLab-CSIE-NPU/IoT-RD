#ifndef MYFUNC_H
#define MYFUNC_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Ping.h>
#include <driver/gpio.h>

#define SSID ".1_AugChaoLab" // WiFi SSID
#define WIFI_PW "0921680824!@" // WiFi 密碼

// 獲取天氣數據的函數，返回天氣數據字串
String get_weather_data(void);

// Ping 主機的函數，返回是否成功，成功回傳 true，失敗回傳 false
bool ping_host(const char *hostname);

// 打印 "Hello, World!" 的函數，在序列埠印出 Hello World!
void say_hello_world(void);

// 啟動 WiFi 的函數，會連接到指定的 WiFi 網路
void start_wifi(void);

// 執行 class0303 的 setup 函數，在 Arduino 的 setup() 中呼叫
void run_class0303_setup(void);

// 執行 class0303 的 loop 函數，在 Arduino 的 loop() 中呼叫
void run_class0303_loop(void);

#endif // MYFUNC_H
