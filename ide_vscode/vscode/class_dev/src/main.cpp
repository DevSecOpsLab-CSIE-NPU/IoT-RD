#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "Arduino.h"
#include "class0318.h"

void setup()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // 關閉棕色掉電檢測器
    Serial.begin(115200);                      // 設定序列埠通訊速率為 115200
    run_setup_class0318();
}

void loop()
{
    run_loop_class0318();
}
