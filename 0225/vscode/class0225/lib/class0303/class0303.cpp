#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Ping.h>
#include <driver/gpio.h>
#include "class0303.h"
#include <ArduinoJson.h>

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
        String url = "https://opendata.cwa.gov.tw/api/v1/rest/datastore/F-D0047-045?Authorization=CWB-B4699BDF-37F0-48C3-A45D-D856D990B91E&format=JSON";
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

void show_weather_info(String *payload)
{
    /*
    "records": {
    "Locations": [
      {
        "DatasetDescription": "臺灣各縣市鄉鎮未來3天天氣預報",
        "LocationsName": "澎湖縣",
        "Dataid": "D0047-045",
        "Location": [
          {
            "LocationName": "馬公市",
            "Geocode": "10016010",
            "Latitude": "23.567554",
            "Longitude": "119.570666",
            "WeatherElement": [
              {
                "ElementName": "溫度",
                "Time": [
                  {
                    "DataTime": "2025-03-03T12:00:00+08:00",
                    "ElementValue": [
                      {
                        "Temperature": "24"
                      }
                    ]
                  },
    */
    DynamicJsonDocument doc(40960);
    deserializeJson(doc, *payload);
    // Navigate through the nested structure
    JsonArray locations = doc["records"]["Locations"];
    for (JsonObject location : locations)
    {
        JsonArray locArray = location["Location"];
        for (JsonObject loc : locArray)
        {
            const char *locationName = loc["LocationName"];
            Serial.print(F("Location: "));
            Serial.println(locationName);

            JsonArray weatherElements = loc["WeatherElement"];
            for (JsonObject weatherElement : weatherElements)
            {
                const char *elementName = weatherElement["ElementName"];
                if (strcmp(elementName, "溫度") == 0)
                { // "溫度" means "Temperature" in Chinese
                    JsonArray times = weatherElement["Time"];
                    for (JsonObject time : times)
                    {
                        const char *dataTime = time["DataTime"];
                        const char *temperature = time["ElementValue"][0]["Temperature"].as<const char*>();
                        Serial.print(F("Time: "));
                        Serial.print(dataTime);
                        Serial.print(F(" - Temperature: "));
                        Serial.print(temperature);
                        Serial.println(F("°C"));
                    }
                }
            }
        }
    }
}

void run_class0303_setup(void)
{
    start_wifi(); // 啟動WiFi

    say_hello_world();                   // 打印 "Hello World"
    String payload = get_weather_data(); // 獲取天氣數據
    show_weather_info(&payload);         // 顯示天氣數據
}

void run_class0303_loop(void)
{
    delay(60000); // 延遲60秒
}