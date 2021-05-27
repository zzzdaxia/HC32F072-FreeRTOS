/**
  ******************************************************************************
  * @file    main.c
  * @author  周大侠
  * @version V1.0
  * @date    2021-5-14 17:33:30
  ******************************************************************************
  * @attention
    Default encoding UTF-8
	
  ******************************************************************************
  */

	
/******************************************************************************
 * Include files
 ******************************************************************************/
#include "main.h"



/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static void App_LedInit(void);

/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ** This sample
 **
 ******************************************************************************/
int32_t main(void)
{
    ///< LED端口初始化
    App_LedInit();

    while(1)
    {
        ///< LED点亮
        Gpio_SetIO(EVB_LEDR_PORT, EVB_LEDR_PIN);
        delay1ms(1000);

        ///< LED关闭
        Gpio_ClrIO(EVB_LEDR_PORT, EVB_LEDR_PIN);
        delay1ms(1000);
    }
}



static void App_LedInit(void)
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

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


