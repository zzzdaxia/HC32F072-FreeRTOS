# HC32F072 + FreeRTOS 详细教程 #

## 记录并分享移植过程   ##

*背景原因：STM32太贵了，而且CubeMx太强了，移植难度0。  
做一个小众单片机的移植，后续其它单片机移植也可参考类似过程。*


**环境说明：**  
开发IDE：MDK-ARM Plus ver 5.34  
MCU：[国产华大单片机 HC32F072](https://www.hdsc.com.cn/Category83-1448 "官方资料") ，主频 48Mhz ，Core M0+内核 ，RAM 16KB ，ROM 128KB  
RTOS：FreeRTOS V10.4.3

***移植分为以下几个步骤***

**一、准备**  
**二、FreeRTOS源码**    
**三、添加工程**  
**四、裁剪**  
**五、使用**  


## 一、准备 ##

1. 首先准备一个HC32F072的最小系统，可以参考官方点灯Demo。为了发挥最大性能，将主频修改至最大48Mhz。此处不做详细教程，也可参考已修改好的branch-[noOS](https://github.com/zhou-daxia/HC32F072-FreeRTOS/tree/noOS "github")  
2. 下载FreeRTOS源代码，官网：[https://www.freertos.org/a00104.html](https://www.freertos.org/a00104.html)  
3. 选择稳定版本下载：FreeRTOS LTS Release 202012.01 并解压

## 二、FreeRTOS源码 ##
1. 先在最小系统的source目录下新建一个FreeRTOS目录用来存放RTOS源码!  ![avatar](/Doc/1.png)
 
2. 拷贝FreeRTOS源码解压后的路径下\FreeRTOS-LTS\FreeRTOS\FreeRTOS-Kernel 的所有内容到本地的source/FreeRTOS目录下。  ![avatar](/Doc/2.png)

3. 在source/FreeRTOS目录下再新建一个一个source目录，将source/FreeRTOS目录下的所有.c文件剪切到source/FreeRTOS/source目录下。![avatar](/Doc/3.png)  ![avatar](/Doc/4.png)

*现在FreeRTOS源码被我们分成了三个目录，分别是①include目录；②portable目录；③source目录  
这里 **分析一下** FreeRTOS源码结构，①和③包含的是FreeRTOS核心功能源文件及头文件 .c和.h，这两部分的文件试用于各种编译器和处理器，是通用的，**基本不需要修改**，②为**需要移植修改**的目录，这与编译器和所使用的CPU有关，属于RTOS硬件接口层。*  

*再分析一下②portable目录* ![avatar](/Doc/5.jpg)  

*keil就是我们就是我们使用的编译器，其实keil里面的内容跟RVDS里面的内容一样，所以我们只需要分析RVDS文件夹里面的内容即可。*  
*RVDS里面包含了各种处理器相关的文件夹，与CPU内核相关。FreeRTOS是一个软件，单片机是一个硬件，FreeRTOS要想运行在一个单片机上面，它们就必须关联在一起。*   
*MemMang文件夹下存放的是跟内存管理相关的源文件,一般情况我们都选用heap4方式。*

  
## 三、添加工程 ##

1. 打开keil 
2. Manage -> project Items -> Groups 添加三个工程目录，分别为FreeRTOS/src ；FreeRTOS/port ；FreeRTOS/config   点击OK。![avatar](/Doc/6.png) 
3. 在 Project栏中 选中FreeRTOS/src，右击->Add Existing File to Group ... .添加source\FreeRTO\source目录下的所有.c文件  
4. 在 Project栏中 选中FreeRTOS/port，右击->Add Existing File to Group ... .添加source\FreeRTOS\portable\RVDS\**ARM_CM0** 目录下的所有.c文件。这里因为MCU是core M0内核，其它MCU选中对应内核目录  
5. 在 Project栏中 选中FreeRTOS/port，右击->Add Existing File to Group ... .添加source\FreeRTOS\portable\MemMang 目录下的heap_4.c文件  ![avatar](/Doc/7.png) 
6. 添加头文件路径 在options -> c/c++ -> include paths -> ...  
.\source\FreeRTOS\include  
.\source\FreeRTOS\portable\MemMang  
.\source\FreeRTOS\portable\RVDS\ARM_CM0
![avatar](/Doc/8.png)  


## 四、裁剪 ##

FreeRTOS的裁剪主要依靠FreeRTOSConfig.h中的宏定义去完成，需要什么功能就打开对应的宏就可以了。  
现在我们需要一个FreeRTOSConfig.h文件。但在源码FreeRTOS-Kernel目录下没有提供config文件。  
有两个途径获得
1. 再去FreeRTOS官网下载常规版本的源码，在demo目录下找到对应内核目录下的demo(可能是其它MCU，不要紧)拷贝一个FreeRTOSConfig.h文件到本地source\FreeRTOS\include目录内
2. 我提供里一个带注释版本的FreeRTOSConfig.h文件，复制到本地source\FreeRTOS\include目录  
内容如下：  
```c  

    #ifndef FREERTOS_CONFIG_H
    #define FREERTOS_CONFIG_H
       
    #define configUSE_PREEMPTION			1//抢占式调度器开关
    #define configUSE_IDLE_HOOK				0//空闲任务钩子函数
    #define configUSE_TICK_HOOK				0//时间片钩子函数
    #define configCPU_CLOCK_HZ				( SystemCoreClock )//CPU主频
    #define configTICK_RATE_HZ				( ( TickType_t ) 1000 )//RTOS节拍频率 即1秒的中断次数
    #define configMAX_PRIORITIES			( 5 )//可使用的最大优先级
    #define configMINIMAL_STACK_SIZE		( ( unsigned short ) 60 )//定义空闲任务使用的堆栈大小
    #define configTOTAL_HEAP_SIZE			( ( size_t ) ( 8*1024 ) )//RTOS内核总计可用的有效的RAM大小
    #define configMAX_TASK_NAME_LEN			( 12 )//任务名最大长度
    #define configUSE_TRACE_FACILITY		0//是否启动可视化跟踪调试
    #define configUSE_16_BIT_TICKS			0//系统节拍计数器的变量类型  0为32位 1为16为
    #define configIDLE_SHOULD_YIELD			1//空闲任务放弃CPU使用权给其他同优先级的用户任务
    #define configUSE_MUTEXES				1//是否使用互斥信号量
    #define configQUEUE_REGISTRY_SIZE		8//设置可以注册的信号量和消息队列个数
    #define configCHECK_FOR_STACK_OVERFLOW	0//堆栈溢出检查 大于0有效
    #define configUSE_RECURSIVE_MUTEXES		1//是否使用递归互斥信号量
    #define configUSE_MALLOC_FAILED_HOOK	0//内存申请失败钩子函数
    #define configUSE_APPLICATION_TASK_TAG	0//为任务分配标签
    #define configUSE_COUNTING_SEMAPHORES	1//是否使用计数信号量
    #define configGENERATE_RUN_TIME_STATS	0//是否启用运行时间统计功能
    
    /* Co-routine definitions. */
    #define configUSE_CO_ROUTINES 			0//启用协程，启用协程以后必须添加文件croutine.c
    #define configMAX_CO_ROUTINE_PRIORITIES ( 2 )//协程的有效优先级数目
    
    /* Software timer definitions. */
    #define configUSE_TIMERS				0//是否启用软件定时器
    #define configTIMER_TASK_PRIORITY		( 2 )//软件定时器优先级
    #define configTIMER_QUEUE_LENGTH		5//软件定时器队列长度
    #define configTIMER_TASK_STACK_DEPTH	( 80 )//软件定时器任务堆栈大小
    
    /* Set the following definitions to 1 to include the API function, or zero
    to exclude the API function. *///是否启用RTOS API函数
    #define INCLUDE_vTaskPrioritySet		1
    #define INCLUDE_uxTaskPriorityGet		1
    #define INCLUDE_vTaskDelete				1
    #define INCLUDE_vTaskCleanUpResources	1
    #define INCLUDE_vTaskSuspend			1
    #define INCLUDE_vTaskDelayUntil			1
    #define INCLUDE_vTaskDelay				1
    
    /* Normal assert() semantics without relying on the provision of an assert.h
    header file. */
    #define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }
    
    /* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
    standard names - or at least those used in the unmodified vector table. */
    #define vPortSVCHandler SVC_Handler
    #define xPortPendSVHandler PendSV_Handler
    #define xPortSysTickHandler SysTick_Handler
    
    #endif /* FREERTOS_CONFIG_H */
```

3. 为了方便修改 在 Project栏中 选中FreeRTOS/config，右击->Add Existing File to Group ... .添加source\FreeRTO\include目录下的FreeRTOSConfig.h 
4. 为了将应用层代码和系统层关联在一起，需要引用一下对方的头文件  
在main.c中添加引用FreeRTOS头文件   #include "FreeRTOS.h" 和 #include "task.h"    
在FreeRTOSConfig.h中添加头文件华大的头文件 #include "hc32f072.h"  
5. RTOS心跳时钟本质是通过定时器中断是实现的，所以我们需要设置一个符合RTOS节拍的定时器中断用作RTOS的“心跳” ，并将中断处理函数交给RTOS管理。  
**定时器中断**  其实在FreeRTOS中，这一部分已经完成了，在port.c文件中已经实现vPortSetupTimerInterrupt()函数 ，采用了滴答定时器SysTick  ，中断时间是根据FreeRTOSConfig.h里configCPU_CLOCK_HZ和configTICK_RATE_HZ宏来设置的，目前是1mS，当我们启动任务调度函数vTaskStartScheduler()时就会调用，所以我们**不需要修改**什么  
**中断服务函数**  这一部分FreeRTOS源码中也已经帮我们实现好了，在port.c文件中已经实现xPortSysTickHandler()函数，所以我们要**注释原来的SysTick中断服务函数**，在\source\common目录在的interrupts_hc32f072.c文件中  ![avatar](/Doc/9.png)    

6. 尝试编译一下， 如果没有报错及警告说明**移植工作已经完成**   
如果出现类以下错误![avatar](/Doc/10.png)   
是由于你的ARM编译器太高了，处理汇编和C代码的混合时导致无法识别__ASM关键字导致语法错误。  
有两种解决办法  
① 修改编译器版本为V5，在options -> Target -> ARM compiler 中选择Use default compiler version 5 
![avatar](/Doc/11.jpg)    


② 修改类似的代码如下   

![avatar](/Doc/12.png)    
 
这里建议还是选择方法①  
## 五、使用 ##

1. 写一个闪烁点灯任务，注意是一个死循环，并通过RTOS 延时API vTaskDelay()函数延时 ![avatar](/Doc/13.png) 
2. 创建一个任务句柄变量 ![avatar](/Doc/14.png)
3. 在main函数中，创建一个点灯任务，并启动任务调度![avatar](/Doc/15.jpg)
4. 编译 
5. **完成！！！**
![avatar](/Doc/16.png)
