#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <M5Unified.h>

namespace esphome {
namespace m5stack_button_sensor {

class M5StackButtonSensor : public sensor::Sensor, public Component  {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};

}  // namespace m5stack_button_sensor
}  // namespace esphome
