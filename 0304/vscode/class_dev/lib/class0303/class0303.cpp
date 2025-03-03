#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Ping.h>
#include <ArduinoJson.h>

#include "secrets.h" // 包含一個單獨的標頭檔案以存放敏感資訊

#define LED_PIN 2


// 打印 "Hello world!" 訊息
void say_hello_world(void)
{
    Serial.println("Hello world! from class0303.h");
}

// 點亮 LED 燈
void lightup_led(void)
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
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
        // 你也可以試著去抓 https://opendata.cwa.gov.tw/dist/opendata-swagger.html?urls.primaryName=openAPI#/%E9%A0%90%E5%A0%B1/get_v1_rest_datastore_F_D0047_045
        // 但這個 JSON 檔案比較大，可能會造成 ESP32 的記憶體不足 或 ArduinoJson 解析失敗，參考 https://arduinojson.org/v7/assistant/
        String url = "https://raw.githubusercontent.com/DevSecOpsLab-CSIE-NPU/IoT-RD/refs/heads/main/0304/convert_cwa/data.json";
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
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, *payload);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    for (JsonObject obj : doc.as<JsonArray>())
    {
        const char *location = obj["location"];
        const char *tpe_time = obj["tpe_time"];
        const char *temperature = obj["temperature"];

        Serial.printf("Location: %s, Time: %s, Temperature: %s\n", location, tpe_time, temperature);
    }
}

void run_class0303_setup(void)
{

    say_hello_world();                   // 印 "Hello World"
    start_wifi();                        // 啟動WiFi
    String payload = get_weather_data(); // 獲取天氣數據
    show_weather_info(&payload);         // 顯示天氣數據
}

void run_class0303_loop(void)
{
    delay(60000); // 延遲60秒
}