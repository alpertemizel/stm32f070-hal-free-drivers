#ifndef SRC_RCC_C_
#define SRC_RCC_C_

#include "RCC.h"

static const uint8_t AHB_Prescaler[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

static const uint8_t APB_Prescaler[] = {0, 0, 0, 0, 1, 2, 3, 4};


uint32_t RCC_GetSystemClock(void)
{
	uint32_t SystemCoreClock = 0;
	uint32_t clckSource = 0;

	clckSource = ( (RCC->CFGR >> 2U) & 0x3U );

	switch(clckSource)
	{
		case 0 : SystemCoreClock = 8000000U; break;
		case 1 : SystemCoreClock = 8000000U; break;

		default : SystemCoreClock = 8000000U;
	}

	return SystemCoreClock;
}

uint32_t RCC_GetHClock(void)
{
    uint32_t SystemCoreClock = RCC_GetSystemClock();

    // AHB Prescaler (bits 4:7)
    uint8_t hpre = ( (RCC->CFGR >> 4U) & 0xFU );

    return (SystemCoreClock >> AHB_Prescaler[hpre]);
}

uint32_t RCC_GetPClock(void)
{
    uint32_t hclk = RCC_GetHClock();

    // APB Prescaler  (bits 8:10)
    uint8_t ppre = ( (RCC->CFGR >> 8U) & 0x7U );

    // PCLK = HCLK / APB_Prescaler
    return (hclk >> APB_Prescaler[ppre]);
}

#endif /* SRC_RCC_C_ */
