#include "Arduino.h"
#include "class0318.h"
#include <WiFi.h>

// 初始化設置
void run_setup_class0318(void)
{
    Serial.println("run_setup_class0318");
    connectWifi(); // 連接 WiFi
    Serial.println("setupMQTT");
    setupMQTT(); // 設置 MQTT
    Serial.println("setupMQTT done");
}

// 主循環
void run_loop_class0318(void)
{
    checkMQTT(); // 檢查 MQTT 連接
    delay(1000);
}

//----------------------------------------------------------------
// 🚀 連接到 WiFi
//----------------------------------------------------------------

#define WIFI_SSID "YOUR_SSID"   // WiFi 名稱，不要上傳到網路上
#define WIFI_PASSWORD "YOUR_WIFI_PASSWD" // WiFi 密碼，不要上傳到網路上

void connectWifi()
{
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected."); // WiFi 連接成功
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); // 顯示 IP 地址
    lightup_led();                  // 點亮 LED 燈
}

//----------------------------------------------------------------
// 🚀 控制 LED 燈
//----------------------------------------------------------------
#define LED_PIN 2
// 點亮 LED 燈 💡
void lightup_led(void)
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

// LED 燈閃一下 💡
void blink_led(void)
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    delay(500);
    lightup_led();
}

//----------------------------------------------------------------
// 🚀 MQTT 操作
//----------------------------------------------------------------

#include <PubSubClient.h>

#define MY_DEV_NAME "ESP32_YOUR_NAME"
#define MQTT_USERNAME "MQTT_ACCOUNT"             // MQTT 用戶名，不要上傳到網路上
#define MQTT_PASSWORD "BfWAB9k!@" // MQTT 密碼，不要上傳到網路上
#define MQTT_TOPIC "testtopic/send_to_client"

WiFiClient espClient;
PubSubClient client(espClient);

// MQTT 回調函數
void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    blink_led(); // 收到消息後閃爍 LED 燈
}

// 重新連接 MQTT
void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(MY_DEV_NAME))
        {
            Serial.println("connected");
            client.subscribe(MQTT_TOPIC); // 訂閱主題
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

// 檢查 MQTT 連接
void checkMQTT()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}

// 設置 MQTT
void setupMQTT()
{
    client.setServer("broker.emqx.io", 1883);
    client.setCallback(callback);
    Serial.print("Connecting to MQTT with client ID: ");
    Serial.println(MY_DEV_NAME);
    if (client.connect(MY_DEV_NAME, MQTT_USERNAME, MQTT_PASSWORD))
    {
        Serial.println("MQTT connected");
        client.subscribe(MQTT_TOPIC); // 訂閱主題
    }
    else
    {
        Serial.print("MQTT connection failed, rc=");
        Serial.println(client.state());
    }
}