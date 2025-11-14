Uses the [M5Unified library](https://docs.m5stack.com/en/arduino/m5unified/helloworld) ([Github](https://github.com/m5stack/M5Unified)) to expose the state of button A.

Possible values for the state are `{ "none", "wasHold", "wasClicked", "wasPressed", "wasReleased", "wasDecidedCount" }`

### example configuration:

```
text_sensor:
  - platform: m5stack_button_text_sensor
    name: Button State
```