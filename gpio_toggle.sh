# Creating heartbeat effect to LED connected to GPIO_B10 and GND 
#!/bin/bash

# GPIO chip and line for GPIO_B10
CHIP=gpiochip1
LINE=10

# Function to turn LED ON
led_on() {
  gpioset $CHIP $LINE=1
}

# Function to turn LED OFF
led_off() {
  gpioset $CHIP $LINE=0
}

while true; do
  # First beat
  led_on
  sleep 0.1
  led_off
  sleep 0.1

  # Second beat (shorter pause)
  led_on
  sleep 0.1
  led_off
  sleep 0.6

  # Pause before next heartbeat
  sleep 0.8
done
