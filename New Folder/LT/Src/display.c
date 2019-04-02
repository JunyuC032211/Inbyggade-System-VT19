#include "display.h"


 uint8_t data[3]={0x00,0x00,0x00};
 
  void initDisplay(void){
        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_SET);
	while(1)
        {
          sendDisplay(0,0,0x3A);/* Function Set -> 8-bit data RE=1 */
          HAL_Delay(1);
        } 
	sendDisplay(0,0,0x09); /* 4 line display */
	sendDisplay(0,0,0x06); /* bottom view */
	sendDisplay(0,0,0x1E); /* BS1 = 1 */
	sendDisplay(0,0,0x39); /* Function Set -> 8-bit data RE=0 */
	sendDisplay(0,0,0x1B); /* Internal OSC */
	sendDisplay(0,0,0x6E); /* Follower control */
	sendDisplay(0,0,0x56); /* Power control */
	sendDisplay(0,0,0x7A); /* Contrast Set */
	sendDisplay(0,0,0x38); /* Function Set -> 8-bit data IS=0 */
	sendDisplay(0,0,0x0F); /* Display on, Cursor on, Blink on */// 0000 1100 = 0C
        sendDisplay(0,0,0x01); // clear display
  }

  void sendDisplay(uint8_t rs,uint8_t rw,uint8_t db)
    {
	data[0] = 0x1F | (rs << 6) | (rw << 5);
	data[1] = db & 0x0f;
	data[2] = (db & 0xf0) >> 4;
	HAL_SPI_Transmit(&hspi2,data,3,1000);
//        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
    }