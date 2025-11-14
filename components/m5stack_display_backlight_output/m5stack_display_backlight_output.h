#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace m5stack_display_backlight_output {

class M5StackDisplayBacklightOutput : public output::FloatOutput, public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void write_state(float state) override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA - 1; }

protected:
  bool write_register_(uint8_t reg, uint8_t value);

  // Storage for last I2C error seen
  esphome::i2c::ErrorCode last_error_;
};


} //namespace m5stack_display_backlight_output
} //namespace esphome