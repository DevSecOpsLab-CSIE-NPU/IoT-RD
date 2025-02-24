#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Ping.h>
#include <driver/gpio.h>

// 打印 "Hello world!" 訊息
void say_hello_world(void)
{
    Serial.println("Hello world! from myfunc.h");
}

// 點亮 LED 燈
void lightup_led(void)
{
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
}

// Ping 主機
bool ping_host(const char *hostname)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        bool ret = Ping.ping(hostname);
        if (ret)
        {
            Serial.printf("Ping to %s successful\n", hostname);
        }
        else
        {
            Serial.printf("Ping to %s failed\n", hostname);
        }
        return ret;
    }
    else
    {
        Serial.println("WiFi not connected");
        return false;
    }
}

// 啟動 WiFi 連接
void start_wifi(void)
{
    WiFi.begin(SSID, WIFI_PW);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, IPAddress(8, 8, 8, 8));
    Serial.println("Connected to WiFi");
    ping_host("www.google.com");
    lightup_led();
}

// 獲取天氣數據
String get_weather_data(void)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        String url = "https://www.cwa.gov.tw/V8/C/W/County/County.html?CID=10016";
        Serial.printf("GET request to %s\n", url.c_str());
        http.begin(url);
        http.addHeader("accept", "application/json");
        int httpCode = http.GET();

        if (httpCode > 0)
        {
            String payload = http.getString();
            http.end();
            return payload;
        }
        else
        {
            Serial.printf("GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
            http.end();
            return "";
        }
    }
    else
    {
        Serial.println("WiFi not connected");
        return "";
    }
}
