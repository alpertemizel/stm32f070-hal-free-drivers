# STM32F070RB Bare-Metal Interrupt-Driven Driver Library

A lightweight, register-level (bare-metal) C driver library developed from scratch for the STM32F070RB microcontroller. This repository demonstrates low-level microcontroller firmware development, focusing on both polling and non-blocking interrupt-driven (IT) communication without utilizing STMicroelectronics' Hardware Abstraction Layer (HAL) or Low-Layer (LL) libraries.

The primary goal of this project is to showcase a deep understanding of ARM Cortex-M0 architecture, memory-mapped registers, NVIC (Nested Vectored Interrupt Controller) configuration, and peripheral clock management.

## Supported Peripherals and Features

Currently, the library includes fully custom implementations for the following peripherals, featuring both standard polling and advanced interrupt modes:

### 1. USART Driver
* Asynchronous Mode: Full-duplex communication support.
* Custom Baudrate Calculation: Configurable baudrate settings using system clock parameters.
* Polling-Based I/O: Transmit and receive mechanisms via status register polling.
* Interrupt-Driven (IT) I/O: Non-blocking transmission and reception utilizing USART RXNE/TXE interrupts and basic ISR handling.

### 2. SPI Driver
* Master Mode Configuration: Full-duplex synchronous data transfer.
* Hardware/Software Slave Management: Flexible NSS (Slave Select) management.
* Configurable Clock Phase/Polarity: Support for different SPI modes (CPOL/CPHA).
* Interrupt-Based Data Transfer: Non-blocking data exchange using SPI transmit and receive buffer interrupts for optimized CPU utilization.

Note: More peripherals (I2C, Timers, ADC) are planned to be added progressively.

## Hardware Setup

The library is developed and tested on the NUCLEO-F070RB development board. 

* MCU: STM32F070RBT6 (ARM Cortex-M0, 48MHz)
* On-Board User Button: Connected to pin PC13 (configured via EXTI/GPIO registers, suitable for external interrupt handling).
* Debugging/Serial Console: USART pins are mapped to route seamlessly via the ST-LINK on-board debugger for real-time serial monitoring.

## Getting Started

### Prerequisites
To build and run this project, you will need:
* An IDE/Toolchain (e.g., STM32CubeIDE, Keil MDK, or VS Code with GNU Arm Embedded Toolchain).
* An ST-LINK debugger (embedded on the Nucleo board).

### Installation and Usage
1. Clone the repository:
   ```bash
   git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)
2. Open the project in your preferred IDE.

3. Include the peripheral header files in your main application:
   #include "usart.h"
   #include "spi.h"
4. Initialize the system clock and the required peripheral structures. You can check the main.c file for a complete example.

Project Structure

├── Inc/
│   ├── spi.h            # SPI driver registers and function prototypes
│   └── usart.h          # USART driver registers and function prototypes
├── Src/
│   ├── spi.c            # SPI peripheral implementation
│   ├── usart.c          # USART peripheral implementation
│   └── main.c           # Application entry point and example usage
└── README.md

License
This project is open-source and available under the MIT License.
