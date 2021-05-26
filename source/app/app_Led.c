/**
  ******************************************************************************
  * @file    app_Led.c
  * @author  周大侠
  * @version V1.0
  * @date    2021-5-26 10:57:03
  ******************************************************************************
  * @attention
    Default encoding UTF-8

  ******************************************************************************
  */

#include "app_Led.h"
#include "g_include.h"



/********************************************************
  * @Description：任务演示-心跳灯 1S闪烁一次
  * @Arguments	：
                无
  * @Returns	：
  * @author     : 周大侠     
 *******************************************************/
void Led_Task(void* param)
{
	while(1)
	{
		///< LED点亮
		Gpio_SetIO(EVB_LEDR_PORT, EVB_LEDR_PIN);
		vTaskDelay(500);

		///< LED关闭
		Gpio_ClrIO(EVB_LEDR_PORT, EVB_LEDR_PIN);
		vTaskDelay(500);
	}
}



