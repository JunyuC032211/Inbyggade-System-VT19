/**
******************************************************************************
@brief	Declares the functions used in display.c
@file	display.h
@author Johan Hanssen
@version 1.0
@date	19-February-2018
******************************************************************************
*/
#include "main.h"
#include "gpio.h"

void initDisplay();
void sendDisplay(uint8_t rs,uint8_t rw,uint8_t db);
void showDisplay(uint16_t value, uint8_t row);
