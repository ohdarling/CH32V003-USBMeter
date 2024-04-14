#pragma once

#include "drivers/clock.h"
#include "drivers/gpio.h"

#define BTN_LEFT    0
#define BTN_RIGHT   1
#define LONG_PRESS_PERIOD   3000

struct ButtonState {
    uint8_t pin;
    uint8_t state;
    uint32_t ts;
};

ButtonState buttons[] = {
    {
        .pin = PD2,
        .state = 1,
        .ts = 0,
    },
    {
        .pin = PD3,
        .state = 1,
        .ts = 0,
    },
};

#define BUTTON_NO_ACTION    0
#define BUTTON_CLICK        1
#define BUTTON_LONG_CLICK   2

void button_setup() {
    PIN_input(buttons[BTN_LEFT].pin);
    PIN_input(buttons[BTN_RIGHT].pin);
}

int check_button(int index) {
    int new_state = PIN_read(buttons[index].pin);
    int old_state = buttons[index].state;
    int action = BUTTON_NO_ACTION;
    if (new_state != old_state) {
        if (new_state == 1) {
            if (millis() - buttons[index].ts > LONG_PRESS_PERIOD) {
                action = BUTTON_LONG_CLICK;
            } else {
                action = BUTTON_CLICK;
            }
        }
        buttons[index].state = new_state;
        buttons[index].ts = millis();
    }

    return action;
}
