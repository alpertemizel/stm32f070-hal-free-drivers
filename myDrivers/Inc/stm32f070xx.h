#ifndef INC_STM32F070XX_H_
#define INC_STM32F070XX_H_

#include <stdint.h>
#include <string.h>
#include <stddef.h>

/*
 *
 * Microprocessor Defines
 *
 */
#define NVIC_ISER0					( (uint32_t*)(0xE000E100) )

#define __IO volatile

#define SET_BIT(REG, BIT)   		((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)			( (REG) &= ~(BIT) )
#define READ_BIT(REG, BIT)			( (REG) & 	(BIT) )
#define UNUSED(x)					(void)x

typedef enum
{
	DISABLE = 0x0U,
	ENABLE = !DISABLE
}FunctionalState_t;

/*
 *
 *  IRQ Numbers of MCU == Vector Table
 *
 */

typedef enum
{
	EXTI0_IRQNumber  = 5,
	EXTI1_IRQNumber  = 5,

	EXTI2_IRQNumber  = 6,
	EXTI3_IRQNumber  = 6,

	EXTI4_IRQNumber  = 7,
	EXTI5_IRQNumber  = 7,
	EXTI6_IRQNumber  = 7,
	EXTI7_IRQNumber  = 7,
	EXTI8_IRQNumber  = 7,
	EXTI9_IRQNumber  = 7,
	EXTI10_IRQNumber = 7,
	EXTI11_IRQNumber = 7,
	EXTI12_IRQNumber = 7,
	EXTI13_IRQNumber = 7,
	EXTI14_IRQNumber = 7,
	EXTI15_IRQNumber = 7,

	SPI2_IRQNumber = 26,

	USART1_IRQNumber = 27,
	USART2_IRQNumber = 28,
}IRQNumber_TypeDef_t;

/*
 * 	Memory Base Addresses
 *
 */

#define FLASH_BASE_ADDR				(0x08000000UL) /* Flash Base Address (up to 1MB) */
#define SRAM_BASE_ADDR				(0x20000000UL) /* SRAM Base Address 16KB */

/*
 *	Peripheral Base Addresses
 *
 */

#define PERIPH_BASE_ADDR			(0x40000000UL) 						/* Base Address for All peripherals */

#define APB_BASE_ADDR				(PERIPH_BASE_ADDR) 					/* APB Bus Domain Base Address 		*/
#define AHB1_BASE_ADDR				(PERIPH_BASE_ADDR + 0x20000UL) 		/* AHB1 Bus Domain Base Address 	*/
#define AHB2_BASE_ADDR				(PERIPH_BASE_ADDR + 0x8000000UL)	/* AHB2 Bus Domain Base Address 	*/

/*
 *	APB Peripheral Base Addresses
 *
 */

#define TIM1_BASE_ADDR				(APB_BASE_ADDR + 0x12C00UL)			/* Timer 1 	Base Address			*/
#define TIM3_BASE_ADDR				(APB_BASE_ADDR + 0x00400UL)			/* Timer 3 	Base Address			*/
#define TIM6_BASE_ADDR				(APB_BASE_ADDR + 0x01000UL)			/* Timer 6 	Base Address			*/
#define TIM7_BASE_ADDR				(APB_BASE_ADDR + 0x01400UL)			/* Timer 7 	Base Address			*/
#define TIM14_BASE_ADDR				(APB_BASE_ADDR + 0x02000UL)			/* Timer 14 Base Address			*/
#define TIM15_BASE_ADDR				(APB_BASE_ADDR + 0x14000UL)			/* Timer 15 Base Address			*/
#define TIM16_BASE_ADDR				(APB_BASE_ADDR + 0x14400UL)			/* Timer 16 Base Address			*/
#define TIM17_BASE_ADDR				(APB_BASE_ADDR + 0x14800UL)			/* Timer 17 Base Address			*/

#define SPI1_BASE_ADDR				(APB_BASE_ADDR + 0x13000UL)			/* SPI 1	Base Address			*/
#define SPI2_BASE_ADDR				(APB_BASE_ADDR + 0x03800UL)			/* SPI 2	Base Address			*/

