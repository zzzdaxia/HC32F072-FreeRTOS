/**
  ******************************************************************************
  * @file    app_Task.c
  * @author  周大侠
  * @version V1.0
  * @date    2021-5-26 10:57:03
  ******************************************************************************
  * @attention
    Default encoding UTF-8

  ******************************************************************************
  */

#include "app_Task.h"



static TaskHandle_t AppLedTask_handle = NULL;


/********************************************************
  * @Description：任务创建
  * @Arguments	：
                无
  * @Returns	：
                成功 0
                失败 -1
  * @author     : 周大侠     
 *******************************************************/
int FreeRTOS_TaskCreate(void)
{
	BaseType_t xReturn = pdPASS;
	
	//创建心跳灯任务
	xReturn = xTaskCreate((TaskFunction_t )Led_Task,  //任务入口函数
                        (const char*    )"LedTask",//任务名字
                        (uint16_t       )64,  //任务栈大小
                        (void*          )NULL,//任务入口函数参数
                        (UBaseType_t    )3, //任务的优先级
                        (TaskHandle_t*  )&AppLedTask_handle);//任务控制块指针

   if(pdPASS != xReturn)
   {
		return -1;
   }

   vTaskStartScheduler();//启动调度
   
   return 0;
}


