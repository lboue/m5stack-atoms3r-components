#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <M5Unified.h>

namespace esphome {
namespace m5stack_button_text_sensor {

class M5StackButtonTextSensor : public text_sensor::TextSensor, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};

}  // namespace m5stack_button_text_sensor
}  // namespace esphome