#define USART1_BASE_ADDR			(APB_BASE_ADDR + 0x13800UL)			/* USART 1 	Base Address			*/
#define USART2_BASE_ADDR			(APB_BASE_ADDR + 0x04400UL)			/* USART 2 	Base Address			*/
#define USART3_BASE_ADDR			(APB_BASE_ADDR + 0x04800UL)			/* USART 3 	Base Address			*/
#define USART4_BASE_ADDR			(APB_BASE_ADDR + 0x04C00UL)			/* USART 4 	Base Address			*/
#define USART5_BASE_ADDR			(APB_BASE_ADDR + 0x05000UL)			/* USART 5 	Base Address			*/
#define USART6_BASE_ADDR			(APB_BASE_ADDR + 0x11400UL)			/* USART 6 	Base Address			*/

#define I2C1_BASE_ADDR				(APB_BASE_ADDR + 0x05400UL)			/* I2C 1 	Base Address			*/
#define I2C2_BASE_ADDR				(APB_BASE_ADDR + 0x05800UL)			/* I2C 2 	Base Address			*/

#define EXTI_BASE_ADDR				(APB_BASE_ADDR + 0x10400UL)			/* EXTI 	Base Address 			*/
#define SYSCFG_BASE_ADDR			(APB_BASE_ADDR + 0x10000UL)			/* SYSCFG 	Base Address			*/

/*
 *	AHB1 Peripheral Base Addresses
 *
 */

#define DMA_BASE_ADDR				(AHB1_BASE_ADDR)					/* DMA 		Base Address			*/
#define RCC_BASE_ADDR				(AHB1_BASE_ADDR + 0x01000UL)		/* RCC  	Base Address			*/
#define FLASH_interface_BASE_ADDR	(AHB1_BASE_ADDR + 0x02000UL)		/* FLASH_i 	Base Address			*/
#define CRC_BASE_ADDR				(AHB1_BASE_ADDR + 0x03000UL)		/* CRC	 	Base Address			*/

/*
 *	AHB2 Peripheral Base Addresses
 *
 */

#define GPIOA_BASE_ADDR				(AHB2_BASE_ADDR)					/* GPIOA 	Base Address			*/
#define GPIOB_BASE_ADDR				(AHB2_BASE_ADDR + 0x0400UL)			/* GPIOB  	Base Address			*/
#define GPIOC_BASE_ADDR				(AHB2_BASE_ADDR + 0x0800UL)			/* GPIOC 	Base Address			*/
#define GPIOD_BASE_ADDR				(AHB2_BASE_ADDR + 0x0C00UL)			/* GPIOD	Base Address			*/
#define GPIOF_BASE_ADDR				(AHB2_BASE_ADDR + 0x1400UL)			/* GPIOF	Base Address			*/



/*
 *	Peripheral Structure Definitions
 *
 */

typedef struct {
	__IO uint32_t MODER; 			/*!< GPIO port mode register 					Address Offset = 0x0000 		*/
	__IO uint32_t OTYPER; 			/*!< GPIO port output type register 			Address Offset = 0x0004 		*/
	__IO uint32_t OSPEEDR; 			/*!< GPIO port output speed register 			Address Offset = 0x0008 		*/
	__IO uint32_t PUPDR; 			/*!< GPIO port pull-up/pull-down register 		Address Offset = 0x000C 		*/
	__IO uint32_t IDR; 				/*!< GPIO port input data register 				Address Offset = 0x0010 		*/
	__IO uint32_t ODR; 				/*!< GPIO port output data register 			Address Offset = 0x0014 		*/
	__IO uint32_t BSRR; 			/*!< GPIO port bit set/reset register 			Address Offset = 0x0018 		*/
	__IO uint32_t LCKR; 			/*!< GPIO port configuration lock register 		Address Offset = 0x001C 		*/
	__IO uint32_t AFR[2]; 			/*!< GPIO alternate function register 			Address Offset = 0x0020 		*/
	__IO uint32_t BRR; 				/*!< GPIO port bit reset register 				Address Offset = 0x0028 		*/
} GPIO_TypeDef_t;

