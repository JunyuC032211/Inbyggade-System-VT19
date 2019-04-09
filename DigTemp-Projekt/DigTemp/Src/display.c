/**
******************************************************************************
@brief	Display handles the initialization of the display and communication.
@file	display.c
@author Johan Hanssen
@version 1.2
@date	26-February-2018
@brief	Two functions where one handles the initialization of the display
		and the second is used for general communication with the display.
******************************************************************************
*/

#include "display.h"
#include "gpio.h"
#include "spi.h"

uint8_t data[3]={0b00000000,0b00000000,0b00000000};


/*
 * @brief	initDisplay holds the data to initialize the display.
 *
 * @param	void
 * @return	void
 */
void initDisplay(void){
	sendDisplay(0,0,0x3A); /* Function Set -> 8-bit data RE=1 */
	sendDisplay(0,0,0x09); /* 4 line display */
	sendDisplay(0,0,0x06); /* bottom view */
	sendDisplay(0,0,0x1E); /* BS1 = 1 */
	sendDisplay(0,0,0x39); /* Function Set -> 8-bit data RE=0 */
	sendDisplay(0,0,0x1B); /* Internal OSC */
	sendDisplay(0,0,0x6E); /* Follower control */
	sendDisplay(0,0,0x56); /* Power control */
	sendDisplay(0,0,0x7A); /* Contrast Set */
	sendDisplay(0,0,0x38); /* Function Set -> 8-bit data IS=0 */
	sendDisplay(0,0,0x0C); /* Display on, Cursor off, Blink off */// 0000 1100 = 0C
	sendDisplay(0,0,0x01); /* Clear Display */
}

/*
 * @brief	sendDisplay takes information bits; rs,rw and 8 bits db.
 * 			uint8_t db = {0b(db7)(db6)(db5)(db4)(db3)(db2)(db1)(db0)}
 * 			it shifts the data into the following 3 bytes:
 * 			{0b0(rs)(rw)11111, 0b0000(db3)(db2)(db1)(db0), 0b0000(db7)(db6)(db5)(db4)}
 *
 * @param	rs,rw,db wich is chosen accordingly to the manual depending on what task
 * 			or information is sent to the display.
 *
 * @return	void
 */
void sendDisplay(uint8_t rs,uint8_t rw,uint8_t db){
	data[0] = 0x1F | (rs << 6) | (rw << 5);
	data[1] = db & 0x0f;
	data[2] = (db & 0xf0) >> 4;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2,data,3,1000);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
}
