#pragma once

#include "drivers/oled_min.h"
#include <string.h>

struct DCfont {
    uint8_t *data;
    uint8_t width;
    uint8_t height;
    uint8_t min, max;
};

#include "res/ModernDos.h"

#define display_init            OLED_init

#define font_data               FONT8X16MDOS

constexpr int BUF_LEN = 128 * 64 / 8;
static uint8_t display_buffer[BUF_LEN] = { 0 };

void display_write_line(int row, const char *str) {
    for (uint8_t row_offset = 0; row_offset < 2; ++row_offset) {
        int buf_offset = (row * 2 + row_offset) * 128;
        uint8_t chidx = 0;
        for (; str[chidx] != 0; ++chidx) {
            uint8_t ch = str[chidx];
            // uint8_t *row_data = (uint8_t *)font_data + ((ch - 32) * 16) + (row_offset * 8);
            uint8_t *row_data = (uint8_t *)font_data->data + (ch - 32) * (font_data->width * font_data->height) + row_offset * font_data->width;
            for (uint8_t i = 0; i < font_data->width; ++i) {
                display_buffer[buf_offset] |= row_data[i];
                buf_offset++;
            }
        }
    }
}

void display_clear() {
    memset(display_buffer, 0, BUF_LEN);
}

void display_flush() {
    OLED_setpos(0, 0);
    for (int i = 0; i < BUF_LEN; ++i) {
        if (i % 16 == 0) {
            if (i > 0) {
                OLED_data_stop();
            }
            OLED_data_start();
        }
        I2C_write(display_buffer[i]);
    }
    OLED_data_stop();
}

void display_draw_dot(int x, int y) {
    int row = y / 8;
    int offset = row * 128 + x;
    int pixel_offset = y % 8;
    u8 b = display_buffer[offset];
    b = b | (1 << pixel_offset);
    display_buffer[offset] = b;
}