typedef struct {
	__IO uint32_t CR; 				/*!< Clock control register						Address Offset = 0x0000 		*/
	__IO uint32_t CFGR; 			/*!< Clock configuration register 				Address Offset = 0x0004 		*/
	__IO uint32_t CIR; 				/*!< Clock interrupt register 					Address Offset = 0x0008 		*/
	__IO uint32_t APB2RSTR; 		/*!< APB peripheral reset register 2			Address Offset = 0x000C 		*/
	__IO uint32_t APB1RSTR; 		/*!< APB peripheral reset register 1 			Address Offset = 0x0010 		*/
	__IO uint32_t AHBENR; 			/*!< AHB peripheral clock enable register 		Address Offset = 0x0014 		*/
	__IO uint32_t APB2ENR; 			/*!< APB peripheral clock enable register 2 	Address Offset = 0x0018 		*/
	__IO uint32_t APB1ENR; 			/*!< APB peripheral clock enable register 1		Address Offset = 0x001C 		*/
	__IO uint32_t BDCR; 			/*!< RTC domain control register 				Address Offset = 0x0020 		*/
	__IO uint32_t CSR; 				/*!< Control/status register 					Address Offset = 0x0024 		*/
	__IO uint32_t AHBRSTR; 			/*!< AHB peripheral reset register 				Address Offset = 0x0028 		*/
	__IO uint32_t CFGR2; 			/*!< Clock configuration register 2 			Address Offset = 0x002C 		*/
	__IO uint32_t CFGR3; 			/*!< Clock configuration register 3				Address Offset = 0x0030 		*/
	__IO uint32_t CR2; 				/*!< Clock control register 2 					Address Offset = 0x0034 		*/
} RCC_TypeDef_t;


typedef struct {
	__IO uint32_t CFGR1;			/*!< SYSCFG configuration register 1 			Address Offset = 0x0000 		*/
	__IO uint32_t RESERVED;			/*!< Reserved									Address Offset = 0x0004 		*/
	__IO uint32_t EXTI_CR[4];		/*!< SYSCFG EXTI configuration register 1		Address Offset = 0x0008 		*/
	__IO uint32_t CFGR2;			/*!< SYSCFG configuration register 2			Address Offset = 0x0018 		*/
} SYSCFG_TypeDef_t;

typedef struct {
	__IO uint32_t IMR;				/*!< interrupt mask register					Address Offset = 0x0000 		*/
	__IO uint32_t EMR;				/*!< Event mask register						Address Offset = 0x0004 		*/
	__IO uint32_t RTSR;				/*!< Rising trigger selection register			Address Offset = 0x0008 		*/
	__IO uint32_t FTSR;				/*!< Falling trigger selection register			Address Offset = 0x000C 		*/
	__IO uint32_t SWIER;			/*!< Software interrupt event register			Address Offset = 0x0010 		*/
	__IO uint32_t PR;				/*!< Pending register							Address Offset = 0x0014 		*/
} EXTI_TypeDef_t;

typedef struct {
	__IO uint32_t CR1;				/*!< SPI control register 1						Address Offset = 0x0000			*/
	__IO uint32_t CR2;				/*!< SPI control register 2						Address Offset = 0x0004			*/
	__IO uint32_t SR;				/*!< SPI status register 						Address Offset = 0x0008			*/
	__IO uint32_t DR;				/*!< SPI data register							Address Offset = 0x000C			*/
	__IO uint32_t CRCPR;			/*!< SPI CRC polynomial register				Address Offset = 0x0010			*/
	__IO uint32_t RXCRCR;			/*!< SPI Rx CRC register						Address Offset = 0x0014			*/
	__IO uint32_t TXCRCR;			/*!< SPI Tx CRC register						Address Offset = 0x0018			*/
} SPI_TypeDef_t;

typedef struct {
	__IO uint32_t CR1;				/*!< USART control register 1					Address Offset = 0x0000			*/
	__IO uint32_t CR2;				/*!< USART control register 2					Address Offset = 0x0004			*/
	__IO uint32_t CR3;				/*!< USART control register 3					Address Offset = 0x0008			*/
	__IO uint32_t BRR;				/*!< USART baud rate register					Address Offset = 0x000C			*/
	__IO uint32_t Reserved;			/*!< Reserved									Address Offset = 0x0010			*/
	__IO uint32_t RTOR;				/*!< USART receiver timeout register			Address Offset = 0x0014			*/
	__IO uint32_t RQR;				/*!< USART request register						Address Offset = 0x0018			*/
	__IO uint32_t ISR;				/*!< USART interrupt and status register		Address Offset = 0x001C			*/
	__IO uint32_t ICR;				/*!< USART interrupt flag clear register		Address Offset = 0x0020			*/
	__IO uint32_t RDR;				/*!< USART receive data register				Address Offset = 0x0024			*/
	__IO uint32_t TDR;				/*!< USART transmit data register				Address Offset = 0x0028			*/
} USART_TypeDef_t;


