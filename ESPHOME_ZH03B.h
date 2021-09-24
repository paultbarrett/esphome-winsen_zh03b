#include "esphome.h"
#include "SD_ZH03B.h"

class WinsenZH03B : public PollingComponent {
 public:
  SD_ZH03B ZH03B; // Runs on Serial2 on the ESP32
  Sensor *pm1_sensor = new Sensor();
  Sensor *pm25_sensor = new Sensor();
  Sensor *pm10_sensor = new Sensor();

  WinsenZH03B() : PollingComponent(10000) { } // Poll sensor every 10 seconds

  void setup() override {
    Serial2.begin(9600);
    delay(100);
    ZH03B.setMode( SD_ZH03B::QA_MODE );
    ZH03B.wakeup();
  }

  void update() override {
    
    if( ZH03B.readData() ) {
        pm1_sensor->publish_state(ZH03B.getPM1_0());
        pm25_sensor->publish_state(ZH03B.getPM2_5());
        pm10_sensor->publish_state(ZH03B.getPM10_0());
    } else {   
        ESP_LOGE("custom", "ZH03B Error reading stream or Check Sum Error" );
    } 
  }
};