/**
  ******************************************************************************
  * @file    dev_clk.c
  * @author  周大侠
  * @version V1.0
  * @date    2021-5-14 17:51:14
  ******************************************************************************
  * @attention
    Default encoding UTF-8

  ******************************************************************************
  */

#include "dev_clk.h"



//时钟相关配置   ，48M时钟配置
void Dev_ClkCfg(void)
{
    stc_sysctrl_clk_cfg_t stcCfg;
    stc_sysctrl_pll_cfg_t stcPLLCfg;    
    
    ///< 开启FLASH外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralFlash, TRUE);
    
    ///< 因将要倍频的PLL作为系统时钟HCLK会达到48MHz：所以此处预先设置FLASH 读等待周期为1 cycle(默认值为0 cycle)
    Flash_WaitCycle(FlashWaitCycle1);
    
    ///< 时钟初始化前，优先设置要使用的时钟源：此处配置PLL
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);             //PLL使用RCH作为时钟源，因此需要先设置RCH    
    
    stcPLLCfg.enInFreq    = SysctrlPllInFreq4_6MHz;     //RCH 4MHz
    stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;  //PLL 输出48MHz
    stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //输入时钟源选择RCH
    stcPLLCfg.enPllMul    = SysctrlPllMul12;            //4MHz x 12 = 48MHz
    Sysctrl_SetPLLFreq(&stcPLLCfg);       
    
    ///< 选择PLL作为HCLK时钟源;
    stcCfg.enClkSrc  = SysctrlClkPLL;
    ///< HCLK SYSCLK
    stcCfg.enHClkDiv = SysctrlHclkDiv1;
    ///< PCLK 为HCLK
    stcCfg.enPClkDiv = SysctrlPclkDiv1;
    ///< 系统时钟初始化
    Sysctrl_ClkInit(&stcCfg);     
}




//端口相关配置  ，时钟频率IO口输出
void App_PortCfg(void)
{
    stc_gpio_cfg_t        stcGpioCfg;
    
    ///< 开启GPIO外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    
    ///< 配置PLL从GPIO输出
    ///< 端口方向配置->输出
    stcGpioCfg.enDir = GpioDirOut;
    ///< 端口驱动能力配置->高驱动能力
    stcGpioCfg.enDrv = GpioDrvH;
    ///< 端口上下拉配置->无上下拉
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;
    ///< 端口开漏输出配置->开漏输出关闭
    stcGpioCfg.enOD = GpioOdDisable;
    ///< GPIO IO PB00初始化
    Gpio_Init(GpioPortB, GpioPin0, &stcGpioCfg);
    ///< GPIO IO PA01初始化
    Gpio_Init(GpioPortA, GpioPin1, &stcGpioCfg);
    
    ///< 设置PLL从PB00输出
    Gpio_SetAfMode(GpioPortB, GpioPin0, GpioAf7);
    
    ///< 设置HCLK从PA01输出
    Gpio_SfHClkOutputCfg(GpioSfHclkOutEnable, GpioSfHclkOutDiv1);
    Gpio_SetAfMode(GpioPortA, GpioPin1, GpioAf6);

}




