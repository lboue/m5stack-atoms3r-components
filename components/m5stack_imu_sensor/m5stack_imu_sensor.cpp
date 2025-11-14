#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "m5stack_imu_sensor.h"

namespace esphome {
namespace m5stack_imu_sensor {

static const char *const TAG = "m5stack_imu_sensor.sensor";

const float GRAVITY_EARTH = 9.80665f;

void M5StackIMUSensor::setup() {
  M5.begin();
}
void M5StackIMUSensor::dump_config() {
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
  LOG_SENSOR("  ", "Mag X", this->mag_x_sensor_);
  LOG_SENSOR("  ", "Mag Y", this->mag_y_sensor_);
  LOG_SENSOR("  ", "Mag Z", this->mag_z_sensor_);
  LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
}

void M5StackIMUSensor::update() {
  ESP_LOGV(TAG, "    Updating BMI270...");

  auto imu_update = M5.Imu.update();
  if (imu_update)
  {
    // Obtain data on the current value of the IMU.
    auto data = M5.Imu.getImuData();
    float temperature;
    M5.Imu.getTemp(&temperature);

    float gyro_x = (float) data.gyro.x;
    float gyro_y = (float) data.gyro.y;
    float gyro_z = (float) data.gyro.z;
    float accel_x = (float) data.accel.x;
    float accel_y = (float) data.accel.y;
    float accel_z = (float) data.accel.z;
    float mag_x = (float) data.mag.x;
    float mag_y = (float) data.mag.y;
    float mag_z = (float) data.mag.z;


    ESP_LOGD(TAG,
          "Got accel={x=%.3f m/s², y=%.3f m/s², z=%.3f m/s²}, "
          "gyro={x=%.3f °/s, y=%.3f °/s, z=%.3f °/s}, "
          "mag={x=%.3f m/s², y=%.3f m/s², z=%.3f m/s²}, "
          "temp=%.3f°C",
          accel_x, accel_y, accel_z,
          gyro_x, gyro_y, gyro_z, 
          mag_x, mag_y, mag_z, 
          temperature);

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

      if (this->mag_x_sensor_ != nullptr)
        this->mag_x_sensor_->publish_state(mag_x);
      if (this->mag_y_sensor_ != nullptr)
        this->mag_y_sensor_->publish_state(mag_y);
      if (this->mag_z_sensor_ != nullptr)
        this->mag_z_sensor_->publish_state(mag_z);
  }
}
float M5StackIMUSensor::get_setup_priority() const { return setup_priority::DATA; }

}  // namespace m5stack_imu_sensor
}  // namespace esphome