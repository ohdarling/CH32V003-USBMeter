#include "clock.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TICK_FREQ_1KHz    1L
// #define TICK_FREQ_100Hz   10L
// #define TICK_FREQ_10Hz    100L


__IO uint64_t msTick=0;
__attribute__ ((weak)) uint64_t GetTick(void)
{
  return msTick;
}


void osSystickHandler() __attribute__((weak, alias("noOsSystickHandler")));
void noOsSystickHandler()
{

}

/**
  * @brief  Function called wto read the current millisecond
  * @param  None
  * @retval None
  */
uint32_t getCurrentMillis(void)
{
  return GetTick();
}


uint32_t getCurrentMicros(void)
{

  uint64_t m0 = GetTick();
  __IO uint64_t u0 = SysTick->CNT;
  uint64_t m1 = GetTick();
  __IO uint32_t u1 = SysTick->CNT;   //may be a interruption
   uint64_t tms = SysTick->CMP + 1;

  if (m1 != m0) {
    return (m1 * 1000 + ((tms - u1) * 1000) / tms);
  } else {
    return (m0 * 1000 + ((tms - u0) * 1000) / tms);
  }
}


/*********************************************************************
 * @fn      SysTick_Handler
 *
 * @brief   This function handles systick interrupt.
 *
 * @return  none
 */
void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick_Handler(void)
{
  msTick+=TICK_FREQ_1KHz;
  osSystickHandler();
  SysTick->SR = 0;
}

void systick_init(void)
{
    SysTick->SR  = 0;
    SysTick->CTLR= 0;
    SysTick->CNT = 0;
    SysTick->CMP = SystemCoreClock / 1000 - 1;
    SysTick->CTLR= 0xF;
    NVIC_SetPriority(SysTicK_IRQn,0xFF);
    NVIC_EnableIRQ(SysTicK_IRQn);
}

void delay(int32_t ms) {
    uint32_t end = msTick + ms;
    while (msTick < end) {
        // loop
    }
}