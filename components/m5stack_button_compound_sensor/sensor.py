import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, text_sensor
from esphome.const import CONF_ID, UNIT_EMPTY

# necessary to auto-load the text_sensor component if used together with sensor
# alternatively we could have one sensor.py and one text_sensor.py file
AUTO_LOAD = ["text_sensor"]

m5stack_button_compound_sensor_ns = cg.esphome_ns.namespace("m5stack_button_compound_sensor")
M5StackButtonCompoundSensor = m5stack_button_compound_sensor_ns.class_(
    "M5StackButtonCompoundSensor", cg.Component
    )

CONF_SENSOR_STATE_NUMBER = "m5stack_button_sensor_number"
CONF_SENSOR_STATE_TEXT = "m5stack_button_sensor_text"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(M5StackButtonCompoundSensor),
        cv.Optional(CONF_SENSOR_STATE_NUMBER): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY, icon="mdi:button-pointer", accuracy_decimals=0
        ),
        cv.Optional(CONF_SENSOR_STATE_TEXT): text_sensor.text_sensor_schema(
            icon="mdi:button-pointer"
        )
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if m5stack_button_sensor_number_config := config.get(CONF_SENSOR_STATE_NUMBER):
        sens = await sensor.new_sensor(m5stack_button_sensor_number_config)
        cg.add(var.set_m5stack_button_sensor_number(sens))

    if m5stack_button_sensor_text_config := config.get(CONF_SENSOR_STATE_TEXT):
        sens = await text_sensor.new_text_sensor(m5stack_button_sensor_text_config)
        cg.add(var.set_m5stack_button_sensor_text(sens))