#!/bin/bash
set -e

# ESP32-S3-Box3 ESPHome Build Script
# Usage: ./build.sh [config.yaml]

CONFIG="${1:-s3b.yaml}"

if [[ ! -f "$CONFIG" ]]; then
    echo "Error: Config file '$CONFIG' not found"
    echo "Available configs:"
    ls -1 *.yaml 2>/dev/null | grep -E '^s3b' || echo "  (none found)"
    exit 1
fi

if [[ ! -f "secrets.yaml" ]]; then
    echo "Error: secrets.yaml not found"
    echo "Create it from the template:"
    echo "  cp secrets.yaml.example secrets.yaml"
    echo "  nano secrets.yaml"
    exit 1
fi

echo "Building firmware from: $CONFIG"
echo "----------------------------------------"

docker compose run --rm esphome compile "$CONFIG"

# Find the built firmware
DEVICE_NAME=$(grep -E '^\s*name:' "$CONFIG" | head -1 | awk '{print $2}' | tr -d '"' | tr -d "'")
FIRMWARE_PATH=".esphome/build/${DEVICE_NAME}/.pioenvs/${DEVICE_NAME}/firmware.bin"

if [[ -f "$FIRMWARE_PATH" ]]; then
    echo ""
    echo "========================================"
    echo "Build successful!"
    echo "Firmware: $FIRMWARE_PATH"
    echo "Size: $(du -h "$FIRMWARE_PATH" | cut -f1)"
    echo "========================================"
    echo ""
    echo "To flash via USB:"
    echo "  ./flash.sh --usb /dev/ttyUSB0"
    echo ""
    echo "To flash via OTA:"
    echo "  ./flash.sh --ota ${DEVICE_NAME}.local"
else
    echo ""
    echo "Build completed but firmware not found at expected path."
    echo "Check .esphome/build/ directory for output."
fi
