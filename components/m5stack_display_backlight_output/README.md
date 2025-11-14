

### example configuration:

```
i2c:
  sda: 45
  scl: 0

light:
  - platform: monochromatic
    output: displaybacklightoutput
    initial_state:
      state: true
    restore_mode: ALWAYS_ON
    name: M5Stack Display Backlight
    id: displaybacklight
    icon: mdi:television-ambient-light

output:
  - platform: m5stack_display_backlight_output
    id: displaybacklightoutput
```