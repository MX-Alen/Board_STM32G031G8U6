/**
  ******************************************************************************
  * @file    air001xx_it.c
  * @author  MCU Application Team
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) AirM2M.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "air001xx_it.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers         */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/* AIR001xx Peripheral Interrupt Handlers                                     */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file.                                          */
/******************************************************************************/
/**
  * @brief This function handles SPI1 interrupt.
  */
void SPI1_IRQHandler(void)
{
  /* 检查 ISR 寄存器中的 RXNE 标志值 */
  if(LL_SPI_IsActiveFlag_RXNE(SPI1))
  {
    /* 调用接收回调函数 */
    APP_SpiRxCallback();
  }
  /* 检查TXE标志 */
  else if(LL_SPI_IsActiveFlag_TXE(SPI1))
  {
    /* 调用发送回调 */
    APP_SpiTxCallback();
  }
  /* 检查 STOP 标志 */
  else if(LL_SPI_IsActiveFlag_OVR(SPI1))
  {
    /* 调用错误回调 */
    APP_SpiTransferErrorCallback();
  }
}

/************************ (C) COPYRIGHT AirM2M *****END OF FILE******************/
