# 開發流程

## 0311
介紹如何在 ESP32 上開發藍牙功能，包括藍牙經典（Bluetooth Classic）和藍牙低功耗（BLE）。課程內容涵蓋以下幾個部分：

1. 初始化和設置：設置 LED 引腳、藍牙設備名稱和 UUID，並初始化藍牙。
2. 藍牙經典功能：
   - startBluetoothService：初始化藍牙並啟動服務。
   - scanBluetoothDevices：異步和同步掃描藍牙設備。
   - repeatMyTyping：接收並回顧藍牙串口數據。
3. BLE 功能：
   - startBLEService：創建 BLE 伺服器、服務和特徵，並啟動廣播。
   - MyServerCallbacks 和 MyCharacteristicCallbacks：處理 BLE 連接和特徵讀寫回調。
學生將學習如何設置和控制 LED，初始化和使用藍牙經典和 BLE 功能，並處理藍牙設備的掃描、連接和數據傳輸。課程還包括實現 BLE 伺服器和特徵的回調函數，以處理連接和數據讀寫事件。

## 0304

在 `run_class0303_setup()` [class0303.cpp#L118](https://github.com/DevSecOpsLab-CSIE-NPU/IoT-RD/blob/08295148b4be0d639726e4be478ec4821da6604b/0304/vscode/class_dev/lib/class0303/class0303.cpp#L118)中
1. 在 class0303.h 中建立 hello world 函數 🌍
2. 嘗試連接你的 WiFi 📶
3. 當連接到 WiFi 時，嘗試 ping Google 🌐
4. 連接成功！點亮藍色 LED 💡
5. 嘗試獲取天氣資訊 ☁️
6. 嘗試解析天氣資訊的 JSON 資料 📊

問與答：
- 為什麼我們不直接使用 CWA 的 JSON 資料？ 🤔

```
#define ARDUINOJSON_SLOT_ID_SIZE 4
#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 20
```
