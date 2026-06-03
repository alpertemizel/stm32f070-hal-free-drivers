#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "stm32f070xx.h"

/*
 * RCC AHB Peripherals Clock Control Macro Definition
 *
 */

#define RCC_GPIOA_CLK_ENABLE()     do{  uint32_t tempValue = 0; \
										SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN); \
										tempValue = READ_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_GPIOB_CLK_ENABLE()     do{  uint32_t tempValue = 0; \
										SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOBEN); \
										tempValue = READ_BIT(RCC->AHBENR, RCC_AHBENR_GPIOBEN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_GPIOC_CLK_ENABLE()     do{  uint32_t tempValue = 0; \
										SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN); \
										tempValue = READ_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_GPIOD_CLK_ENABLE()     do{  uint32_t tempValue = 0; \
										SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIODEN); \
										tempValue = READ_BIT(RCC->AHBENR, RCC_AHBENR_GPIODEN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_GPIOA_CLK_DISABLE()		CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN)
#define RCC_GPIOB_CLK_DISABLE()		CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_GPIOBEN)
#define RCC_GPIOC_CLK_DISABLE()		CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN)
#define RCC_GPIOD_CLK_DISABLE()		CLEAR_BIT(RCC->AHBENR, RCC_AHBENR_GPIODEN)


/*
 * RCC APB Peripherals Clock Control Macro Definition
 *
 */

#define RCC_SYSCFG_CLK_ENABLE()		do{ uint32_t tempValue = 0; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGCOMPEN); \
										tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGCOMPEN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_SPI1_CLK_ENABLE()		do{ uint32_t tempValue = 0;\
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); \
										tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_SPI2_CLK_ENABLE()		do{ uint32_t tempValue = 0;\
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN); \
										tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_SPI1_CLK_DISABLE()		CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN)
#define RCC_SPI2_CLK_DISABLE()		CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN)

#define RCC_USART1_CLK_ENABLE()		do{ uint32_t tempValue = 0;\
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN); \
										tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_USART2_CLK_ENABLE()		do{ uint32_t tempValue = 0;\
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN); \
										tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_USART3_CLK_ENABLE()		do{ uint32_t tempValue = 0;\
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN); \
										tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_USART4_CLK_ENABLE()		do{ uint32_t tempValue = 0;\
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART4EN); \
										tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART4EN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_USART5_CLK_ENABLE()		do{ uint32_t tempValue = 0;\
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART5EN); \
										tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART5EN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_USART6_CLK_ENABLE()		do{ uint32_t tempValue = 0;\
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART6EN); \
										tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART6EN); \
										UNUSED(tempValue); \
										}while(0)

#define RCC_USART1_CLK_DISABLE()		CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN)
#define RCC_USART2_CLK_DISABLE()		CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN)
#define RCC_USART3_CLK_DISABLE()		CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN)
#define RCC_USART4_CLK_DISABLE()		CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_USART4EN)
#define RCC_USART5_CLK_DISABLE()		CLEAR_BIT(RCC->APB1ENR, RCC_APB1ENR_USART5EN)
#define RCC_USART6_CLK_DISABLE()		CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART6EN)

uint32_t RCC_GetSystemClock(void);
uint32_t RCC_GetHClock(void);
uint32_t RCC_GetPClock(void);

#endif /* INC_RCC_H_ */

