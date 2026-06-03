#include "USART.h"

static void closeUSART_ISR(USART_HandleTypeDef_t *USART_Handle)
{
	USART_Handle->TxBufferSize = 0;
	USART_Handle->pTxBuffer = NULL;
	USART_Handle->TxStatus = USART_BUS_FREE;

	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_TxEIE);
}

static void closeUSART_ISR_Rx(USART_HandleTypeDef_t *USART_Handle)
{
	USART_Handle->RxBufferSize = 0;
	USART_Handle->pRxBuffer = NULL;
	USART_Handle->RxStatus = USART_BUS_FREE;

	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_RxNEIE);
}

static void USART_SendWith_IT(USART_HandleTypeDef_t *USART_Handle)
{
	if( (USART_Handle->Init.WordLength) == USART_WORD_LENGTH_9Bits && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		uint16_t *p16BitsData = (uint16_t*)(USART_Handle->pTxBuffer);

		USART_Handle->Instance->TDR = (uint16_t)(*p16BitsData & (uint16_t)0x01FFU);
		USART_Handle->pTxBuffer += sizeof(uint16_t);
		USART_Handle->TxBufferSize -= 2;
	}
	else
	{
		USART_Handle->Instance->TDR = (uint8_t)(*(USART_Handle->pTxBuffer) & (uint8_t)0x00FF);
		USART_Handle->pTxBuffer++;
		USART_Handle->TxBufferSize --;
	}
	if(USART_Handle->TxBufferSize == 0)
	{
		closeUSART_ISR(USART_Handle);
	}
}

static void USART_ReceiveWith_IT(USART_HandleTypeDef_t *USART_Handle)
{
	uint16_t *p16BitsBuffer;
	uint8_t *p8BitsBuffer;

	if( (USART_Handle->Init.WordLength == USART_WORD_LENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		p16BitsBuffer = (uint16_t*)USART_Handle->pRxBuffer;
		p8BitsBuffer = NULL;
	}
	else
	{
		p8BitsBuffer = (uint8_t*)USART_Handle->pRxBuffer;
		p16BitsBuffer = NULL;
	}

	if(p8BitsBuffer == NULL)
	{
		*p16BitsBuffer = (uint16_t)(USART_Handle->Instance->RDR & 0x01FFU);
		USART_Handle->pRxBuffer += sizeof(uint16_t);
		USART_Handle->RxBufferSize -=2;
	}
	else
	{
		if( (USART_Handle->Init.WordLength == USART_WORD_LENGTH_9Bits) && (USART_Handle->Init.Parity != USART_PARITY_NONE) )
		{
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->RDR & 0x00FFU);
			USART_Handle->pRxBuffer++;
			USART_Handle->RxBufferSize--;
		}
		else if( (USART_Handle->Init.WordLength == USART_WORD_LENGTH_8Bits) && (USART_Handle->Init.Parity != USART_PARITY_NONE) )
		{
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->RDR & 0x00FFU);
			USART_Handle->pRxBuffer++;
			USART_Handle->RxBufferSize--;
		}
		else
		{
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->RDR & 0x007FU);
			USART_Handle->pRxBuffer++;
			USART_Handle->RxBufferSize--;
		}
	}
	if(USART_Handle->RxBufferSize == 0)
	{
		closeUSART_ISR_Rx(USART_Handle);
	}

}

/**
  * @brief  USART_Init, Configures the USART Peripheral
  * @param  USART_Handle = User config structure
  *
  * @retval Void
  */

