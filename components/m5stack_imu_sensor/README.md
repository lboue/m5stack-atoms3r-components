Uses the [M5Unified library](https://docs.m5stack.com/en/arduino/m5unified/helloworld) ([Github](https://github.com/m5stack/M5Unified)) to expose the BMI270 as well as the stacked BMM150.

### example configuration:

```
sensor:
  - platform: m5stack_imu_sensor
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
    temperature:
      name: "IMU Temperature"
```