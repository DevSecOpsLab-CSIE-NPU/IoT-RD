#include <Arduino.h>

#include <Arduino.h>             // 引入 Arduino 的基本函式庫
#include <Wire.h>                // 引入 I2C 通訊函式庫
#include <Adafruit_GFX.h>        // 引入 Adafruit 的圖形函式庫（處理圖形、文字）
#include <Adafruit_SSD1306.h>    // 引入 SSD1306 OLED 顯示器的函式庫

// 定義 OLED 螢幕寬度與高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1          // 沒有使用 RESET 腳位，設為 -1

// 建立一個 OLED 顯示器物件（使用 I2C）
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 初始化 OLED 的設定
void setup_oled() {
    Wire.begin(22, 21); // 設定 I2C 腳位：SDA = GPIO22、SCL = GPIO21

    // 嘗試啟動 OLED，如果失敗就停住程式
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");  // 顯示錯誤訊息
        for (;;);  // 無限迴圈，停止執行
    }

    display.clearDisplay();  // 清空畫面
    display.setTextSize(1);  // 設定文字大小為 1（標準大小）
    display.setTextColor(SSD1306_WHITE);  // 設定文字顏色為白色
    display.setCursor(0, 0);  // 設定游標位置為左上角

    display.println("OLED Initialized");  // 顯示初始化文字
    display.display();  // 將內容顯示在螢幕上

    delay(2000);  // 停留 2 秒
    display.clearDisplay();  // 清空畫面
}

// 顯示數字的函式，可輸入任意數字
void display_number(int number) {
    display.clearDisplay();  // 清空畫面
    display.setCursor(0, 0);  // 游標設在第一行第一列
    display.print("Number: ");  // 顯示文字
    display.println(number);  // 顯示數字並換行

    display.setCursor(1, 20);  // 移動游標到下方一點
    display.print("TEST: ");   // 顯示測試文字
    display.println(number);   // 再次顯示數字
    display.display();         // 更新螢幕內容
}

// Arduino 的 setup() 函式（這裡命名為 test_setup）
void test_setup() {
    Serial.begin(11520);  // 啟動序列埠，方便除錯輸出
    Serial.println("OledTest setup");  // 顯示啟動訊息

    setup_oled();       // 初始化 OLED
    display_number(5);  // 顯示數字 5
}

// Arduino 的 loop() 函式（這裡命名為 test_loop）
void test_loop() {
    // 目前沒做任何事，可放自動更新畫面或讀取感測器等邏輯
}

void setup()
{
    Serial.begin(115200);
    test_setup();
}
uint32_t chipId = 0;

void loop()
{
    test_loop();
}
