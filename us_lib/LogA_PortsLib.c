/**
  ******************************************************************************
  * @file		LogA_PortsLib.c
  * @author		Urban Seger
  * @version	v0.1
  * @date		2013-07
  * @brief		This file provides set of firmware functions to manage ports
  * 			(registers and pins) on the STM32F4-Discovery Kit.
  ******************************************************************************
  * @attention
  *
  * Adopted from stm32f4_discovery.c
  * V1.1.1
  * by MCD Application Team
  * &copy; COPYRIGHT 2012 STMicroelectronics
  *
  ******************************************************************************
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "LogA_PortsLib.h"

/**
  * @brief  Configures DigOUT channels on GPIOC.
  */
void LogA_DigOUT_Init(void)
{
  meGPIO_Init(DIGOUT_CHAN0, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGOUT_CHAN1, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGOUT_CHAN2, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGOUT_CHAN3, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGOUT_CHAN4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGOUT_CHAN5, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGOUT_CHAN6, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGOUT_CHAN7, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
}

/**
  * @brief  Configures DigIN channels on GPIOB.
  */
void LogA_DigIN_Init(void)
{
  meGPIO_Init(DIGIN_CHAN0, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGIN_CHAN1, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGIN_CHAN2, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGIN_CHAN3, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGIN_CHAN4, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGIN_CHAN5, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGIN_CHAN6, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
  meGPIO_Init(DIGIN_CHAN7, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz, 0);
}



/**
  * @brief  Essential function that allows pick 8 individual bits out of a 16-bit port register
  * @param  ExpandVal: is the wide value that needs to be compacted
  * @param  Bitmask: 1s designate the positions where the information is stored
  * @retval Unsigned 16bit integer with one byte sitting at the LSB end
  */ 
uint16_t LogA_PortBits_Compactor(uint16_t ExpandVal, uint16_t Bitmask)
{
	uint16_t CompactVal = 0;
	uint8_t pos = 0;

	for (uint8_t i=0; i<16; i++)
	{
		if (Bitmask & 0x01<<i)
		{
			if (ExpandVal & 0x01<<i)
			{
				CompactVal |= 0x01<<pos;
			}
		pos++;
		}
	}
	return CompactVal;
}

/**
  * @brief  Essential function places one byte's bits into a 16bit wide register
  * @param  CompactVal: is the narrow value that wants to be expanded
  * @param  Bitmask: 1s designate the positions where the information has to be placed
  * @retval Unsigned 16bit integer with one byte distributed over the whole width
  */ 
uint16_t LogA_PortBits_Expander(uint16_t CompactVal, uint16_t Bitmask)
{
	uint16_t ExpandVal = 0;
	uint8_t pos = 0;

	for (uint8_t i=0; i<16; i++)
	{
		if (Bitmask & 0x01<<i)
		{
			if (CompactVal & 0x01<<pos)
			{
				ExpandVal |= 0x01<<i;
			}
		pos++;
		}
	}
	return ExpandVal;
}


    
/*****END OF FILE****/

/* PREVIOUS VERSION OF CompatOr
uint16_t LogA_PortBits_Compacter(uint16_t ExpandVal, uint16_t Bitmask)
{
	uint16_t CompactVal = 0;
	uint8_t i;
	uint8_t zeroes = 0;

	for (i=0; i<16; i++)
	{
		if (Bitmask & 0x0001)
		{
			CompactVal >>= 1;
			if (ExpandVal & 0x0001)
			{
				CompactVal |= 0x8000;
			}
		}
		else
		{
			zeroes++;
		}
		ExpandVal >>= 1;
		Bitmask >>= 1;
	}
	CompactVal >>= zeroes;
	return(CompactVal);
}
*/
