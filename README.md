# Air Quality Monitor - STM32 RTOS Project

A production-quality embedded system for indoor air quality monitoring, built on the STM32F446RE microcontroller with FreeRTOS and Modbus RTU communication.

## Project Overview

This firmware implements a complete air quality sensor system that acquires environmental data (temperature, humidity, VOC index), logs it to non-volatile memory, and exposes it via Modbus RTU for remote monitoring and control.

## Technical Architecture

**Hardware Platform:**
- **MCU:** STM32F446RE (ARM Cortex-M4, 180 MHz)
- **Sensors:** Sensirion SHT3x (temperature/humidity), SGP40 (VOC index)
- **Storage:** SPI FRAM for non-volatile data logging
- **Communication:** UART-based Modbus RTU slave

**Software Stack:**
- **RTOS:** FreeRTOS with custom task architecture
- **Drivers:** Register-level peripheral drivers using CMSIS (no HAL)
- **Communication Protocol:** Custom Modbus RTU implementation
- **Development:** Bare-metal embedded C with modular architecture

## Key Features & Technical Skills Demonstrated

### Low-Level Firmware Development
- **Register-level peripheral drivers** for GPIO, UART, SPI, I2C using CMSIS
- **Interrupt-driven communication** with DMA support
- **Hardware abstraction layers** for sensor and storage interfaces
- **Clock tree configuration** and power management

### Real-Time Operating System (FreeRTOS)
- **Multi-task architecture** with 5 concurrent application tasks:
  - Sensor Data Acquisition Task
  - System Health Monitor Task
  - Error Handler Task
  - Modbus Slave Task
  - Modbus Data Manager Task
- **Synchronization mechanisms:** Queues, semaphores, mutexes, task notifications, event groups
- **Non-blocking peripheral drivers** using RTOS primitives
- **Watchdog integration** for fault recovery

### Communication & Data Management
- **Custom Modbus RTU slave** implementation with register mapping
- **SPI FRAM driver** for reliable data logging
- **I2C sensor drivers** with error handling and retry logic
- **Structured data flow** between tasks using queues and shared memory

### Professional Software Engineering Practices
- **Modular architecture** with clear separation of concerns
- **Scalable design patterns** for embedded systems
- **Comprehensive error handling** and fault detection
- **Production-ready code structure** suitable for commercial products

## Technology Stack

| Layer | Technology |
|-------|-----------|
| **Hardware** | STM32F446RE, Sensirion sensors, SPI FRAM |
| **RTOS** | FreeRTOS (tasks, queues, semaphores, mutexes) |
| **Peripherals** | UART, SPI, I2C, ADC, DMA, Timers, GPIO |
| **Protocol** | Modbus RTU slave |
| **Language** | Embedded C |
| **Toolchain** | ARM GCC, STM32CubeIDE |

## System Architecture

```
┌─────────────────────────────────────────────┐
│          FreeRTOS Application Layer          │
├─────────────────────────────────────────────┤
│  Sensor Task  │  Health Monitor  │  Modbus   │
│  Error Handler │  Data Manager               │
├─────────────────────────────────────────────┤
│        Custom Peripheral Drivers             │
│    (UART, SPI, I2C, GPIO, ADC, Timers)      │
├─────────────────────────────────────────────┤
│              CMSIS Core                      │
├─────────────────────────────────────────────┤
│            STM32F446RE Hardware              │
└─────────────────────────────────────────────┘
```

## Project Highlights

- **Production-oriented design:** Emphasis on maintainability, scalability, and robustness
- **Complete system implementation:** From power-on to operational data acquisition and communication
- **Professional code quality:** Modular structure, comprehensive error handling, clear documentation
- **Real-world applicability:** Demonstrates skills directly transferable to commercial embedded products