# 開發流程

## 0303

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
