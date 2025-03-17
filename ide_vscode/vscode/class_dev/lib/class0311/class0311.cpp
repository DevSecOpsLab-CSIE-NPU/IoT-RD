#include "Arduino.h"
#include "class0311.h"
#include "BluetoothSerial.h"
#include "BLEDevice.h"

#define LED_PIN 2
#define BT_DISCOVER_TIME 10000
#define BT_DEV_NAME "August-Bluetooth"

// 使用 https://uuidgenerator.net 來生成新的 UUID
#define SERVICE_1_UUID "c11ca591-c87f-4828-9db1-3312bfd1daee"
#define CHARACTERISTIC_1A_UUID "c7576937-5485-4ead-a62a-7cba46422c23"

BluetoothSerial SerialBT;

void run_setup_class0311(void)
{
    Serial.println("run_setup_class0311");
    // 開始藍牙服務
    // startBLEService();
}

void run_loop_class0311(void)
{
    // 掃描藍牙設備
    // scanBluetoothDevices();
    // 重複我的輸入
    // repeatMyTyping();
}

// 點亮 LED 燈 💡
void lightup_led(void)
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

// 關閉 LED 燈 💡
void turnoff_led(void)
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

//----------------------------------------------------------------
// 🚀 開始藍牙服務
//----------------------------------------------------------------
void startBluetoothService(void)
{
    // 初始化藍牙
    Serial.println("Initializing Bluetooth...");

    if (!SerialBT.begin(BT_DEV_NAME))
    { // 藍牙設備名稱
        Serial.println("An error occurred initializing Bluetooth");
    }
    else
    {
        Serial.println("Bluetooth initialized.");
    }

    lightup_led();
}

// 輔助功能：列出找到的設備 📋
void btAdvertisedDeviceFound(BTAdvertisedDevice *pDevice)
{
    Serial.printf("Found a device asynchronously: %s\n", pDevice->toString().c_str());
}

//----------------------------------------------------------------
// 🚀 步驟 1: 當發現藍牙裝置時的列出函數
//----------------------------------------------------------------
void scanBluetoothDevices(void)
{
    Serial.println("Starting Bluetooth scan...");

    static bool btScanAsync = true;
    static bool btScanSync = true;

    if (btScanAsync)
    {
        Serial.print("Starting asynchronous discovery... ");
        if (SerialBT.discoverAsync(btAdvertisedDeviceFound))
        {
            Serial.println("Findings will be reported in \"btAdvertisedDeviceFound\"");
            delay(10000);
            Serial.print("Stopping discoverAsync... ");
            SerialBT.discoverAsyncStop();
            Serial.println("stopped");
        }
        else
        {
            Serial.println("Error on discoverAsync f.e. not working after a \"connect\"");
        }
    }

    if (btScanSync)
    {
        Serial.println("Starting synchronous discovery... ");
        BTScanResults *pResults = SerialBT.discover(BT_DISCOVER_TIME);
        if (pResults)
        {
            pResults->dump(&Serial);
        }
        else
        {
            Serial.println("Error on BT Scan, no result!");
        }
    }
}

//----------------------------------------------------------------
//
//  🚀 步驟 2: 與藍牙裝置連線，並透過序列埠與其溝通 📡
//  [Android] 需要使用超潮的 BlueTooth Serial Terminal 來測試 📱
//  https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal
//  [iOS] 需要使用時尚的 LightBlue 來測試 🍏
//  https://apps.apple.com/us/app/lightblue/id557428110
//  或者
//  https://bluetooth-le-terminal.appstor.io/
//
//----------------------------------------------------------------
void repeatMyTyping(void)
{
    // 檢查是否有可讀取的數據
    if (SerialBT.available())
    {
        // 從傳入的序列緩衝區讀取數據
        char incoming = SerialBT.read();
        // 將傳入的數據打印到終端
        Serial.print("Received: ");
        Serial.println(incoming);
    }
}

// BLE 伺服器回調函數
class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        lightup_led();
        Serial.println("BLE Server Connected");
    }

    void onDisconnect(BLEServer *pServer)
    {
        turnoff_led();
        Serial.println("BLE Server Disconnected");
        BLEDevice::startAdvertising();
    }
};

// BLE 特徵回調函數
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onRead(BLECharacteristic *pCharacteristic)
    {
        Serial.println("BLE Characteristic Read");
        pCharacteristic->setValue("Send from ESP32, I am August!!!");
    }
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string value = pCharacteristic->getValue();
        Serial.print("BLE Characteristic Written: ");
        for (size_t i = 0; i < value.length(); ++i)
        {
            Serial.printf("%02X ", (unsigned char)value[i]);
        }
        Serial.println();
    }
};

//----------------------------------------------------------------
// 🚀 步驟 3a: 開始 BLE 服務
//----------------------------------------------------------------
void startBLEService(void)
{
    Serial.println("startBLEService");

    // 註冊設備名稱
    BLEDevice::init(BT_DEV_NAME);

    // 創建 BLE 伺服器
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // 創建服務 (3b)
    BLEService *pService = pServer->createService(SERVICE_1_UUID);

    // 創建特徵 (3c)
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_1A_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // 幫助解決 iPhone 連接問題的函數
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}