#define GPIOA						( (GPIO_TypeDef_t *)(GPIOA_BASE_ADDR) )
#define GPIOB						( (GPIO_TypeDef_t *)(GPIOB_BASE_ADDR) )
#define GPIOC						( (GPIO_TypeDef_t *)(GPIOC_BASE_ADDR) )
#define GPIOD						( (GPIO_TypeDef_t *)(GPIOD_BASE_ADDR) )
#define GPIOF						( (GPIO_TypeDef_t *)(GPIOF_BASE_ADDR) )

#define RCC							( (RCC_TypeDef_t *)(RCC_BASE_ADDR) )

#define SYSCFG						( (SYSCFG_TypeDef_t*)(SYSCFG_BASE_ADDR) )

#define EXTI						( (EXTI_TypeDef_t*)(EXTI_BASE_ADDR) )

#define SPI1						( (SPI_TypeDef_t*)(SPI1_BASE_ADDR) )
#define SPI2						( (SPI_TypeDef_t*)(SPI2_BASE_ADDR) )

#define USART1						( (USART_TypeDef_t*)(USART1_BASE_ADDR) )
#define USART2						( (USART_TypeDef_t*)(USART2_BASE_ADDR) )
#define USART3						( (USART_TypeDef_t*)(USART3_BASE_ADDR) )
#define USART4						( (USART_TypeDef_t*)(USART4_BASE_ADDR) )
#define USART5						( (USART_TypeDef_t*)(USART5_BASE_ADDR) )
#define USART6						( (USART_TypeDef_t*)(USART6_BASE_ADDR) )

/*
 *	Bit Definitions
 *
 */

#define RCC_AHBENR_GPIOAEN_Pos			(17U)									// RCC AHBENR register GPIOAEN Bit Position
#define RCC_AHBENR_GPIOAEN_Msk			(0x1 << RCC_AHBENR_GPIOAEN_Pos)			// RCC AHBENR register GPIOAEN Bit Mask
#define RCC_AHBENR_GPIOAEN				RCC_AHBENR_GPIOAEN_Msk					// RCC AHBENR register GPIOAEN Bit Macro

#define RCC_AHBENR_GPIOBEN_Pos			(18U)									// RCC AHBENR register GPIOBEN Bit Position
#define RCC_AHBENR_GPIOBEN_Msk			(0x1 << RCC_AHBENR_GPIOBEN_Pos)			// RCC AHBENR register GPIOBEN Bit Mask
#define RCC_AHBENR_GPIOBEN				RCC_AHBENR_GPIOBEN_Msk					// RCC AHBENR register GPIOBEN Bit Macro

#define RCC_AHBENR_GPIOCEN_Pos			(19U)									// RCC AHBENR register GPIOCEN Bit Position
#define RCC_AHBENR_GPIOCEN_Msk			(0x1 << RCC_AHBENR_GPIOCEN_Pos)			// RCC AHBENR register GPIOCEN Bit Mask
#define RCC_AHBENR_GPIOCEN				RCC_AHBENR_GPIOCEN_Msk					// RCC AHBENR register GPIOCEN Bit Macro

#define RCC_AHBENR_GPIODEN_Pos			(20U)									// RCC AHBENR register GPIODEN Bit Position
#define RCC_AHBENR_GPIODEN_Msk			(0x1 << RCC_AHBENR_GPIODEN_Pos)			// RCC AHBENR register GPIODEN Bit Mask
#define RCC_AHBENR_GPIODEN				RCC_AHBENR_GPIODEN_Msk					// RCC AHBENR register GPIODEN Bit Macro

#define RCC_APB2ENR_SYSCFGCOMPEN_Pos	(0U)									//RCC APB2ENR register SYSCFGCOMPEN Bit Position
#define RCC_APB2ENR_SYSCFGCOMPEN_Msk	(0x1U << RCC_APB2ENR_SYSCFGCOMPEN_Pos)	//RCC APB2ENR register SYSCFGCOMPEN Bit Mask
#define RCC_APB2ENR_SYSCFGCOMPEN		RCC_APB2ENR_SYSCFGCOMPEN_Msk			//RCC APB2ENR register SYSCFGCOMPEN Bit Macro

#define RCC_APB2ENR_SPI1EN_Pos			(12U)									//RCC APB2ENR register SPI1 Bit Position
#define RCC_APB2ENR_SPI1EN_Msk			(0x1U << RCC_APB2ENR_SPI1EN_Pos)		//RCC APB2ENR register SPI1 Bit Mask
#define RCC_APB2ENR_SPI1EN				RCC_APB2ENR_SPI1EN_Msk					//RCC APB2ENR register SPI1 Bit Macro

