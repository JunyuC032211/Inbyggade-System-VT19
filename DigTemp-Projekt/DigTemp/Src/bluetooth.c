/**
 ******************************************************************************
 @brief	bluetooth.c file, complements main.c and
 @file	bluetooth.c
 @author Johan Hanssen
 @version 1.0
 @date	28-February-2018
 @brief	The code for initializing the bluetooth module
 ******************************************************************************
 */

#include "bluetooth.h"
#include "gpio.h"
#include "usart.h"
#include "main.h"
#include "setuartrtc.h"


void initBluetooth(){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
}
