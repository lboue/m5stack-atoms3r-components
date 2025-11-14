Uses the [M5Unified library](https://docs.m5stack.com/en/arduino/m5unified/helloworld) ([Github](https://github.com/m5stack/M5Unified)) to expose the state of button A as a number.

The enum for the returned integer is `{ "none", "wasHold", "wasClicked", "wasPressed", "wasReleased", "wasDeciedCount" }`

### example configuration:

```
sensor:
  - platform: m5stack_button_sensor
    name: Button State Number
```