#define RCC_APB1ENR_SPI2EN_Pos			(14U)									//RCC APB1ENR register SPI2 Bit Position
#define RCC_APB1ENR_SPI2EN_Msk			(0x1U << RCC_APB1ENR_SPI2EN_Pos)		//RCC APB1ENR register SPI2 Bit Mask
#define RCC_APB1ENR_SPI2EN				RCC_APB1ENR_SPI2EN_Msk					//RCC APB1ENR register SPI2 Bit Macro

#define RCC_APB2ENR_USART1EN_Pos		(14U)
#define RCC_APB2ENR_USART1EN_Msk		(0x1U << RCC_APB2ENR_USART1EN_Pos)
#define RCC_APB2ENR_USART1EN			RCC_APB2ENR_USART1EN_Msk

#define RCC_APB1ENR_USART2EN_Pos		(17U)
#define RCC_APB1ENR_USART2EN_Msk		(0x1U << RCC_APB1ENR_USART2EN_Pos)
#define RCC_APB1ENR_USART2EN			RCC_APB1ENR_USART2EN_Msk

#define RCC_APB1ENR_USART3EN_Pos		(18U)
#define RCC_APB1ENR_USART3EN_Msk		(0x1U << RCC_APB1ENR_USART3EN_Pos)
#define RCC_APB1ENR_USART3EN			RCC_APB1ENR_USART3EN_Msk

#define RCC_APB1ENR_USART4EN_Pos		(19U)
#define RCC_APB1ENR_USART4EN_Msk		(0x1U << RCC_APB1ENR_USART4EN_Pos)
#define RCC_APB1ENR_USART4EN			RCC_APB1ENR_USART4EN_Msk

#define RCC_APB1ENR_USART5EN_Pos		(20U)
#define RCC_APB1ENR_USART5EN_Msk		(0x1U << RCC_APB1ENR_USART5EN_Pos)
#define RCC_APB1ENR_USART5EN			RCC_APB1ENR_USART5EN_Msk

#define RCC_APB2ENR_USART6EN_Pos		(5U)
#define RCC_APB2ENR_USART6EN_Msk		(0x1U << RCC_APB2ENR_USART6EN_Pos)
#define RCC_APB2ENR_USART6EN			RCC_APB2ENR_USART6EN_Msk

#define SPI_SR_Busy						(7U)									//SPI SR Register Busy Flag Bit
#define SPI_SR_TxE						(1U)									//SPI SR Register TxE Flag Bit
#define SPI_SR_RxNE						(0U)									//SPI SR Register RxNE Flag Bit

#define SPI_CR1_SPE						(6U)									//SPI Register SPE Start Bit

#define SPI_CR2_TXEIE					(7U)									//SPI Register TXEIE Start Bit
#define SPI_CR2_RXNEIE					(6U)									//SPI Register RXNEIE Start Bit
#define SPI_CR2_DS_Pos					(8U)									//SPI Register DS Start Bit

#define SPI_CR2_DS_8BIT    				(0x7U)									//SPI Data Size Definitions
#define SPI_CR2_DS_16BIT   				(0xFU)									//SPI Data Size Definitions

#define USART_CR1_UE					(0x0U)
#define USART_CR1_TxEIE					(0x7U)
#define USART_CR1_RxNEIE				(0x5U)

#define USART_CR2_STOP					(12U)

#define USART_ISR_TxE					(7U)
#define USART_ISR_TxC					(6U)
#define USART_SR_RxNE					(5U)


/*
 *
 *	Flag Definitions
 *
 */

#define SPI_TxE_FLAG					(0x1U << SPI_SR_TxE)
#define SPI_Busy_FLAG					(0x1U << SPI_SR_Busy)
#define SPI_Flag_RxNE					(0x1U << SPI_SR_RxNE)

#define USART_TxE_FLAG					(0x1U << USART_ISR_TxE)
#define USART_TxC_FLAG					(0x1U << USART_ISR_TxC)
#define USART_RxNE_FLAG					(0x1U << USART_SR_RxNE)

#include "RCC.h"
#include "GPIO.h"
#include "EXTI.h"
#include "SPI.h"
#include "USART.h"

#endif /* INC_STM32F070XX_H_ */
