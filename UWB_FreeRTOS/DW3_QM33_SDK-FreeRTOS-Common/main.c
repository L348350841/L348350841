/**
 * @file      main.c
 *
 * @brief     DW3_QM33_SDK FREERTOS main
 *
 * @author    Decawave Applications
 *
 * @attention Copyright (c) 2021 - 2022, Qorvo US, Inc.

 * 
 *
 */

#include <stdint.h>
#include <cmsis_os.h>
#include "app.h"
#include "thisBoard.h"
#include "appConfig.h"
#include "EventManager.h"
#include "controlTask.h"
#include "uartTask.h"
#include "HAL_error.h"
#include "flushTask.h"
#include "defaultTask.h"




/*
主控初始程序：

主要是用于初始化开发板及其 UWB 模块，配置硬件资源（spi，gpio等），
启动 FreeRTOS 任务调度，解析由pc发送的UCI指令，并执行与超宽带通信、数据处理及其他嵌入式应用相关的任务。
*/

int main(void)
{



    BoardInit();//初始化硬件资源,GPIO、时钟、UART 等外设
    AppConfigInit();
    EventManagerInit();
    board_interface_init();
    if (uwb_init())//初始化超宽带（UWB）模块的配置。配置SPI与 UWB通信。也有设置通信参数、载波频率、数据速率等
    {
        error_handler(1, _ERR_DEVID);
    }
    DefaultTaskInit();
    FlushTaskInit();
    ControlTaskInit();
    UartTaskInit();
    /* Start scheduler */
    osKernelStart();//执行完之后，各个任务开始运行，程序控制权交给调度器，所以不往下运行了
    while (1)
    {

    }

    return 0;
}
