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
**五、优化**  


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



