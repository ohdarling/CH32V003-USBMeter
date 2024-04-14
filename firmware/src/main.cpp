#include <ch32v00x.h>
#include <debug.h>

#include "display.hpp"
#include "data_manager.hpp"
#include "button.hpp"

extern "C" void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
extern "C" void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

int current_page = 0;
#define PAGE_METRICS    0
#define PAGE_HISTORY    1
#define PAGE_COUNT      2

void show_power_metrics() {
    char buf[17];
    display_clear();

    snprintf(buf, 17, (const char *)"Volt : %dmV", (int)measure_vbus_mv);
    display_write_line(0, buf);

    snprintf(buf, 17, (const char *)"Curr : %dmA", (int)measure_current_ma);
    display_write_line(1, buf);

    snprintf(buf, 17, (const char *)"Power: %dmW", (int)measure_power_mw);
    display_write_line(2, buf);

    snprintf(buf, 17, (const char *)"Cap  : %dmWh", (int)(measure_cap_mwh / 3600));
    display_write_line(3, buf);

    display_flush();
}

void show_power_history() {
    display_clear();

    display_write_line(0, "Power History");

    for (int i = 0; i < power_history_count; ++i) {
        u16 p = power_history[(power_history_index + i) % POWER_HISTORY_MAX_COUNT];
        int32_t y = 63 - (p * 63 / 30000);
        display_draw_dot(i, y);
    }

    display_flush();
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    systick_init();
    USART_Printf_Init(115200);

    // Delay_Ms(1000); // give serial monitor time to open
    // printf("SystemClk: %u\r\n", (unsigned)SystemCoreClock);
    // printf("DeviceID: %08x\r\n", (unsigned)DBGMCU_GetDEVID());

    display_init();
    adc_setup();
    button_setup();

    while (1) {
        adc_read_values();

        if (check_button(BTN_LEFT) == BUTTON_CLICK) {
            current_page = current_page - 1;
            if (current_page < 0) {
                current_page = PAGE_COUNT - 1;
            }
        }

        if (check_button(BTN_RIGHT) == BUTTON_CLICK) {
            current_page = (current_page + 1) % PAGE_COUNT;
        }

        switch (current_page) {
            case PAGE_METRICS:
                show_power_metrics();
                break;
            case PAGE_HISTORY:
                show_power_history();
                break;
            default:
                break;
        }
    }
}

void NMI_Handler(void) {}
void HardFault_Handler(void)
{
    while (1)
    {
    }
}
