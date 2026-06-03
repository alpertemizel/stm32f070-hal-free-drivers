#include "stm32f070xx.h"

static void GPIO_LedConfig();
static void GPIO_ButtonInterruptConfig();
static void SPI_Config();
static void SPI_GPIO_Config();

SPI_HandleTypeDef_t SPI_Handle;

void EXTI4_15_IRQHandler()
{
	char msgToSend[] = "Hello World!\n";

	if (EXTI->PR & (0x1U << 13))
	{
		EXTI->PR = (0x1U << 13U);

		SPI_TransmitData_IT(&SPI_Handle, (uint8_t*)msgToSend, strlen(msgToSend));
		SPI_ReceiveData_IT(&SPI_Handle, (uint8_t*)msgToSend, strlen(msgToSend));
	}
}

void SPI2_IRQHandler()
{
	SPI_InterruptHandler(&SPI_Handle);
}

int main(void) {

	GPIO_LedConfig();

	GPIO_ButtonInterruptConfig();

	SPI_GPIO_Config();

	SPI_Config();



	for (;;) {

	}
}

static void GPIO_LedConfig() {
	GPIO_Init_TypeDef_t GPIO_InitStruct = { 0 };

	RCC_GPIOA_CLK_ENABLE(); 	// Clock is active
	RCC_GPIOC_CLK_ENABLE(); 	// Clock is active

	GPIO_InitStruct.pinNumber = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOA, &GPIO_InitStruct); // Configuration

	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));

	GPIO_InitStruct.pinNumber = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.PuPd = GPIO_PUPD_PULLUP;

	GPIO_Init(GPIOC, &GPIO_InitStruct); // Configuration
}

static void GPIO_ButtonInterruptConfig() {
	EXTI_InitTypeDef_t EXTI_InitStruct = { 0 };

	RCC_SYSCFG_CLK_ENABLE();

	EXTI_LineConfig(EXTI_PortSource_GPIOC, EXTI_LineSource_13);

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_LineNumber = EXTI_LineSource_13;
	EXTI_InitStruct.EXTI_Mode = EXTI_MODE_Interrupt;
	EXTI_InitStruct.TriggerSelection = EXTI_TRIGGER_Rising;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_EnableInterrupt(EXTI13_IRQNumber);
}

void SPI_Config()
{
	RCC_SPI2_CLK_ENABLE();

	SPI_Handle.Instance = SPI2;
	SPI_Handle.Init.BaudRate = SPI_BAUDRATE_DIV4;
	SPI_Handle.Init.BusConfig = SPI_BUS_FullDuplex;
	SPI_Handle.Init.CPHA = SPI_CPHA_FIRST;
	SPI_Handle.Init.CPOL = SPI_CPOL_LOW;
	SPI_Handle.Init.DataSize = SPI_DS_8BIT;
	SPI_Handle.Init.FrameFormat = SPI_FRAMEFORMAT_MSB;
	SPI_Handle.Init.Mode = SPI_MODE_MASTER;
	SPI_Handle.Init.SSM_Cmd = SPI_SSM_ENABLE;

	SPI_Init(&SPI_Handle);

	NVIC_EnableInterrupt(SPI2_IRQNumber);

	SPI_PeriphCmd(&SPI_Handle, ENABLE);
}

void SPI_GPIO_Config()
{
	GPIO_Init_TypeDef_t GPIO_InitStruct = {0};

	RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.pinNumber = GPIO_PIN_13 | GPIO_PIN_15; //PB13 = SCK PB15 = MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_VERY;
	GPIO_InitStruct.Alternate = GPIO_AF0;

	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
