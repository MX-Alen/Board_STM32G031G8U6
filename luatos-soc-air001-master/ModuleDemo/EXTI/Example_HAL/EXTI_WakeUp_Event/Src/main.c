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
EXTI_HandleTypeDef exti_handle;

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_ConfigureEXTI(void);
void GPIO_Init(void){
  GPIO_InitTypeDef GPIO_Struct;
  
  
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
	GPIO_Struct.Pin = GPIO_PIN_3;
  GPIO_Struct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Struct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_Struct);
}
/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 复位所有外设，初始化flash接口和systick */
  HAL_Init();
  
  /* 初始化LED */
  GPIO_Init();
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

  /* 初始化按键BUTTON */
//  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  /* 配置外部中断 */
  APP_ConfigureEXTI();
  
  /* 暂停systick */
  HAL_SuspendTick();
  
  /* 点亮小灯 */
  
  
  /* 等待用户按键按下，主机程序开始运行 */
  
  /* 关闭小灯 */
  
  /* 进入STOP模式 */
//  HAL_PWR_EnterSTOPMode(1, PWR_SLEEPENTRY_WFE);
  
  /* 恢复systick */
  HAL_ResumeTick();
  
  while (1)
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_Delay(100);
  }
}

/**
  * @brief  配置事件引脚引脚
  * @param  无
  * @retval 无
  */
static void APP_ConfigureEXTI(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();                  /* 使能GPIOA时钟 */
  GPIO_InitStruct.Mode  = GPIO_MODE_EVT_FALLING; /* GPIO模式为下降沿中断 */
  GPIO_InitStruct.Pull  = GPIO_PULLUP;           /* 上拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  /* 速度为高速 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
{
  /* 无限循环 */
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
