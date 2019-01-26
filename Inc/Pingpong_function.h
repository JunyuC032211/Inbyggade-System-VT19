

#ifndef __Pingpong_function_H
#define __Pingpong_function_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "main.h"
#include "stdbool.h"

void Led_on(uint8_t Lednr);
/**
@brief L_hit, check if L button is pressed
@param void
@return bool, true if L button pushed, false otherwise
*/
bool L_hit(void);
/**
@brief R_hit, check if R button is pressed
@param void
@return bool, true if R button pushed, false otherwise
*/
bool R_hit(void);

#ifdef __cplusplus
}
#endif

#endif /* __Pingpong_function_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/