void USART_Init(USART_HandleTypeDef_t *USART_Handle)
{
	/*******OverSampling	 WordLength		Mode	Parity***********/
	uint32_t tempReg = 0;
	uint32_t periphClock = 0;
	uint32_t mantissaPart = 0;
	uint32_t fractionPart = 0;
	uint32_t USART_DIV_Value = 0;
	uint32_t tempValue = 0;

	tempReg = USART_Handle->Instance->CR1;

	tempReg |= (USART_Handle->Init.OverSampling) | (USART_Handle->Init.WordLength) | (USART_Handle->Init.Mode) | \
			   (USART_Handle->Init.Parity);

	USART_Handle->Instance->CR1 = tempReg;

	/******************Parity********************/

	tempReg = USART_Handle->Instance->CR2;

	tempReg &= ~(0x3U << USART_CR2_STOP);

	tempReg |= (USART_Handle->Init.StopBits);

	USART_Handle->Instance->CR2 = tempReg;

	/**************HardWareFlowControl*******************/

	tempReg = USART_Handle->Instance->CR3;

	tempReg |= (USART_Handle->Init.HardwareFlowControl);

	USART_Handle->Instance->CR3 = tempReg;

	/**********************Baud Rate Configuration************************/

	periphClock = RCC_GetPClock();

	if(USART_Handle->Init.OverSampling == USART_OVERSAMPLE_8)
	{
		USART_DIV_Value = __USART_DIV_VALUE_8(periphClock, USART_Handle->Init.BaudRate);
		mantissaPart = (USART_DIV_Value / 100U);
		fractionPart = (USART_DIV_Value) - (mantissaPart * 100U);

		fractionPart = ( ( (fractionPart * 8U) + 50U) / 100U ) & (0x07U);
	}
	else
	{
		USART_DIV_Value = __USART_DIV_VALUE_16(periphClock, USART_Handle->Init.BaudRate);
		mantissaPart = (USART_DIV_Value / 100U);
		fractionPart = (USART_DIV_Value) - (mantissaPart * 100U);

		fractionPart = ( ( (fractionPart * 16U) + 50U) / 100U ) & (0xFU);
	}
	tempValue |= (mantissaPart << 4U);
	tempValue |= (fractionPart << 0U);

	USART_Handle->Instance->BRR = tempValue;
}


/**
  * @brief  USART_ReceiveData, Receives data
  *
  * @param  USART_Handle = User config structure
  *
  *
  * @param pBuffer = Adress of data to store
  *
  * @param sizeOfData = Length of your data in bytes. Multiply by 2 in 9Bits Yes Parity
  *
  * @retval Void
  */

void USART_ReceiveData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pBuffer, uint16_t dataSize)
{
	uint16_t *p16BitsBuffer;
	uint8_t *p8BitsBuffer;

	if( (USART_Handle->Init.WordLength == USART_WORD_LENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		p16BitsBuffer = (uint16_t*)pBuffer;
		p8BitsBuffer = NULL;
	}
	else
	{
		p8BitsBuffer = (uint8_t*)pBuffer;
		p16BitsBuffer = NULL;
	}

	while(dataSize > 0)
	{
		while( !(USART_GetFlagStatus(USART_Handle, USART_RxNE_FLAG)) );

		if(p8BitsBuffer == NULL)
		{
			*p16BitsBuffer = (uint16_t)(USART_Handle->Instance->RDR & 0x01FFU);
			p16BitsBuffer++;
			dataSize -= 2;
		}
		else
		{
			if( (USART_Handle->Init.WordLength == USART_WORD_LENGTH_9Bits) && (USART_Handle->Init.Parity != USART_PARITY_NONE) )
			{
				*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->RDR & 0x00FFU);
				p8BitsBuffer++;
				dataSize --;
			}
			else if ( (USART_Handle->Init.WordLength == USART_WORD_LENGTH_8Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
			{
				*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->RDR & 0x00FFU);
				p8BitsBuffer++;
				dataSize --;
			}
			else if ( (USART_Handle->Init.WordLength == USART_WORD_LENGTH_8Bits) && (USART_Handle->Init.Parity != USART_PARITY_NONE) )
			{
				*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->RDR & 0x007FU);
				p8BitsBuffer++;
				dataSize --;
			}
		}
	}
}

void USART_ReceiveData_IT(USART_HandleTypeDef_t *USART_Handle, uint8_t *pBuffer, uint16_t dataSize)
{
	USART_BusState_t usartBusState = USART_Handle->RxStatus;

	if(usartBusState != USART_BUS_Rx)
	{
		USART_Handle->pRxBuffer = (uint8_t*)pBuffer;
		USART_Handle->RxBufferSize = (uint16_t)dataSize;
		USART_Handle->RxStatus = USART_BUS_Rx;
		USART_Handle->RxISR_Function = USART_ReceiveWith_IT;

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_RxNEIE);
	}
}

