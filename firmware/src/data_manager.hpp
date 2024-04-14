#pragma once

#include "drivers/INA219_WE.h"
#include <string.h>
#include "drivers/clock.h"
#include "drivers/flash_eeprom.h"

#define INA219_I2C_ADDRESS (0x40 << 1)
#define SHUNT_SIZE_IN_MR 10

INA219_WE ina219(INA219_I2C_ADDRESS);

int32_t measure_vbus_mv = 0;
int32_t measure_vshunt_uv = 0;
int32_t measure_current_ma = 0;
int32_t measure_power_mw = 0;
int32_t measure_cap_mwh = 0;
int32_t measure_cap_last_time = 0;

#define POWER_HISTORY_PERIOD 300
#define POWER_HISTORY_MAX_COUNT  128

u16 power_history[POWER_HISTORY_MAX_COUNT] = { 0 };
int power_history_index = 0;
int power_history_count = 0;
uint32_t power_history_last_ts = 0;

#define CAPACITY_SAVE_PERIOD 60000
#define EEPROM_OFFSET_CAPACITY 0
uint32_t capacity_last_saved_ms = 0;
int32_t capacity_last_save_val = 0;

void adc_setup() {
    ina219.init();
    ina219.setMeasureMode(CONTINUOUS);
    ina219.setPGain(PG_80);
    ina219.setShuntSizeInOhms(SHUNT_SIZE_IN_MR / 1000);

    ch32v_eeprom_load();
    ch32v_eeprom_read(EEPROM_OFFSET_CAPACITY, (u8 *)&measure_cap_mwh, sizeof(measure_cap_mwh));
    capacity_last_save_val = measure_cap_mwh;
}

void adc_read_values() {
    measure_vbus_mv = ina219.getBusVoltage_V() * 1000;
    measure_vshunt_uv = ina219.getShuntVoltage_mV() * 1000;
    if (measure_vshunt_uv < 0) {
        measure_vshunt_uv = 0;
    }
    measure_current_ma = measure_vshunt_uv / SHUNT_SIZE_IN_MR;
    measure_power_mw = measure_vbus_mv * measure_current_ma / 1000;

    uint32_t now = millis();
    uint32_t period = now - measure_cap_last_time;
    measure_cap_last_time = now;
    int32_t period_cap = measure_power_mw * period / 1000;

    measure_cap_mwh += period_cap;

    if (now - power_history_last_ts >= POWER_HISTORY_PERIOD) {
        int save_index = (power_history_index + power_history_count) % POWER_HISTORY_MAX_COUNT;
        power_history[save_index] = measure_power_mw;

        power_history_count = power_history_count + 1;
        if (power_history_count >= POWER_HISTORY_MAX_COUNT) {
            power_history_count = POWER_HISTORY_MAX_COUNT;
            power_history_index = (power_history_index + 1) % POWER_HISTORY_MAX_COUNT;
        }
        power_history_last_ts = now;
    }

    if (now - capacity_last_saved_ms >= CAPACITY_SAVE_PERIOD) {
        if (measure_cap_mwh > capacity_last_save_val) {
            ch32v_eeprom_write(EEPROM_OFFSET_CAPACITY, (u8 *)&measure_cap_mwh, sizeof(measure_cap_mwh));
            capacity_last_save_val = measure_cap_mwh;
        }

        capacity_last_saved_ms = now;
    }
}
