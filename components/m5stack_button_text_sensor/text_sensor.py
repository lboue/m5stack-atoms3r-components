import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor


m5stack_button_text_sensor_ns = cg.esphome_ns.namespace("m5stack_button_text_sensor")
M5StackButtonTextSensor = m5stack_button_text_sensor_ns.class_(
    "M5StackButtonTextSensor", text_sensor.TextSensor, cg.Component
    )

CONFIG_SCHEMA = text_sensor.text_sensor_schema(
    M5StackButtonTextSensor, icon="mdi:button-pointer"
    ).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    await cg.register_component(var, config)
