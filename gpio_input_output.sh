#!/bin/bash

CHIP_INPUT=gpiochip0
INPUT_PIN=14
CHIP_OUTPUT=gpiochip1
OUTPUT_PIN=10

# Keep track of previous state to avoid repeated setting
PREV_STATE=""

led_toggle() {
    TOGGLE=$(gpioget $CHIP_INPUT $INPUT_PIN)

    # Only update the output if state has changed
    if [ "$TOGGLE" != "$PREV_STATE" ]; then
        if [ "$TOGGLE" -eq 0 ]; then
            gpioset $CHIP_OUTPUT $OUTPUT_PIN=1
        else
            gpioset $CHIP_OUTPUT $OUTPUT_PIN=0
        fi
        PREV_STATE=$TOGGLE
    fi
}

while true; do
    led_toggle
    sleep 0.5
done
