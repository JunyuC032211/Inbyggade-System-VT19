/**
******************************************************************************
@brief	SetUartRtc declares the functions used by setuartrtc.c
@file	setuartrtc.h
@author Johan Hanssen
@version 1.0
@date	26-February-2018
******************************************************************************
*/
#include "main.h"
#include "gpio.h"

void setUartRtc(void);

void sendBluetooth(double temp, uint16_t Humidity);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);
