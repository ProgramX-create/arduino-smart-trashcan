# arduino-smart-trashcan

#Arduino Smart Trashcan(Engineering Class Final Project)

# Arduino Smart Trash Can (V8 Architecture)

This is the code for the touch-free smart trash can I built as my engineering class final project using an Arduino, an ultrasonic distance sensor, and a servo motor.

## Why I Built This
For my final project, I wanted to fix a common issue with basic DIY automation. Most beginner tutorials just slam a motor open and closed instantly, which breaks the physical lid hinge and wastes battery. 

My code fixes this by using smart filters, exact angle boundaries, and automatic motor power shutoffs to make the lid open smoothly and save energy.

## How My Code Works
Here is a breakdown of the custom features I programmed into the script:

1. **Glitch Filtering**: Ultrasonic sensors can get confused if something is too close. I coded a safe zone constraint (`8cm` to `25cm`) so the trash can only opens when a real hand is intentionally placed in front of it.
2. **Angle Calibration**: To stop the lid from flipping too far back and breaking the hinges, I restricted the movement loop to top out at exactly `88 degrees` instead of a full 90 or 180.
3. **Battery Saving Loop**: Normal motors constantly hum and drain power even when they aren't moving. I used `.attach()` and `.detach()` commands so the motor only turns on when moving the lid, and completely shuts off while waiting.
4. **Smooth Movements**: Instead of snapping open instantly, I wrote a `for` loop that moves the motor in small 2-degree steps with a tiny 15-millisecond pause. This gives the lid a smooth, motorized lift instead of a jerky motion.

## Pin Connections
- **Pin 5**: Sensor Transmitter (Trig)
- **Pin 6**: Sensor Receiver (Echo)
- **Pin 9**: Servo Motor Control Line

## Video


https://github.com/user-attachments/assets/f56059d0-c126-459b-aafe-9083b9d9a084


