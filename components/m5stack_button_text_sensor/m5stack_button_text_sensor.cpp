#include "esphome/core/log.h"
#include "m5stack_button_text_sensor.h"

namespace esphome {
namespace m5stack_button_text_sensor {

static const char *TAG = "m5stack_button_text_sensor.text_sensor";

void M5StackButtonTextSensor::setup() {
  M5.begin();  
  M5.Display.setBrightness(128);
}

void M5StackButtonTextSensor::loop() {
  M5.update();

  static constexpr const char* const names[] = { "none", "hold", "wasClick", "click", "wasHold", "wasDecideClickCount", "wasDoubleClicked" };
  static constexpr uint32_t colors[] = { BLACK, NAVY, DARKGREEN, DARKCYAN, MAROON, PURPLE, OLIVE, LIGHTGREY, DARKGREY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE, ORANGE, GREENYELLOW, PINK, BROWN, GOLD, SILVER, SKYBLUE, VIOLET };

  int state = M5.BtnA.wasHold() ? 1
            : M5.BtnA.wasClicked() ? 2
            : M5.BtnA.wasPressed() ? 3
            : M5.BtnA.wasReleased() ? 4
            : M5.BtnA.wasDecideClickCount() ? 5
            : 0;

  if (state)
  {
    int clickCount = M5.BtnA.getClickCount();
    ESP_LOGI(TAG, "BtnA:%s  count:%d", names[state], clickCount);
    publish_state(names[state]);

    //set state to wasDoubleClicked if state is wasDecideClickCount and clickCount is 2
    state = (state == 5 && clickCount == 2) ? 6 : state;

    if (state == 1 | state == 2 | state == 3 | state == 4 | state == 6)
    {
      uint32_t color = colors[random(0, 23)];
      M5.Display.clear(color);
      M5.Display.setTextColor(TFT_WHITE, color);

      int16_t x = M5.Display.width() / 2;
      int16_t y = M5.Display.height() / 2;
      M5.Display.setTextDatum(middle_center);
      M5.Display.drawString(String(names[state]).c_str(), x, y, &fonts::FreeSans9pt7b);
    }
  }
}

void M5StackButtonTextSensor::dump_config() { 
  ESP_LOGCONFIG(TAG, "M5Stack Button Text Sensor");
}

}  // namespace m5stack_button_text_sensor
}  // namespace esphome