# BMI270_BMM150 componant

The `BMI270_BMM150` componant reports:
 * Accelerometer range is set at [-4, +4]g -/+0.122 mg.
 * Gyroscope range is set at [-2000, +2000] dps +/-70 mdps.
 * Magnetometer range is set at [-400, +400] uT +/-0.014 uT.
 * Accelerometer output data rate is fixed at 104 Hz.
 * Gyroscope output data rate is fixed at 104 Hz.
 * Magnetometer output data rate is fixed at 20 Hz.

## AtomS3R

[AtomS3R](https://docs.m5stack.com/en/core/AtomS3R)

**Config**

```yaml
external_components:
    # https://github.com/DennisGaida/m5stack-atoms3r-components/tree/main
  - source: github://DennisGaida/m5stack-atoms3r-components@main
    components: [ bmi270_bmm150 ]
    refresh: always

i2c:
  sda: 45
  scl: 0
  scan: false # Disable I2C scan to speed up boot time
  frequency: 400kHz
  # timeout: 200us # doesn't work with idf

sensor:
  #- platform: m5stack_imu_sensor
  - platform: bmi270_bmm150
    update_interval: 5s
    acceleration_x:
      name: "IMU Accel X"
    acceleration_y:
      name: "IMU Accel Y"
    acceleration_z:
      name: "IMU Accel z"
    gyroscope_x:
      name: "IMU Gyro X"
    gyroscope_y:
      name: "IMU Gyro Y"
    gyroscope_z:
      name: "IMU Gyro z"
    field_strength_x:
      name: "IMU Mag X"
    field_strength_y:
      name: "IMU Mag Y"
    field_strength_z:
      name: "IMU Mag z"
    #temperature:
    #  name: "IMU Temperature"
```

