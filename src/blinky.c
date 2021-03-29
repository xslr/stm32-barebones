
#include <stm32f4xx_hal.h>
#include "stm32f4xx_it.h"


// Diymore STM32F4 user led - PE0
#define LED_PORT                GPIOE
#define LED_PIN                 GPIO_PIN_0
#define LED_PORT_CLK_ENABLE     __HAL_RCC_GPIOE_CLK_ENABLE

void SysTick_Handler(void)
{
  HAL_IncTick();

  // 1 Hz blinking
#if 0
  auto tick_val = HAL_GetTick();
  if (tick_val % 10 < 5) {
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
  }
#endif

#if 1
  if ((HAL_GetTick() % 500) == 0)
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
#endif
}


void initGPIO()
{
  GPIO_InitTypeDef GPIO_Config;

  GPIO_Config.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Config.Pull = GPIO_NOPULL;
  GPIO_Config.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_Config.Pin = LED_PIN;

  LED_PORT_CLK_ENABLE();
  HAL_GPIO_Init(LED_PORT, &GPIO_Config);
}


int main(void)
{
  HAL_Init();
  initGPIO();
  // 1kHz ticks
  HAL_SYSTICK_Config(SystemCoreClock / 1000);

  for (;;) {
    __WFI();
  }

  return 0;
}
