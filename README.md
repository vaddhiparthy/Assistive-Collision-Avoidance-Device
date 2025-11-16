# Assistive Collision Avoidance Device for the Visually Impaired

An embedded mobility-assist system that detects obstacles using ultrasonic ranging and provides audio alerts for visually impaired users. Built using an AT89C52 microcontroller, HC-SR04 ultrasonic module, voice playback hardware, and a 16×2 LCD for calibration and debugging.

## Overview

This device uses ultrasonic echo timing to measure distance in real time and delivers spoken warnings based on proximity thresholds. The system is low-cost, fully embedded, and designed for hands-free operation.

## Features

- Real-time ultrasonic ranging (2–350 cm, ~3 mm accuracy)
- Distance-based voice alerts via prerecorded audio module
- 16×2 LCD display for debugging and calibration
- Embedded 5V regulated power supply
- Suitable for wearable or handheld mobility aids

## System Architecture

```
[HC-SR04 Ultrasonic Sensor] → Echo Timing → [AT89C52 MCU] → Select Line → [Voice Output Module] → [Speaker]
                                          │
                                          └──→ [16×2 LCD Display]
```

## Hardware Components

### Microcontroller – AT89C52
- MCS-51 compatible 8-bit CPU (up to 33 MHz)
- 8 KB Flash, 256 B RAM
- 32 GPIO lines
- 3× 16-bit timers/counters
- 8 interrupt sources
- Watchdog timer support

### Ultrasonic Sensor – HC-SR04
- Range: 2 cm → 350 cm
- Resolution: ~3 mm
- Sends 8 pulses of 40 kHz ultrasound and measures echo time

### LCD Display – 16×2
- HD44780-compatible character LCD
- Displays measured distance

### Voice Output Module
- Prerecorded alert messages
- Controlled by MCU select lines
- Output to external speaker

### Power Supply
- Step-down transformer
- DB107 full-bridge rectifier
- 7805 regulator for +5V DC

## Distance Measurement Logic

```
distance_cm = (echo_high_time_seconds × 340 m/s) / 2
```

## Firmware Workflow

1. Trigger HC-SR04 with 10 µs HIGH pulse  
2. Wait for echo return  
3. Measure echo HIGH duration  
4. Compute distance  
5. Update LCD  
6. Trigger voice alert  
7. Loop

## Example Outputs

| Distance (cm) | LCD Text       | Voice Alert                          |
|---------------|----------------|---------------------------------------|
| 44            | Obj at 44 Cm   | "Object under 50 centimeters"         |
| 83            | Obj at 83 Cm   | "Object under 100 centimeters"        |
| 129           | Obj at 129 Cm  | "Object under 150 centimeters"        |
| 181           | Obj at 181 Cm  | "Object under 200 centimeters"        |
| 353 / 500     | Obj at XXX Cm  | "Obstacle is out of range"            |

## Software Toolchain

### Keil µVision
### Flash Magic
### Embedded C

## Advantages

- Hands-free obstacle detection
- No complex training needed
- Robust in crowded environments
- Low-cost and scalable

## Applications

- Visually impaired mobility
- Industrial collision avoidance
- Parking and proximity sensing

## Author

**V. S. Surya Sameer**  
Under the guidance of  
**Dr. S. V. Ranganayakulu** – Dean (R&D)
