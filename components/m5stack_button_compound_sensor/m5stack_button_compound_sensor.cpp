#include "esphome/core/log.h"
#include "m5stack_button_compound_sensor.h"
#include <M5Unified.h>
#include <M5GFX.h>

namespace esphome {
namespace m5stack_button_compound_sensor {

static const char *TAG = "m5stack_button_compound_sensor.sensor";

void M5StackButtonCompoundSensor::setup() {
  M5.begin();
}

void M5StackButtonCompoundSensor::loop() {
  M5.update();

  static constexpr const char* const names[] = { "none", "wasHold", "wasClicked", "wasPressed", "wasReleased", "wasDecideClickCount", "wasDoubleClicked" };
  static constexpr uint32_t colors[] = { BLACK, NAVY, DARKGREEN, DARKCYAN, MAROON, PURPLE, OLIVE, LIGHTGREY, DARKGREY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE, ORANGE, GREENYELLOW, PINK, BROWN, GOLD, SILVER, SKYBLUE, VIOLET };

  int state = M5.BtnA.wasHold() ? 1             // Determine if the button is held down, default threshold time is 500ms
            : M5.BtnA.wasClicked() ? 2          // Determine if the button has been clicked
            : M5.BtnA.wasPressed() ? 3          // Determine if the button has changed from a released state to a pressed state
            : M5.BtnA.wasReleased() ? 4         // Determine if the button is in a released state (after hold)
            : M5.BtnA.wasDecideClickCount() ? 5 // Trigger button click count, click count can be obtained through getClickCount API
            : 0;

  if (state)
  {
    int clickCount = M5.BtnA.getClickCount();
    ESP_LOGI(TAG, "BtnA:%s  count:%d", names[state], clickCount);

    //set state to wasDoubleClicked if state is wasDecideClickCount and clickCount is 2
    state = (state == 5 && clickCount == 2) ? 6 : state;

    //we don't need wasReleased (which is being set after hold)
    if (state == 1 | state == 2 | state == 3 | state == 4 | state == 6)
    {

      if (this->m5stack_button_sensor_number_ != nullptr)
        this->m5stack_button_sensor_number_->publish_state(state);
      if (this->m5stack_button_sensor_text_ != nullptr)
        this->m5stack_button_sensor_text_->publish_state(names[state]);

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

void M5StackButtonCompoundSensor::dump_config(){
  ESP_LOGCONFIG(TAG, "Button Compound Sensor");
}

}  // namespace m5stack_button_compound_sensor
}  // namespace esphome