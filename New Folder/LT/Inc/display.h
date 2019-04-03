#ifndef __display_H
#define __display_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "main.h"
#include "stdint.h"

 void initDisplay(void);
 void sendDisplay(uint8_t rs,uint8_t rw,uint8_t db);

#ifdef __cplusplus
}
#endif

#endif /* __display_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/