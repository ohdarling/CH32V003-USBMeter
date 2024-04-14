#pragma once

/* Includes ------------------------------------------------------------------*/
#include <ch32v00x.h>

#ifdef __cplusplus
extern "C" {
#endif

#define millis() getCurrentMillis()

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t getCurrentMillis(void);
uint32_t getCurrentMicros(void);
void systick_init(void);
void delay(int32_t ms);

// void configIPClock(void);
// void enableClock(sourceClock_t source);
// void configHSECapacitorTuning(void);

#ifdef __cplusplus
}
#endif
