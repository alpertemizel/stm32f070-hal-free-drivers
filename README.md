# STM32F070RB Bare-Metal Driver Library

A lightweight, register-level (bare-metal) C driver library developed from scratch for the STM32F070RB microcontroller. This repository demonstrates low-level microcontroller firmware development without utilizing STMicroelectronics' Hardware Abstraction Layer (HAL) or Low-Layer (LL) libraries.

The primary goal of this project is to showcase a deep understanding of ARM Cortex-M0 architecture, memory-mapped registers, and peripheral clock configurations.

## Supported Peripherals and Features

Currently, the library includes fully custom implementations for the following peripherals:

### 1. USART Driver
* Asynchronous Mode: Full-duplex communication support.
* Custom Baudrate Calculation: Configurable baudrate settings using system clock parameters.
* Polling-Based I/O: Safe transmit and receive mechanisms via status register polling.

### 2. SPI Driver
* Master Mode Configuration: Full-duplex synchronous data transfer.
* Hardware/Software Slave Management: Flexible NSS (Slave Select) management.
* Configurable Clock Phase/Polarity: Support for different SPI modes (CPOL/CPHA).

Note: More peripherals (I2C, Timers, ADC) are planned to be added progressively.

## Hardware Setup

The library is developed and tested on the NUCLEO-F070RB development board. 

* MCU: STM32F070RBT6 (ARM Cortex-M0, 48MHz)
* On-Board User Button: Connected to pin PC13 (configured via EXTI/GPIO registers).
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