/**
  * @brief  USART_TransmitData, Transmits data
  *
  * @param  USART_Handle = User config structure
  *
  *
  * @param pData = Adress of data to send
  *
  * @param sizeOfData = Length of your data in bytes
  *
  * @retval Void
  */

void USART_TransmitData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t dataSize)
{
	// 9 Bit = frame no parity // 9 Bit = frame yes parity
	// 8 Bit = frame no parity // 8 Bit = frame yes parity

	uint16_t *data16Bits;

	if( (USART_Handle->Init.WordLength == USART_WORD_LENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE) )
	{
		data16Bits = (uint16_t *)pData;
	}
	else
	{
		data16Bits = NULL;
	}

	while(dataSize > 0)
	{
		while( !(USART_GetFlagStatus(USART_Handle, USART_TxE_FLAG)) );

		/* 9Bits Data No Parity is for ELSE Condition, for others you will be in  IF Case */

		if(data16Bits == NULL)
		{
			USART_Handle->Instance->TDR = (uint8_t)(*pData & 0xFFU);
			pData++;
			dataSize--;
		}
		else
		{
			USART_Handle->Instance->TDR = (uint16_t)(*data16Bits & (0x01FFU));
			data16Bits++;
			dataSize -= 2;
		}
	}
	while( !(USART_GetFlagStatus(USART_Handle, USART_TxC_FLAG)) );
}


void USART_TransmitData_IT(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t dataSize)
{
	USART_BusState_t usartBusState = USART_Handle->TxStatus;

	if(usartBusState != USART_BUS_Tx)
	{
		USART_Handle->pTxBuffer = (uint8_t*)pData;
		USART_Handle->TxBufferSize = (uint16_t)dataSize;
		USART_Handle->TxStatus = USART_BUS_Tx;
		USART_Handle->TxISR_Function = USART_SendWith_IT;

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_TxEIE);
	}
}



/**
  * @brief  USART_PeriphCmd, Enable or Disable USART Peripheral
  * @param  USART_Handle = User config structure
  *
  *
  * @param stateOfUSART = ENABLE or DISABLE
  *
  * @retval Void
  */

void USART_PeriphCmd(USART_HandleTypeDef_t *USART_Handle, FunctionalState_t stateOfUSART)
{
	if(stateOfUSART == ENABLE)
	{
		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_UE);
	}
	else
	{
		USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_UE);
	}
}


/**
  * @brief  USART_GetFlagStatus, Return the flag of SR register
  *
  * @param  USART_Handle = User config structure
  *
  *
  * @param USART = Flag name of SR register
  *
  *
  * @retval USART_FlagStatus_t
  */

USART_FlagStatus_t USART_GetFlagStatus(USART_HandleTypeDef_t *USART_Handle, uint16_t flagName)
{
	return( (USART_Handle->Instance->ISR & flagName) ? USART_FLAG_SET : USART_FLAG_RESET );
}

void USART_InterruptHandler(USART_HandleTypeDef_t *USART_Handle)
{
	uint8_t flagValue = 0;
	uint8_t interruptValue = 0;

	flagValue = (uint8_t)( (USART_Handle->Instance->ISR >> 7U) & 0x1U );
	interruptValue = (uint8_t)( (USART_Handle->Instance->CR1 >> 7U) & 0x1U );

	if(flagValue && interruptValue)
	{
		USART_Handle->TxISR_Function(USART_Handle);
	}

	flagValue = (uint8_t)( (USART_Handle->Instance->ISR >> 5U) & 0x1U );
	interruptValue = (uint8_t)( (USART_Handle->Instance->CR1 >> 5U) & 0x1U );

	if(flagValue & interruptValue)
	{
		USART_Handle->RxISR_Function(USART_Handle);
	}
}
