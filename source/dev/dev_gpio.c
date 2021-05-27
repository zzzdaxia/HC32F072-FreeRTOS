/**
  ******************************************************************************
  * @file    dev_gpio.c
  * @author  周大侠
  * @version V1.0
  * @date    2021-5-14 17:51:14
  ******************************************************************************
  * @attention
    Default encoding UTF-8

  ******************************************************************************
  */

#include "dev_gpio.h"



void Dev_LedInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    ///< 打开GPIO外设时钟门控
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
    
    ///< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
    stcGpioCfg.enDir = GpioDirOut;
    ///< 端口上下拉配置->下拉
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdEnable;
    
    ///< LED关闭
    Gpio_ClrIO(EVB_LEDR_PORT, EVB_LEDR_PIN);
    
    ///< GPIO IO LED端口初始化
    Gpio_Init(EVB_LEDR_PORT, EVB_LEDR_PIN, &stcGpioCfg);
    

}



