# Smart Home Automation System

**Embedded Systems | C Programming | Arduino Due (SAM3X8E)**

**Course Project:** Computer Systems Engineering (DST1)  
**Institution:** Halmstad University  
**Year:** 2023  
**Development Environment:** IAR Embedded Workbench

## 1. Project Overview

This project presents the design and implementation of an embedded Smart Home Automation System developed as part of the Computer Systems Engineering course at Halmstad University.

The system is built around the Arduino Due platform, powered by the ARM Cortex-M3-based Atmel SAM3X8E microcontroller.

The main objective is to monitor indoor environmental conditions and provide automated control of selected home functions, including temperature monitoring, sunlight tracking, motorized shading, and alarm management.

The system integrates multiple hardware components with embedded C software, demonstrating sensor integration, interrupt handling, data management, and real-time user interaction.

## 2. Key Features

### Temperature Monitoring and Data Logging
- Periodic temperature measurements using a temperature sensor.
- Storage of timestamped temperature readings using linked lists.
- Calculation of minimum, maximum, and average temperature values.
- Configurable temperature sampling frequency.
- Memory management that replaces older recordings when the storage limit is reached.

### Automated Shading System
- Sunlight detection using two photosensors.
- Analog-to-digital conversion (ADC) for light intensity measurements.
- Servo motor control based on differences in light intensity.
- Automatic adjustment of the shading position in response to changing light conditions.

### Temperature Alarm Management
- User-configurable upper and lower temperature thresholds.
- Alarm activation when temperatures exceed the configured limits.
- LED indicators displaying normal and alarm conditions.
- Manual acknowledgement and reset through the user interface.

### LCD Display and User Interface
- LCD-based presentation of time, date, and temperature information.
- Keypad-controlled menu navigation and system configuration.
- Graphical representation of recorded temperature data.
- Display of minimum, average, and maximum temperature measurements.

### Calendar and Time Management
- Software-based calendar functionality using SysTick.
- Display of date and time.
- User configuration of calendar settings.
- Timestamping of recorded temperature measurements.

### Fast Mode and Testing
- Accelerated temperature logging for testing purposes.
- Simulation of 30 minutes within one second.
- Pre-recorded data used to verify temperature graph visualization.

## 3. Hardware Components

The prototype includes the following components:

| Component | Purpose |
|---|---|
| Arduino Due (Atmel SAM3X8E) | Main embedded processing platform |
| Temperature Sensor | Temperature measurement |
| Two Photosensors | Light intensity measurement and sunlight tracking |
| RC Servo Motor | Motorized shading control |
| LCD Display | User interface and data visualization |
| Numeric Keypad | Menu navigation and configuration |
| LEDs | Alarm and system status indication |
| Switch / Push Buttons | User interaction and interrupt handling |
| Breadboard and Wiring | Hardware integration and prototyping |

## 4. Software Architecture

The embedded software is written primarily in C and organized into functional modules.

Important modules include:

- `main.c` – Main application logic.
- `temperature_sensor.c` – Temperature measurement.
- `light_sensor.c` – Photosensor data acquisition.
- `servo.c` – Servo motor control.
- `shader.c` – Automatic shading functionality.
- `display.c` – LCD interface.
- `keypad.c` – Keypad input handling.
- `user_interface.c` – Menu navigation and interaction.
- `date_and_time.c` – Calendar functionality.
- `data_structure_linkedList.c` – Dynamic data storage.
- `make_temperature_data.c` – Temperature data processing.
- `interrupt_handlers.c` – Interrupt handling.

The system combines hardware peripherals, sensor measurements, user inputs, and software control functions to support automated environmental monitoring.

## 5. Technical Implementation

The project demonstrates embedded programming concepts including:

- **Embedded C:** Modular development for ARM-based microcontrollers.
- **GPIO:** Digital input/output for peripheral interaction.
- **ADC:** Analog acquisition from photosensors.
- **PWM:** Servo motor control.
- **Interrupt Handling:** Processing hardware and timer-related events.
- **SysTick:** Software timing and calendar updates.
- **Linked Lists:** Dynamic management of recorded sensor data.
- **LCD Graphics:** Presentation of temperature statistics and graphical information.

## 6. Development Environment

The project was developed for the Arduino Due (Atmel SAM3X8E) using IAR Embedded Workbench.

The repository contains C source files, header files, startup code, and IAR project configuration files.

The existing project configuration should be maintained when opening or building the application, as changing the source file locations may require updating project paths and include directories.

## 7. Challenges and Limitations

Several technical challenges were addressed during development:

**Memory Management:** The system used a limited data storage capacity of 341 recording nodes, requiring automatic removal of older records to allow continued logging.

**Hardware Integration:** Coordinating temperature measurements, photosensor readings, servo control, and LCD updates required iterative testing and configuration.

**Dual Photosensor Acquisition:** Reading two photosensors required ADC configuration and interrupt handling to obtain the appropriate sensor data.

**LCD Visualization:** Custom display functions were developed to present information and visualize temperature measurements.

**Calendar Limitations:** The implemented calendar simplified date management by treating each month as having 30 days, rather than implementing full calendar rules.

**System Reliability:** The project report documents occasional unexpected program interruptions, indicating an area for future improvement.

## 8. Project Outcome

The project resulted in an integrated embedded smart home prototype combining environmental monitoring, user interaction, automated shading control, temperature alarms, and data visualization.

The implementation provided practical experience in embedded C programming, microcontroller peripherals, memory management, hardware-software integration, and system testing.

## 9. Documentation

The original DST1 project report and requirement specification describe the system's objectives, implementation, results, and limitations.

## 10. Academic Context

This project was developed as a collaborative university coursework project at Halmstad University in 2023.

The repository documents the original academic implementation and its technical development.

## 11. Future Improvements

Potential further development includes:

- More accurate calendar handling.
- Improved system stability and error handling.
- More robust sensor-data validation.
- Extended system testing.
- Improved code documentation and maintainability.
- Enhanced graphical data visualization.
