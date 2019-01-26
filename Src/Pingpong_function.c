

#include "Pingpong_function.h"
#include "stdbool.h"
  

/* Function Led_on
Input: Turn on led Lednr
 Lednr can be 1-8, all other values turns all leds off
Output: No
*/
void Led_on(uint8_t Lednr)
{
 uint8_t i;
 for (i=1; i<= 8; i++)
 {
 switch(i){
 case 1 : // Led 1
 if (Lednr==i) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
 else HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
 break;
 case 2 : // Led 2
 if (Lednr==i) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
 else HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
 break;

 case 3 : // Led 3
 if (Lednr==i) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
 else HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
 break;
 case 4 : // Led 4
 if (Lednr==i) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
 else HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
 break;
 case 5 : // Led 5
 if (Lednr==i) HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
 else HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
 break;
 case 6 : // Led 6
 if (Lednr==i) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
 else HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
 break;
 case 7 : // Led 7
 if (Lednr==i) HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
 else HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
 break;
 case 8 : // Led 8
 if (Lednr==i) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
 else HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
 break;
 default :
 ;
 } // end switch

 } // end for-loop

 return;
 } // end function Led_on

/**
@brief L_hit, check if L button is pressed
@param void
@return bool, true if L button pushed, false otherwise
*/
bool L_hit(void)
{
   if(HAL_GPIO_ReadPin(L_BUTTON_GPIO_Port, L_BUTTON_Pin) == 0)
   return true;
   else
     return false;
}
/**
@brief R_hit, check if R button is pressed
@param void
@return bool, true if R button pushed, false otherwise
*/
bool R_hit(void)
{
   if( HAL_GPIO_ReadPin(R_BUTTON_GPIO_Port, R_BUTTON_Pin) == 0)
     return true;
   else
     return false;
}