Uses the [M5Unified library button class](https://docs.m5stack.com/en/arduino/m5unified/button_class) ([Github](https://github.com/m5stack/M5Unified)) to expose the state of button A as a number and as a text.

The enum for the returned integer is `{ "none", "hold", "wasClick", "click", "wasHold", "wasDecideClickCount", "wasDoubleClicked" };`

### example configuration:

```
sensor:
  - platform: m5stack_button_sensor
    name: Button State Number
```