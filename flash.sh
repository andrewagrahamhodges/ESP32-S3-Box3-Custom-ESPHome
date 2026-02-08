#!/bin/bash
set -e

# ESP32-S3-Box3 ESPHome Flash Script
# Usage: ./flash.sh --usb /dev/ttyUSB0 [config.yaml]
#        ./flash.sh --ota hostname.local [config.yaml]

CONFIG="${3:-s3b.yaml}"

show_help() {
    echo "ESP32-S3-Box3 Flash Script"
    echo ""
    echo "Usage:"
    echo "  ./flash.sh --usb <port> [config.yaml]   Flash via USB"
    echo "  ./flash.sh --ota <host> [config.yaml]   Flash via OTA (WiFi)"
    echo ""
    echo "Examples:"
    echo "  ./flash.sh --usb /dev/ttyUSB0"
    echo "  ./flash.sh --usb /dev/ttyACM0 s3b_no_sensors.yaml"
    echo "  ./flash.sh --ota esp32-s3box-3.local"
    echo "  ./flash.sh --ota 192.168.1.100 s3b.yaml"
    echo ""
    echo "Note: For USB flashing, hold the BOOT button while plugging in USB,"
    echo "      or hold BOOT and press RESET to enter bootloader mode."
}

if [[ $# -lt 2 ]]; then
    show_help
    exit 1
fi

MODE="$1"
TARGET="$2"

if [[ ! -f "$CONFIG" ]]; then
    echo "Error: Config file '$CONFIG' not found"
    exit 1
fi

DEVICE_NAME=$(grep -E '^\s*name:' "$CONFIG" | head -1 | awk '{print $2}' | tr -d '"' | tr -d "'")
FIRMWARE_PATH=".esphome/build/${DEVICE_NAME}/.pioenvs/${DEVICE_NAME}/firmware.bin"

case "$MODE" in
    --usb)
        echo "Flashing via USB to: $TARGET"
        echo "Config: $CONFIG"
        echo "----------------------------------------"

        if [[ ! -e "$TARGET" ]]; then
            echo "Error: Device $TARGET not found"
            echo ""
            echo "Available serial ports:"
            ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null || echo "  (none found)"
            echo ""
            echo "Tip: Hold BOOT button while connecting USB to enter bootloader mode"
            exit 1
        fi

        # Use esphome run which compiles and uploads
        docker compose run --rm --device="$TARGET" esphome run "$CONFIG" --device "$TARGET"
        ;;

    --ota)
        echo "Flashing via OTA to: $TARGET"
        echo "Config: $CONFIG"
        echo "----------------------------------------"

        # Use esphome upload for OTA
        docker compose run --rm esphome upload "$CONFIG" --device "$TARGET"
        ;;

    --help|-h)
        show_help
        exit 0
        ;;

    *)
        echo "Error: Unknown mode '$MODE'"
        echo ""
        show_help
        exit 1
        ;;
esac

echo ""
echo "========================================"
echo "Flash complete!"
echo "========================================"
