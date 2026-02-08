import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.const import CONF_ID
from esphome.components import microphone

DEPENDENCIES = ["microphone", "wifi"]

CONF_MICROPHONE = "microphone"
CONF_VPS_HOST = "vps_host"
CONF_VPS_PORT = "vps_port"
CONF_VPS_PATH = "vps_path"

robbie_voice_ns = cg.esphome_ns.namespace("robbie_voice")
RobbieVoice = robbie_voice_ns.class_("RobbieVoice", cg.Component)

# Actions
StartListeningAction = robbie_voice_ns.class_("StartListeningAction", automation.Action)
StopListeningAction = robbie_voice_ns.class_("StopListeningAction", automation.Action)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(RobbieVoice),
        cv.Required(CONF_MICROPHONE): cv.use_id(microphone.Microphone),
        cv.Required(CONF_VPS_HOST): cv.string,
        cv.Optional(CONF_VPS_PORT, default=8081): cv.port,
        cv.Optional(CONF_VPS_PATH, default="/voice"): cv.string,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    mic = await cg.get_variable(config[CONF_MICROPHONE])
    cg.add(var.set_microphone(mic))

    cg.add(var.set_vps_host(config[CONF_VPS_HOST]))
    cg.add(var.set_vps_port(config[CONF_VPS_PORT]))
    cg.add(var.set_vps_path(config[CONF_VPS_PATH]))


ROBBIE_VOICE_ACTION_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(RobbieVoice),
    }
)


@automation.register_action("robbie_voice.start", StartListeningAction, ROBBIE_VOICE_ACTION_SCHEMA)
async def robbie_voice_start_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, paren)


@automation.register_action("robbie_voice.stop", StopListeningAction, ROBBIE_VOICE_ACTION_SCHEMA)
async def robbie_voice_stop_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, paren)
