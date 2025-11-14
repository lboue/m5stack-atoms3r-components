#include "BMI270.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace bmi270 {

static const char *const TAG = "bmi270";


void BMI270Component::internal_setup_(int stage) {

  this->setup_complete_ = true;
}

void BMI270Component::setup() { this->internal_setup_(0); }
void BMI270Component::dump_config() {
  ESP_LOGCONFIG(TAG, "BMI270:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with BMI270 failed!");
  }
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "Acceleration X", this->accel_x_sensor_);
  LOG_SENSOR("  ", "Acceleration Y", this->accel_y_sensor_);
  LOG_SENSOR("  ", "Acceleration Z", this->accel_z_sensor_);
  LOG_SENSOR("  ", "Gyro X", this->gyro_x_sensor_);
  LOG_SENSOR("  ", "Gyro Y", this->gyro_y_sensor_);
  LOG_SENSOR("  ", "Gyro Z", this->gyro_z_sensor_);
  LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
}

i2c::ErrorCode BMI270Component::read_le_int16_(uint8_t reg, int16_t *value, uint8_t len) {
  uint8_t raw_data[len * 2];
  // read using read_register because we have little-endian data, and read_bytes_16 will swap it
  i2c::ErrorCode err = this->read_register(reg, raw_data, len * 2, true);
  if (err != i2c::ERROR_OK) {
    return err;
  }
  for (int i = 0; i < len; i++) {
    value[i] = (int16_t) ((uint16_t) raw_data[i * 2] | ((uint16_t) raw_data[i * 2 + 1] << 8));
  }
  return err;
}

void BMI270Component::update() {
  if (!this->setup_complete_) {
    return;
  }

  ESP_LOGV(TAG, "    Updating BMI270...");
  int16_t data[6];
  if (this->read_le_int16_(BMI270_REGISTER_DATA_GYRO_X_LSB, data, 6) != i2c::ERROR_OK) {
    this->status_set_warning();
    return;
  }

  float gyro_x = (float) data[0] / (float) INT16_MAX * 2000.f;
  float gyro_y = (float) data[1] / (float) INT16_MAX * 2000.f;
  float gyro_z = (float) data[2] / (float) INT16_MAX * 2000.f;
  float accel_x = (float) data[3] / (float) INT16_MAX * 16 * GRAVITY_EARTH;
  float accel_y = (float) data[4] / (float) INT16_MAX * 16 * GRAVITY_EARTH;
  float accel_z = (float) data[5] / (float) INT16_MAX * 16 * GRAVITY_EARTH;

  int16_t raw_temperature;
  if (this->read_le_int16_(BMI270_REGISTER_DATA_TEMP_LSB, &raw_temperature, 1) != i2c::ERROR_OK) {
    this->status_set_warning();
    return;
  }
  float temperature = (float) raw_temperature / (float) INT16_MAX * 64.5f + 23.f;

  ESP_LOGD(TAG,
           "Got accel={x=%.3f m/s², y=%.3f m/s², z=%.3f m/s²}, "
           "gyro={x=%.3f °/s, y=%.3f °/s, z=%.3f °/s}, temp=%.3f°C",
           accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z, temperature);

  if (this->accel_x_sensor_ != nullptr)
    this->accel_x_sensor_->publish_state(accel_x);
  if (this->accel_y_sensor_ != nullptr)
    this->accel_y_sensor_->publish_state(accel_y);
  if (this->accel_z_sensor_ != nullptr)
    this->accel_z_sensor_->publish_state(accel_z);

  if (this->temperature_sensor_ != nullptr)
    this->temperature_sensor_->publish_state(temperature);

  if (this->gyro_x_sensor_ != nullptr)
    this->gyro_x_sensor_->publish_state(gyro_x);
  if (this->gyro_y_sensor_ != nullptr)
    this->gyro_y_sensor_->publish_state(gyro_y);
  if (this->gyro_z_sensor_ != nullptr)
    this->gyro_z_sensor_->publish_state(gyro_z);

  this->status_clear_warning();
}
float BMI270Component::get_setup_priority() const { return setup_priority::DATA; }

}  // namespace BMI270
}  // namespace esphome
