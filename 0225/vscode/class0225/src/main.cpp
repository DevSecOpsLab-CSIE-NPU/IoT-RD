#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "class0303.h"

void setup()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // 關閉棕色掉電檢測器
    Serial.begin(9600);                        // 設定序列埠通訊速率為9600

    run_class0303_setup();
}

void loop()
{
    run_class0303_loop();
}

