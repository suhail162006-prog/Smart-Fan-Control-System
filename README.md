# Smart Fan Control & Climate Autonomy System

An embedded C++ climate-control system developed for the **ATmega328P (Arduino UNO)**. The system automatically regulates DC fan speed using **PWM based on real-time temperature**, while **PIR motion detection** manages system activation through non-blocking timing logic.

## Technical Specifications

| Component              | Specification                                   |
| ---------------------- | ----------------------------------------------- |
| **Microcontroller**    | ATmega328P (Arduino UNO)                        |
| **Firmware**           | Embedded C++ with non-blocking `millis()` logic |
| **Motor Driver**       | L293D H-Bridge                                  |
| **Temperature Sensor** | TMP36 analogue temperature sensor               |
| **Motion Sensor**      | Digital PIR sensor                              |
| **Circuit Protection** | 1N4007 reverse-polarity protection diode        |
| **Motor Supply**       | 12 V DC external battery                        |
| **Logic Supply**       | 5 V DC Arduino rail                             |

---

## Hardware Interfacing

### Pinout

| Component              | Arduino Pin | Function                    |
| ---------------------- | ----------: | --------------------------- |
| TMP36                  |        `A0` | Analogue temperature input  |
| PIR Sensor             |        `D5` | Digital motion detection    |
| L293D Enable (`3&4EN`) |        `D6` | PWM fan-speed control       |
| L293D `IN3`            |        `D3` | Motor direction control     |
| L293D `IN4`            |        `D4` | Motor direction control     |
| Red LED                |        `D2` | Standby / fan OFF indicator |
| Green LED              |        `D8` | Active / fan ON indicator   |

### Power Distribution

* **Logic Supply (`VCC1`):** 5 V DC from the Arduino rail
* **Motor Supply (`VCC2`):** 12 V DC external battery
* **Reverse-Polarity Protection:** 1N4007 diode installed in series with the motor supply
* **Measured Motor Rail:** approximately **11.7 V DC** under normal operating conditions

---

## Control Logic

The system uses a temperature-dependent state machine combined with a non-blocking PIR timeout.

| System State      | Motion       | Temperature |   PWM | Duty Cycle | Green LED | Red LED |
| ----------------- | ------------ | ----------- | ----: | ---------: | --------- | ------- |
| **Standby / OFF** | No / Timeout | Any         |   `0` |         0% | OFF       | ON      |
| **Cold Override** | Yes          | `< 10°C`    |   `0` |         0% | OFF       | ON      |
| **Low Speed**     | Yes          | `10–25°C`   |  `64` |        25% | ON        | OFF     |
| **Medium Speed**  | Yes          | `25–30°C`   | `128` |        50% | ON        | OFF     |
| **High Speed**    | Yes          | `> 30°C`    | `255` |       100% | ON        | OFF     |

### Motion Timeout

When motion is no longer detected, the system maintains the current active state for **15 seconds** using the Arduino `millis()` timer.

* No blocking `delay()` is used during timeout handling.
* The main control loop continues executing while the timer is monitored.
* Detecting motion again immediately resets the timeout counter.
* After 15 seconds without motion, the fan returns to **Standby / OFF**.

This allows motion detection, temperature monitoring, PWM control, and timeout handling to operate concurrently.

---

## System Behaviour

```text
                 ┌──────────────────┐
                 │  Read Sensors    │
                 └────────┬─────────┘
                          │
              ┌───────────┴───────────┐
              │                       │
        Motion Detected?        No Motion
              │                       │
             Yes                 Start/Check
              │                 15 s Timeout
              ▼                       │
       Read Temperature               │
              │                       │
       ┌──────┼──────┐                │
       │      │      │                │
     <10°C  10-25°C 25-30°C       Timeout?
       │      │      │                │
      OFF   25% PWM  50% PWM          │
              │                       │
              └───────┬───────────────┘
                      │
                    >30°C
                      │
                   100% PWM
```

---

## Verification & Testing

### PWM Response

Verified distinct PWM transitions at the programmed temperature thresholds:

* **Below 10°C:** Fan OFF
* **10–25°C:** 25% PWM
* **25–30°C:** 50% PWM
* **Above 30°C:** 100% PWM

### Non-Blocking Operation

The `millis()`-based timing system was tested to ensure the **15-second motion timeout operates without blocking the main control loop**.

### Power-Rail Verification

A multimeter was used to verify the motor supply rail, measuring approximately **11.7 V DC** after the reverse-polarity protection diode under full-load conditions.

---

## Key Engineering Concepts Demonstrated

* Embedded C++ programming
* ATmega328P microcontroller programming
* PWM motor-speed control
* Analogue sensor interfacing
* Digital motion detection
* State-machine-based control logic
* Non-blocking timing using `millis()`
* H-bridge motor control
* Reverse-polarity protection
* Hardware debugging and electrical measurement
* Sensor-driven autonomous control
