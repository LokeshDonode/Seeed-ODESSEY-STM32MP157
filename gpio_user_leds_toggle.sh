#!/bin/bash

# LED mappings
LED0_CHIP=gpiochip8
LED0_LINE=0

LED1_CHIP=gpiochip8
LED1_LINE=1

LED2_CHIP=gpiochip7
LED2_LINE=15

# Turn LED ON
led_on() {
    gpioset $1 $2=1
}

# Turn LED OFF
led_off() {
    gpioset $1 $2=0
}

# Play one LED like a piano key
play_led() {
    CHIP=$1
    LINE=$2

    led_on  $CHIP $LINE
    sleep 0.15       # duration LED stays ON (adjust to taste)
    led_off $CHIP $LINE
}

# Continuous piano sequence
while true; do
    play_led $LED0_CHIP $LED0_LINE
    play_led $LED1_CHIP $LED1_LINE
    play_led $LED2_CHIP $LED2_LINE
done
