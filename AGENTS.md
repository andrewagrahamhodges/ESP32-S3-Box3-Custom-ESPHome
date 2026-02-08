# AGENTS.md

> Context and instructions for AI coding agents working on this project.

## Project Overview

Custom ESPHome firmware for the ESP32-S3-Box-3 device, integrating with Home Assistant. The firmware turns the S3 Box 3 into a voice assistant, media player, and touch-screen dashboard for controlling Home Assistant entities.

Originally forked from [BigBobbas/ESP32-S3-Box3-Custom-ESPHome](https://github.com/BigBobbas/ESP32-S3-Box3-Custom-ESPHome).

## Repository Structure

| Path | Purpose |
|------|---------|
| `s3b.yaml` | Main ESPHome config (with sensor dock) |
| `s3b_no_sensors.yaml` | Config variant without sensor dock |
| `s3b_import.yaml` | Shared imports and common config |
| `s3b_og.yaml` | Original unmodified config for reference |
| `secrets.yaml` | WiFi credentials and keys (gitignored) |
| `secrets.yaml.example` | Template for secrets.yaml |
| `docker-compose.yml` | Docker-based ESPHome build environment |
| `build.sh` | Compile YAML to firmware binary |
| `flash.sh` | Flash firmware via USB or OTA |
| `fonts/` | Custom display fonts (.ttf) |
| `images/` | Display UI images (idle, listening, error, etc.) |
| `sounds/` | Audio files (wake sound, timer finished) |
| `instructions/` | User guides (installation, customization) |

## Setup

### Prerequisites

- Docker and Docker Compose
- Home Assistant instance on the same network
- ESP32-S3-Box-3 hardware

### First-time setup

```bash
cp secrets.yaml.example secrets.yaml
# Edit secrets.yaml with your WiFi credentials
```

### Build firmware

```bash
./build.sh s3b.yaml
```

### Flash firmware

```bash
# Via OTA (WiFi)
./flash.sh --ota esp32-s3box-3.local

# Via USB (hold BOOT button while connecting)
./flash.sh --usb /dev/ttyUSB0
```

## Code Style and Conventions

- Configuration is written in ESPHome YAML
- The `substitutions:` section at the top of each config contains user-editable values
- Substitutions below the `DO NOT CHANGE` comment are internal and should not be modified casually
- Device name (`esp32-s3box-3`) is used for mDNS hostname -- changing it after HA adoption causes connection issues
- All sensitive values (WiFi credentials, API keys) go in `secrets.yaml`, never committed

## Key Technical Decisions

| Decision | Rationale |
|----------|-----------|
| ESPHome framework | Native Home Assistant integration, OTA updates, YAML config |
| Native speaker/media_player | Replaced external `adf_pipeline` for stability (as of firmware 2024.09.02) |
| Micro Wake Word | On-device wake word detection, reduces latency and cloud dependency |
| Docker build environment | Consistent builds, avoids local dependency issues |
| Multiple config variants | `s3b.yaml` (with sensors) and `s3b_no_sensors.yaml` (without) for hardware flexibility |

## Device Configuration

| Setting | Value |
|---------|-------|
| Device name | `esp32-s3box-3` |
| Friendly name | `ESP32-S3-Box-3` |
| Board | `esp32s3box` / 16MB flash / octal PSRAM |
| Framework | ESP-IDF 5.4.0 |
| Min ESPHome | 2025.2.0 |
| External media player | `living_room_speaker_2` |
| HA host | `http://homeassistant.local:8123` |
| Wake words | alexa, hey_jarvis, okay_nabu, hey_mycroft |

## Important Warnings

- **Do not commit `secrets.yaml`** -- it contains WiFi credentials. It is in `.gitignore`.
- **The `.esphome/` directory** is a build cache. It is in `.gitignore` and should not be committed. If it appears in the repo, remove it from tracking.
- **Changing `name:` in substitutions** after the device is adopted by Home Assistant will break the connection.
- **Builds are resource-heavy** -- may fail on low-RAM machines. Use Docker or a capable host.

## Known Limitations

- **No continuous conversation**: The device requires a wake word for every interaction. This is a Home Assistant Assist pipeline limitation, not a firmware issue.
- **Single TTS voice speed**: The `tts_voice_speed` substitution must match your TTS provider (Nabu Casa: 24000, Piper: 16000, ElevenLabs: 44100).

## Testing

After flashing new firmware:

1. Verify device connects to WiFi and Home Assistant
2. Test voice assistant with each configured wake word
3. Test touch screen buttons and display pages
4. Test media player (internal speaker + external)
5. Test timers (start, cancel, finish with sound)
6. Test screensaver activation and wake-on-touch
7. Verify sensor readings (temperature, humidity) if using sensor dock

## Session State

### Active Objectives

- Firmware updated to 2024.09.02 -- testing in progress
- Repository migrated to personal GitHub (andrewagrahamhodges)

### Recent Changes

| Date | Summary |
|------|---------|
| 2026-02-08 | Migrated repo to personal GitHub, set BigBobbas as upstream |
| 2026-01-25 | Created Docker build environment (docker-compose.yml, build.sh, flash.sh) |
| 2026-01-25 | Flashed firmware 2024.09.02 with native audio pipeline |

### Next Steps

1. Test firmware (voice assistant, display, sensors, timers)
2. Verify device reconnects to Home Assistant properly
3. Investigate continuous conversation workarounds
4. Clean up `.esphome/` cached files from git history if present

### Bugs

- **Continuous conversation**: Requires wake word for every interaction. HA Assist pipeline limitation. No current workaround.
