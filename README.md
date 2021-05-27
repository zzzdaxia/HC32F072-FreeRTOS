# HC32F072 + FreeRTOS V10.4.3详细教程 #

## 记录并分享移植过程   ##

*背景原因：STM32太贵了，而且移植RTOS 0难度，资料太多了，做一个小众单片机的移植，后续其它单片机移植也可参考类似过程。*


**环境说明：**  
开发IDE：MDK-ARM Plus ver 5.34  
MCU：[国产华大单片机 HC32F072](https://www.hdsc.com.cn/Category83-1448 "官方资料") ，主频 48Mhz ，Core M0+内核 ，RAM 16KB ，ROM 128KB  
RTOS：FreeRTOS V10.4.3

***移植分为以下几个步骤***

**一、准备**  
**二、FreeRTOS源码**    
**三、添加工程**  
**四、裁剪**  
**五、优化**  


## 一、准备 ##

1.首先准备一个HC32F072的最小系统，可以参考官方点灯Demo。为了发挥最大性能，将主频修改至最大48Mhz。此处不做详细教程，也可参考已修改好的branch-[noOS](https://github.com/zhou-daxia/HC32F072-FreeRTOS/tree/noOS "github")  
2.下载FreeRTOS源代码，官网：[https://www.freertos.org/a00104.html](https://www.freertos.org/a00104.html)  
选择稳定版本下载：FreeRTOS LTS Release 202012.01 并解压

## 一、FreeRTOS源码 ##
