import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import UNIT_EMPTY

m5stack_button_sensor_ns = cg.esphome_ns.namespace("m5stack_button_sensor")
M5StackButtonSensor = m5stack_button_sensor_ns.class_(
    "M5StackButtonSensor", sensor.Sensor, cg.Component
    )

CONFIG_SCHEMA = sensor.sensor_schema(
    M5StackButtonSensor, unit_of_measurement=UNIT_EMPTY, icon="mdi:button-pointer", accuracy_decimals=0
    ).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)