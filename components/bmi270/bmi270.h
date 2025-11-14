#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

// #include "bmi270-api.h"

namespace esphome {
namespace bmi270 {

class BMI270Sensor : public PollingComponent, public i2c::I2CDevice {
  private:

  public:
    void setup() override;
    void dump_config() override;

    void update() override;

    float get_setup_priority() const override;

    void set_accel_x_sensor(sensor::Sensor *accel_x_sensor) { accel_x_sensor_ = accel_x_sensor; }
    void set_accel_y_sensor(sensor::Sensor *accel_y_sensor) { accel_y_sensor_ = accel_y_sensor; }
    void set_accel_z_sensor(sensor::Sensor *accel_z_sensor) { accel_z_sensor_ = accel_z_sensor; }
    void set_gyro_x_sensor(sensor::Sensor *gyro_x_sensor) { gyro_x_sensor_ = gyro_x_sensor; }
    void set_gyro_y_sensor(sensor::Sensor *gyro_y_sensor) { gyro_y_sensor_ = gyro_y_sensor; }
    void set_gyro_z_sensor(sensor::Sensor *gyro_z_sensor) { gyro_z_sensor_ = gyro_z_sensor; }
    void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }

  protected:

  enum imu_spec_t
  {
    imu_spec_none  = 0,
    imu_spec_accel = 0b0001,
    imu_spec_gyro  = 0b0010,
    imu_spec_mag   = 0b0100,
  };

  struct point3d_i16_t
  {
    union
    {
      int16_t value[3];
      struct
      {
        int16_t x;
        int16_t y;
        int16_t z;
      };
    } __attribute__((__packed__));
  };

  struct imu_raw_data_t
  {
    union
    {
      int16_t value[10] = { 0, };
      point3d_i16_t sensor[3];
      struct
      {
        point3d_i16_t accel;
        point3d_i16_t gyro;
        point3d_i16_t mag;
        int16_t temp;
      } __attribute__((__packed__));
    };
  };

  struct imu_convert_param_t
  {
    union
    {
      float value[3] = { 8.0f / 32768.0f, 2000.0f / 32768.0f, 10.0f * 4912.0f / 32768.0f };
      struct
      {
        float accel_res;
        float gyro_res;
        float mag_res;
      };
    };
    float temp_res = 1.0f;
    float temp_offset = 0.0f;
  };

    sensor::Sensor *accel_x_sensor_{nullptr};
    sensor::Sensor *accel_y_sensor_{nullptr};
    sensor::Sensor *accel_z_sensor_{nullptr};
    sensor::Sensor *gyro_x_sensor_{nullptr};
    sensor::Sensor *gyro_y_sensor_{nullptr};
    sensor::Sensor *gyro_z_sensor_{nullptr};
    sensor::Sensor *temperature_sensor_{nullptr};

    imu_spec_t internal_setup_();
    bool setup_complete_{false};

    bool _upload_file(const uint8_t *config_data, size_t write_len);

    bool write_register_(uint8_t reg, const uint8_t *value, size_t len = 1);
    bool read_register_(uint8_t reg, uint8_t data);

    bool auxSetupMode(uint8_t i2c_addr);
    bool auxWriteRegister8(uint8_t reg, uint8_t data);
    uint8_t auxReadRegister8(uint8_t reg);

    imu_spec_t getImuRawData(imu_raw_data_t* data);
    void getConvertParam(imu_convert_param_t* param);
    bool getTemp(int16_t* t);

    // Storage for last I2C error seen
    esphome::i2c::ErrorCode last_error_;
};

}  // namespace bmi270
}  // namespace esphome