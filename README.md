# ESP32-S3-Box3-Custom Firmware
# The S3 BOX 3  is not just a voice assistant... it can do so much more!! 
Video demo available [HERE](<https://youtu.be/5W52TOQU_oM>)

> [!IMPORTANT]
> Please note that this firmware is intended to be used as a template for you to customise. You will need to edit the configuration to add your own entities from Home Assistant, and make other changes if you wish . This is not particularly difficult, we will provide as much information and support as possible.<br><br>
> You will need to navigate the configuration file, so a basic understanding of how ESPHome yaml works is an advantage. We strongly recommend that you use the included guides and refer to these as you should find most things covered.<br><br>
>I apreciate it is a lot of reading but it will make your life easier if you have not used ESPHome yaml previously.  Also check out the [Discord server](<https://discord.gg/U3SRYCG6Kp>) or [Discussions](<https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome/discussions>) section in the repo, for latest updates, new features, and to ask questions or make suggestions 👍
 
## This firmware will enable your S3 Box 3 to use the touch screen and home button, and configure the box to act like a dashboard for Home Assistant. Giving you the power to control your entitities and display sensor information. 
## The box will also be configured as a media player, giving you volume control (also improves the overall volume of the internal speaker compared to the ESPHome stock config) and easily broadcast messages to the device or stream media. Oh, and don't forget! it is also a Voice Assistant!!
The following features are now included with the latest version of this configuration and all accessible using the touchscreen or the HA ESPHome integration.
- Alarmo integration (This is not Home Assistant alarm control panel - it is the **Alarmo** integration)
- Timers
- Output all audio to external HA media player with a tap of a switch
- Advanced device information
  - WIFI connection info, Device uptime, ip address, hostname
- Brigtness control
- Volume control of internal and external speakers
- Screensaver with on screen timeout settings
- Radar motion sensor
- 24hr/12hr time switch
- Touch Screen buttons - to control your home
- Media Player with controls too for an external player
- Red circle button on front of display
- Top lefthand side hardware button
- Temp and Humidity Sensor
- Push to talk voice assistant
- Voice assistant with switchable 'on device' wake word or Home Assistant wakeword engine eg. Openwakeword

There are also some settings that can be changed within the config and these can be found at the very top under the `substitutions:` section more details of these can be found in the 'how to customise' Guide [click here](<https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome/blob/main/instructions/make%20it%20your%20own.md>)<BR>


To go straight to the web installer page [click here](<https://support.bbdl.co.uk>)<br>
 
To go straight to the config to use with the sensor dock [click here](<https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome/blob/main/s3b.yaml>)<br>
To go straight to a config for use without the sensor dock [click here](<https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome/blob/main/s3b_no_sensors.yaml>)<br>
 
To go straight to Installation Guide [click here](<https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome/blob/main/instructions/installation%20guide.md>)<br>
To go straight to the 'how to customise' Guide [click here](<https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome/blob/main/instructions/make%20it%20your%20own.md>)<BR>

 ![Screenshot 2024-09-27 142215](https://github.com/user-attachments/assets/b7c9f130-e6f8-4faa-a255-f2e366e93231)

 # Introduction.<br>
 >Firstly I am not a coder/developer/programmer. I Just know the small amount I do know from having a go, and spending many frustrated hours until things do what I want them to do. I apologise if the config makes you pro's cringe... as I am sure there will be many different ways that I could have made this config that would be the 'correct way' however it does what I want, so I will take that as a win.<br><br> 
This example config allows use of the touch screen and other sensors on the ESP32-S3-Box-3 using ESPhome for use with Home Assistant. The provided config is intended to be used as template for you to customise for your own purposes. I will provide as much detailed instruction as possible for you to achieve this.<br><br>
If you have any ideas, feedback or feel you could help make things 'even better' then it would be great to hear your thoughts.
#### Please Remember to backup any previous configs and associated files that you may have previously used for the device. <br><br>Using this config or installing the .bin via the web installer is at your own risk. They work for me... but I am not a professional.
 
## Installation and setup notes
follow the installation instructions [here](<https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome/blob/main/instructions/installation%20guide.md>) 
to unleash more of the devices potential.<br>
The s3box is quite a capable device and NOT just a voice assistant.

 ## Requirements
 * ESP32 S3 Box 3
 * ESPHome installation, either Home Assistant add-on, Local Cli install or docker.
   Please note that the compile of the config is fairly resource hungry and may fail on older devices with low ram and low processing power. However running ESPHome from a local machine with more power, will make this much faster and less likelihood of encountering errors.
   Details of how to run ESPHome in different ways, can be found [here](<https://esphome.io/guides/installing_esphome.html>) for OS installs or Docker [here](<https://esphome.io/guides/getting_started_command_line.html>) 
 * A Working installation of HomeAssistant preferably on the same network/vlan as the device, to avoid connection issues.
 * Samba Share Home Assistant add-on (available in the add-on store)or some other means of accessing your Home Assistant files and folders. you will need to access the config/esphome folder from your local computer in order to copy the required sound files. 
 * For Voice Asssistant to function you will either need a Nabu Casa (HomeAssistant Cloud) [subscription](<https://www.nabucasa.com/>) or the Whisper & Piper add-ons. If you don't intend to use the on device Micro Wake Word, you will require a wake word engine such as openwakeword. The following add-ons are all available in the Home Assistant add-on store Whisper, Piper & openwakeword

Click [here](<https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome/blob/main/instructions/installation%20guide.md>) if you have everything ready and are ready to start the installation.<br><br>

### I really hope you enjoy this project and I thank you for your support. If you have found this project useful and would like to buy me a coffee then the link is below ❤️<br>
<a href="https://www.buymeacoffee.com/BigBobba" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

---

# AI Context & Session State

> **Note:** This section serves as persistent context for AI coding agents. It is updated at the end of each development session to maintain continuity across sessions.

## Active Objectives

*What are we currently building?*

- Firmware updated to 2024.09.02 - currently testing
- Awaiting user feedback on new firmware behavior

## Technical Decisions

*Why did we choose specific libraries or architectures?*

| Decision | Rationale |
|----------|-----------|
| ESPHome framework | Native Home Assistant integration, OTA updates, YAML-based configuration |
| LVGL for display | Hardware-accelerated graphics, touch support, efficient memory usage |
| Micro Wake Word | On-device wake word detection reduces latency and cloud dependency |
| Modular YAML structure | `s3b.yaml` (with sensors) and `s3b_no_sensors.yaml` (without) for flexibility |

## Current Blockers

*What is stopping progress right now?*

- **Continuous conversation not supported**: The device cannot hold a conversation with Gemini/ChatGPT - it's limited to single question/answer exchanges. Each interaction requires a wake word. This is a limitation of Home Assistant Assist pipeline, not the ESP32 firmware.

## Next Steps

*The immediate tasks for the next session:*

1. [x] ~~Update `secrets.yaml` with WiFi credentials~~
2. [x] ~~Build firmware: `./build.sh s3b.yaml`~~
3. [x] ~~Flash via OTA: `./flash.sh --ota esp32-s3box-3.local`~~
4. [ ] Test firmware and report any issues (voice assistant, display, sensors, timers)
5. [ ] Verify device reconnects to Home Assistant properly
6. [ ] Investigate continuous conversation workarounds or Home Assistant feature requests

## Key File Mappings

*Which files hold the core logic for the current feature?*

| File | Purpose |
|------|---------|
| `s3b.yaml` | Main configuration for S3 Box 3 with sensor dock |
| `s3b_no_sensors.yaml` | Configuration for S3 Box 3 without sensor dock |
| `s3b_import.yaml` | Shared imports and common configuration |
| `docker-compose.yml` | Docker-based ESPHome build environment |
| `build.sh` | Script to compile YAML to firmware .bin |
| `flash.sh` | Script to flash firmware via USB or OTA |
| `secrets.yaml.example` | Template for WiFi credentials |
| `instructions/installation guide.md` | Step-by-step installation instructions |
| `instructions/make it your own.md` | Customization guide for users |

## Device Configuration

*Current device settings discovered during this session:*

| Setting | Value |
|---------|-------|
| Device name | `esp32-s3box-3` |
| Friendly name | `ESP32-S3-Box-3` |
| External media player | `living_room_speaker_2` |
| HA host | `http://homeassistant.local:8123` |
| Has sensor dock | Yes (temperature, humidity, presence) |
| API encryption | None (open) |
| OTA password | None (open) |
| Current firmware | **2024.09.02** (flashed 2026-01-25) |
| Previous firmware | 2024.09.01 (ESPHome 2024.12.2) |

## Firmware Update Analysis

*Comparison of current vs repo firmware:*

| Aspect | Current (2024.09.01) | Repo (2024.09.02) |
|--------|---------------------|-------------------|
| Audio system | `adf_pipeline` (external) | Native ESPHome `speaker`/`media_player` |
| ESP-IDF | 4.4.x | 5.4.0 |
| Min ESPHome | 2024.9.0 | 2025.2.0 |
| External deps | `esphome_audio` repo | None |

**Benefits of updating:**
- No external audio component dependency (more stable)
- New mixer speaker architecture for better audio
- Piper TTS crash fix
- Built-in timer sounds (no HTTP fetch)
- Better buffer stability

**Note:** Update is worthwhile for stability but won't enable continuous conversation.

## Session Log

*Summary of recent development sessions:*

| Date | Summary |
|------|---------|
| 2026-01-25 | Added AI Context & Session State section to README for AI agent persistence |
| 2026-01-25 | Created Docker-based build environment (docker-compose.yml, build.sh, flash.sh, secrets.yaml.example) |
| 2026-01-25 | Analyzed current device config from HA, compared firmware versions, identified continuous conversation as key limitation |
| 2026-01-25 | **Successfully flashed firmware 2024.09.02** via Docker build environment. Device now running new native audio pipeline. Testing in progress. |

## Known Issues / Bugs

*Bugs found but not yet fixed:*

- **Continuous conversation**: Device requires wake word for every interaction. Limitation is in HA Assist pipeline, not firmware. No current workaround available.

---

## AI Session Prompts

*Use these prompts to manage AI coding sessions:*

### Wrap Up Prompt (End of Session)
> "We are wrapping up for the day. I need you to perform a 'State Dump' into the `README.md` under the 'AI Context & Session State' section.
> 
> Please:
> 1. Summarize exactly what we accomplished today.
> 2. Document any changes made to the project structure or logic that might not be obvious.
> 3. Explicitly list the **'Next Steps'** so that when I return tomorrow, you (or another AI) will know exactly where to pick up.
> 4. Mention any bugs we found but didn't fix yet.
> 
> Once the README is updated, provide a brief summary of the status here and say goodbye."

### Pick Up Prompt (Start of Session)
> "We are starting a new session. Please read the `README.md` file, specifically the 'AI Context & Session State' section, to understand the current state of the project, recent progress, and the planned next steps.
> 
> Once you have processed the context:
> 1. Briefly summarize your understanding of our current goal.
> 2. Propose the first task from the 'Next Steps' list that we should tackle right now.
> 3. List the files you'll need to examine to get started."

---

*Last updated: 2026-01-25 (session wrapped up, firmware flashed, awaiting test results)*
