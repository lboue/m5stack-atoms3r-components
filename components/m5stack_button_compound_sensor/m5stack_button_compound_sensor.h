#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace m5stack_button_compound_sensor {

class M5StackButtonCompoundSensor : public Component  {
 public:
 void set_m5stack_button_sensor_number(sensor::Sensor *m5stack_button_sensor_number) { m5stack_button_sensor_number_ = m5stack_button_sensor_number; }
 void set_m5stack_button_sensor_text(text_sensor::TextSensor *m5stack_button_sensor_text) { m5stack_button_sensor_text_ = m5stack_button_sensor_text; }

  void setup() override;
  void loop() override;
  void dump_config() override;

  protected:
    sensor::Sensor *m5stack_button_sensor_number_;
    text_sensor::TextSensor *m5stack_button_sensor_text_;
};

}  // namespace m5stack_button_compound_sensor
}  // namespace esphome
