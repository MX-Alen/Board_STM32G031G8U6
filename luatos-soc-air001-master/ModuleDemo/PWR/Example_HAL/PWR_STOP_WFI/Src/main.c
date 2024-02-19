/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
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

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EXTI_HandleTypeDef exti_handle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_ExtiConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init(); 
  DBGMCU->CR |= 0x02;
  
  

  /* 配置外部中断 */
  APP_ExtiConfig();    

  /* systick中断关闭 */
  HAL_SuspendTick();    

  /* 进入STOP模式 */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);  

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

  while (1)
  {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_Delay(200);
  }
}

/**
  * @brief  中断配置函数
  * @param  无
  * @retval 无
  */
static void APP_ExtiConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();                                        /* 使能GPIOA时钟 */
  GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;                        /* GPIO模式为下降沿中断 */
  GPIO_InitStruct.Pull  = GPIO_PULLUP;                                 /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;                        /* 速度为高速 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  /* 初始化GPIO */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);                                   /* 使能EXTI中断 */
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);                           /* 配置中断优先级 */
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
{
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT AirM2M *****END OF FILE******************/
