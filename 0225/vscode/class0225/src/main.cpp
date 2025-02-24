#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "myfunc.h"

void setup()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // 關閉棕色掉電檢測器
    Serial.begin(9600); // 設定序列埠通訊速率為9600
    start_wifi(); // 啟動WiFi
}

void loop()
{
    say_hello_world(); // 打印 "Hello World"
    String payload = get_weather_data(); // 獲取天氣數據
    Serial.println(payload); // 打印天氣數據
    delay(60000); // 延遲60秒
}